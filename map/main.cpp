
#include <random>
#include <algorithm>
#include <sstream>

#include "map.h"
#include "timetable.h"
#include "timer.h"


std::vector< int > randomvector( size_t sz )
{
   std::vector< int > res;
   for( size_t i = 0; i != sz; ++ i )
   {
      res. push_back( rand( ) );
   }
   return res;
}


int main( int argc, char* argv[ ] )
{

#if 1
   {
      map deutsch;
      deutsch[ "null" ] = 0;
      deutsch[ "eins" ] = 1;
      deutsch[ "zwei" ] = 2;
      deutsch[ "drei" ] = 3;
      deutsch[ "vier" ] = 4;
      deutsch[ "fuenf" ] = 5;
      deutsch[ "sechs" ] = deutsch[ "fuenf" ];
      deutsch[ "sechs" ] ++; 
      deutsch[ "sieben" ] = 7;
      deutsch[ "acht" ] = deutsch[ "sieben" ] + 1;
      deutsch[ "neun" ] = 9;
      deutsch[ "zehn" ] = deutsch. at( "neun" ) + 1;
      std::cout << deutsch << "\n";
      std::cout << deutsch. size( ) << "\n";
   }
#endif

#if 0
   {
      map kazakh;
      kazakh[0] = "nol";
      kazakh[1] = "bir";
      kazakh[2] = "eki";
      kazakh[3] = "ush";
      kazakh[4] = "tort";
      kazakh[5] = "bes";
      kazakh[6] = "alty";
      kazakh[7] = "zheti";   
      kazakh[8] = "segiz";
      kazakh[9] = "toryz";
      kazakh[10] = "on";

      std::cout << kazakh << "\n";
      return 0;
   }
#endif

#if 0 
   { 
      // Tests for case insensitive map:

      map small;    // A small test map.

      small[ "the" ] = 4;
      std::cout << small[ "The" ] << "\n";

      small[ "notthere" ] ++ ;

      small. insert( "if", 2 ); 
      small[ "the" ] = 3;
      small[ "value" ] = 5;
      small. insert( "aaa", 4 );
      small. insert( "aAa", 4 );
      small. insert( "ccc", 2 );
      small. insert( "xyz", 2 );
      small. insert( "XYZ", 2 );
      small. insert( "ssss", 4 );

      std::cout << small. at( "xYZ" ) << "\n";
      small. at( "ssss" ) = 55;

      std::cout << small << "\n";
      std::cout << small. size( ) << "\n";

      map small3 = small; 
      small. clear( );
      std::cout << "this is the hash map after clear:\n" << small << "\n";
      std::cout << small3 << "\n";

      small = std::move( small3 );
      std::cout << "small3\n";
      std::cout << small3 << "\n";

      std::cout << small << "\n";
      std::cout << small. contains( "xx" ) << "\n";
      std::cout << small. at( "CCC" ) << "\n";
         // To contain or not to contain, that's the question. 

      return 0;
   }
#endif

#if 0
   // Measurements using int -> int.

   timetable tab( std::string( "map" ));

   for( size_t s = 1000; s < 4096 * 1000; s = 2 * s )
   {
      std::cout << "----------------------------------------\n";

      std::vector< int > values = randomvector(s);

      //  Turn on if you want to see the test vector.

      bool i_want_to_see_the_test_vector = false;
      if( i_want_to_see_the_test_vector )
      {
         std::cout << "values: ";
         for( const auto& s : values )
            std::cout << s << " ";
         std::cout << "\n";
      }

      map somemap1;

      timer tt;
      size_t nr_insertions = 0;
      size_t nr_deletions = 0;

      for( size_t i = 0; i != values. size( ); ++ i )
      {
         nr_insertions += somemap1. insert(
                              std::to_string( values[i] ), values[i] );
      }

      // We do some deletions too:

      for( const auto& s : values )
      {
         // Remove the odd values:

         if( s & 1 )
            nr_deletions += somemap1. erase( std::to_string(s));

         nr_deletions += somemap1. erase( std::to_string( s + 2 ));  
                                     // Probably not there.
      }

      // std::cout << somemap1 << "\n";

      std::cout << nr_insertions << " " << nr_deletions << "\n";

      auto somemap2 = somemap1;

      if( nr_insertions - nr_deletions != somemap2. size( ))
      {
         std::cout << "nr = " << nr_insertions << "\n";
         std::cout << "size( ) = " << somemap2. size( ) << "\n";
         throw std::runtime_error(
                       "something went wrong with counting insertions" );
      }

      tab. insert( s, tt. time( ));

      std::cout << "number of insertions " << nr_insertions << "\n";
      std::cout << "number of deletions " << nr_deletions << "\n";
  
      somemap1. printstatistics( std::cout ); 
   }

   std::cout << tab << "\n"; 
   std::cout << "totaltime " << tab. totaltime( ) << "\n";
#endif

}

/*
Performance table of map (inputsize/runtime in seconds):
1000/1.4716e-03     2000/2.1686e-03 
4000/1.6014e-02     8000/1.3857e-01 
16000/4.3140e-01     32000/9.2838e-01
64000/2.9199e+00     128000/3.1128e+00
256000/9.0182e+00     512000/1.0037e+01
1024000/2.8692e+01     2048000/1.5052e+02

totaltime 2.0582e+02
*/


