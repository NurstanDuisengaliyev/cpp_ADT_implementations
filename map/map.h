
#ifndef MAP_
#define MAP_

#include <iostream>
#include <vector>
#include <list>
#include <string> 
#include <utility>
#include <cmath>

struct case_insensitive_cmp
{
   case_insensitive_cmp( ) noexcept = default;

   int operator( ) ( const std::string& s1, const std::string& s2 ) const;
      // Case insensitive compare.
      // return a negative number if s1 < s2 (case insensitive).
      // return zero if s1 == s2 (case insensitive).
      // return a positive number if s1 > s2 (case insensitive).
};

template< std::totally_ordered T >
struct standard_cmp
{
   standard_cmp( ) noexcept = default;

   int operator( ) ( const T& t1, const T& t2 ) const
   {
      if( t1 < t2 ) return -1;
      if( t1 > t2 ) return 1;
      return 0;
   }
};

struct case_insensitive_hash
{
   case_insensitive_hash( ) noexcept = default;

   size_t operator( ) ( const std::string& s ) const;
      // Case insensitive hash function.
};


template< std::totally_ordered T >
struct standard_hash
{
   standard_hash( ) noexcept = default;

   size_t operator( ) ( const T& t ) const
   {
      std::hash<T> h;
      return h(t); 
   }
};


struct map
{
   using keytype = std::string;
   using keyhash = standard_hash< keytype > ;
   using keycmp = standard_cmp< keytype > ;
   // using keyhash = case_insensitive_hash;
   // using keycmp = case_insensitive_cmp;

   using valtype = int;

   // Switch this to private when finished:

public:
   double max_load_factor;
   size_t current_size;         // Total number of elements.

   using buckettype = std::list< std::pair< keytype, valtype >> ; 
      // The type of a bucket. Never use typedef in C++ . 

   std::vector< buckettype > buckets;

   buckettype& getbucket( const keytype& key );
   const buckettype& getbucket( const keytype& key ) const;

   static buckettype::iterator find( const keytype& key, buckettype& bk );

   static buckettype::const_iterator find( const keytype& key,
                                           const buckettype& bk );

   bool rehash_needed( size_t sz ) const
      { return sz > buckets. size( ) * max_load_factor; }

      // True if increasing the size to sz makes the load factor so high
      // that a rehash will be needed.

   size_t nrbuckets_needed( size_t sz ) const;
      // nr of buckets needed when we have size sz, and
      // the load factor is <= max_load_factor.

   void rehash( size_t nrbuckets );
      // Rehash towards nrbuckets.
 
public:
   // Number of buckets cannot be zero. 
   // Different from earlier interpretations, we use 
   // powers of three. Best would be prime numbers close
   // to powers of two. 
   
   map( double max_load_factor = 3.0, size_t initialbuckets = 3 ) 
      : max_load_factor( max_load_factor ),
        current_size(0),
        buckets( std::vector< buckettype > ( initialbuckets ))
   { 
      if( max_load_factor <= 0.01 )   
         throw std::logic_error( "max load factor must be > 0" ); 

      if( initialbuckets < 3 )
         throw std::logic_error( "initial bucket nr must be at least 3" );
   }

   map( std::initializer_list< std::pair< keytype, valtype >> init, 
        double max_load_factor = 3 )
      : max_load_factor( max_load_factor ),
        current_size(0),
        buckets( std::vector< buckettype > ( nrbuckets_needed( init. size( ))))
   {
      for( const auto& kv : init )
         insert( kv. first, kv. second );
   }

   map( const map& mp ) = default;

   map( map&& mp )
      : max_load_factor( mp. max_load_factor ),
        current_size( std::exchange( mp. current_size, 0 )),
        buckets( std::exchange( mp. buckets, std::vector< buckettype > (3))) 
   { }

   map& operator = ( const map& mp ) = default;

   map& operator = ( map&& mp ) 
   {
      max_load_factor = mp. max_load_factor;
      current_size = std::exchange( mp. current_size, 0 );
      buckets = std::exchange( mp. buckets, std::vector< buckettype > (3));
      return *this;  
   }

   bool contains( const keytype& key ) const; 

   bool insert( const keytype& key, const valtype& val );
      // Returns true if the insertion took place.

   const valtype& at( const keytype& key ) const;
   valtype& at( const keytype& k );

   valtype& operator [] ( const keytype& key );
      // Creates a default value if key is not present.

   bool erase( const keytype& key );
      // Returns true if s was found and removed.

   size_t size() const;

   bool empty() const;

   void clear();
      // No need to decrease the number of buckets.
     
   void print( std::ostream& out ) const; 

   // The functions below are not part of 
   // the map interface, they are specific for hashing:

   double loadfactor() const 
   {
      return static_cast<double> ( current_size ) / buckets. size( ); 
         // C-style casts of form (double) map_size are deprecated. 
   }

   double standarddev() const 
   {
      double sum = 0.0;
      double lf = loadfactor();

      for ( const auto& l : buckets ) 
      {
	  double dif = l. size( ) - lf;
          sum += dif*dif;
      }

      return sqrt( sum / buckets. size( ));
   }
  
   std::ostream& printstatistics( std::ostream& out ) const
   {
      out << "map size =            " << size( ) << "\n";
      out << "load factor =         " << loadfactor( ) <<
          " ( max = " << max_load_factor << " )\n";
      out << "standard deviation =  " << standarddev( ) << "\n";
      return out;
   }

};

inline std::ostream& operator << ( std::ostream& out, const map& m ) 
{
   m. print( out );
   return out;
}

#endif


