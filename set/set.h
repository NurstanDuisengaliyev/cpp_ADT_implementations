
#ifndef SET_
#define SET_ 1

#include <iostream>
#include <string> 
#include <concepts>

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


struct treenode
{
   // using valtype = std::string; 
   // using valcmp = standard_cmp< valtype > ; 

   using valtype = int;
   using valcmp = standard_cmp< valtype > ;

   valtype val; 
   treenode* left;
   treenode* right;

   treenode( const valtype& val, 
             treenode* left = nullptr, treenode* right = nullptr )
      : val( val ),
        left( left ),
        right( right )  
   { }

};


const treenode* find( const treenode* n, const treenode::valtype& val );
   // Returns nullptr if not found.

treenode** find( treenode** n, const treenode::valtype& val ); 
   // Returns a pointer to nullptnr if not found. 

size_t size( const treenode* n ); 
   // Returns the number of values stored in the tree. 

void deallocate( treenode* n ); 
   // Deallocate the complete tree below n.

treenode* makecopy( const treenode* n );
   // Make a copy of the tree below n.

treenode* extractrightmost( treenode** from );
   // Extract and remove the rightmost tree below *from.

void print( std::ostream& out, const treenode* n, unsigned int indent );
   // Print the tree as tree.

size_t height( const treenode* n );
   // Returns the height of the tree starting at n.

unsigned int log_base2( size_t s );


class set
{
   treenode* tr;

   using valtype = treenode::valtype;
      // Don't change this line. If you want to change the type,
      // change it in treenode. 

public: 
   set( ) 
      : tr( nullptr ) 
   { } 

   set( const set& other );

   set& operator = ( const set& other );

   ~set( );

   set( std::initializer_list< valtype > init )
      : tr( nullptr ) 
   {
      for( const auto& s: init ) 
         insert(s);
   } 
  
   bool contains( const valtype& val ) const;

   bool insert( const valtype& val );
      // Returns true if the insertion took place.

   bool remove( const valtype& val );

   size_t size( ) const; 
   size_t height( ) const; 

   bool empty( ) const; 
      // Must work in constant time!

   void clear( );

   void checksorted( ) const;
      // Check if the tree is sorted, and throw an exception
      // if it is not. Call this function often to check your
      // trees, but make your final performance tests without it.  

   void print( std::ostream& out, unsigned int indent = 0 ) const;
};


inline std::ostream& operator << ( std::ostream& out, const set& s )
{
   s. print( out );
   return out; 
}

#endif

