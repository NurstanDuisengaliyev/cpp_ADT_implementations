
#include "map.h"

// Should be copied from assignment 3: 

int case_insensitive_cmp::operator( ) 
      ( const std::string& s1, const std::string& s2 ) const
{
   for (size_t i = 0; i < std::min(s1.size(), s2.size()); i ++) {
      char a = s1[i], b = s2[i];

      if (a >= 'A' && a <= 'Z') a = char((int)a + 32);
      if (b >= 'A' && b <= 'Z') b = char((int)b + 32);


      if (a == b) continue;
      if (a < b) return -1;
      else return 1;

   }
   if (s1.size() == s2.size()) return 0;
   else if (s1.size() < s2.size()) return -1;
   else return 1;
}


// Must be written:

size_t case_insensitive_hash::operator( ) ( const std::string& s ) const
{
   std::hash<std::string> h;
   std::string s1 = s;

   for (size_t i = 0; i < s1.size(); i ++) {

      if (s1[i] >= 'A' && s1[i] <= 'Z') s1[i] = char((int)s1[i] + 32);
      
   }

   return h(s1);

} 

auto map::getbucket( const keytype& key ) -> buckettype& 
{
   keyhash hh;
   size_t idx = hh(key) % buckets.size();
   buckettype& bucket = buckets[idx];
   return bucket;
}

auto map::getbucket( const keytype& key ) const -> const buckettype& 
{
   keyhash hh;
   size_t idx = hh(key) % buckets.size();
   const buckettype& bucket = buckets[idx];
   return bucket;
}

auto map::find( const keytype& key, buckettype& bk ) 
-> buckettype::iterator
{
   map::keycmp cmp;

   for (auto it = bk.begin(); it != bk.end(); it++) {
      // (*it).first
      // (*it).second

      if ( cmp (it->first, key) == 0 ) {
         return it;
      }

   }

   return bk.end();
}

auto map::find( const keytype& key, const buckettype& bk )
-> buckettype::const_iterator
{
   map::keycmp cmp;

   for (auto it = bk.begin(); it != bk.end(); it++) {
      // (*it).first
      // (*it).second

      if ( cmp (it->first, key) == 0 ) {
         return it;
      }

   }

   return bk.end();

}


size_t map::nrbuckets_needed( size_t sz ) const
{
   for (size_t i = 3;; i *= 3) {
      if (i * max_load_factor >= sz) {
         return i;
      }
   }
}

void map::rehash( size_t nrbuckets ) 
{
   auto oldbuckets = 
      std::exchange( buckets, std::vector< buckettype > ( nrbuckets ));

   // In this way, you can use method getbucket( ) for reinserting.

   for (size_t i = 0; i < oldbuckets.size(); i ++) {
      auto bucket = oldbuckets[i];
      // bucket is list

      for (auto it = bucket.begin(); it != bucket.end(); it++) {
         // it->first
         // it->second

         auto& ls = getbucket(it->first);

         ls.push_back(*it);

      }

   }

   

}


bool map::contains( const keytype& key ) const
{
   auto& ls = getbucket(key);

   if (find (key, ls) == ls.end()) {
      return false;
   }
   else {
      return true;
   }

}


bool map::insert( const keytype& key, const valtype& val )
{
   auto& ls = getbucket(key);
   if (find(key, ls) != ls.end()) {
      return false;
   }
   else {

      if (rehash_needed(current_size + 1 )) {

         rehash( nrbuckets_needed( current_size + 1 ));
         auto& ls2 = getbucket (key);
         ls2.push_back ( {key, val} );

      }
      else {  

         ls.push_back ( {key, val} );

      }
      current_size ++;
      return true;
   }
}

auto map::at( const keytype& key ) const -> const valtype&
{
   // If you want to store the bucket of key, make sure to use
   // a reference (not a copy). 
   auto& ls = getbucket(key);
   buckettype::const_iterator it = find (key, ls);

   if (it == ls.end()) {
      throw std::out_of_range ("blah");
   }
   else {
      const valtype& x = it->second;
      return x;
   }



}

auto map::at( const keytype& key ) -> valtype&
{
   // If you want to store the bucket of key, make sure to use
   // a reference (not a copy).
   auto& ls = getbucket(key);
   buckettype::iterator it = find (key, ls);
   if (it == ls.end()) {
      throw std::out_of_range ("blah");
   }
   else {
      valtype& x = it->second;
      return x;
   }

}

auto map::operator[] ( const keytype& key ) -> valtype& 
{
   auto& ls = getbucket(key);
   buckettype::iterator it = find (key, ls);
   if (it == ls.end()) {
      current_size ++;
      // create new

      if (rehash_needed(current_size + 1 )) {

         rehash( nrbuckets_needed( current_size + 1 ));
         auto& ls2 = getbucket (key);
         ls2.push_back( { key, valtype( ) } );

         valtype& x = ls2.back().second;

         return x;

      }
      else {  

         ls.push_back( { key, valtype( ) } );

         valtype& x = ls.back().second;

         return x;

      }


   }
   else {
      valtype& x = it->second;
      return x;
   }
}

bool map::erase( const keytype& key ) 
{
   auto& ls = getbucket(key);
   buckettype::iterator it = find (key, ls);

   if (it == ls.end()) {
      // doesn't exist
      return false;
   }
   else {
      ls.erase (it);
      current_size --;
      return true;

   }
}

size_t map::size( ) const
{
   return current_size;
}

bool map::empty( ) const
{
   if (current_size == 0) return true;
   else return false;
}

void map::clear( ) 
{
   current_size = 0;
   while (buckets.size() != 0) buckets.pop_back();

   std::exchange( buckets, std::vector< buckettype > ( 3 ));

}

void map::print( std::ostream& out ) const
{
   out << "hashmap( max_load_factor = " << max_load_factor;
   out << ", size = " << current_size << " ):\n";

   for( size_t i = 0; i != buckets. size( ); i++ )
   {
      out << "   bucket[" << i << "]:    {";
      for( auto p = buckets[i]. begin( ); p != buckets[i]. end( ); ++ p )
      {
         if( p != buckets[i]. begin( ))
            out << ", ";
         else
            out << " ";
         out << ( p -> first ) << " : " << ( p -> second );
      }
      out << " }\n";
   }
}


