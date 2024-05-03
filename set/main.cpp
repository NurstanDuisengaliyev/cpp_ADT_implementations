
#include <random>
#include <algorithm>

#include "set.h"
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

#if 0
   // A few simple tests with std::string.

   set small;    // A small test tree.

   std::cout << small. height( ) << "\n";
   small. insert( "if" ); 
   std::cout << small. height( ) << "\n"; 
   small. insert( "thE" ); 
   std::cout << small. height( ) << "\n";
   small. insert( "vaLue" );
   std::cout << small << "\n";
   std::cout << small. height( ) << "\n";
//   small. clear( );
   std::cout << "this is the tree: " << small << "\n";
   set small3 = small; 
   std::cout << small3 << "\n";

   std::cout << small. contains( "Xx" ) << "\n";
   std::cout << small. contains( "vAlUe" ) << "\n";
#endif

#if 0
   // Some more tests with std::string: 
   // Make sure that your set is case insensitive.
   small. insert( "oskemen" );
   std::cout << small. contains( "kostanay" ) << "\n";

   small. insert( "atyrau" );
   small. insert( "nursultan" );
   small. insert( "Almaty" );
   small. insert( "shymkent" ); 
   small. insert( "almaty" ); 
   small. insert( "pavlodar" );

   small. insert( "PavloDar" ); 
   small. insert( "sHYmKeNt" );  
   std::cout << small << "\n";
   return 0;
   small. remove( "PavLoDar" );
   small. remove( "almaty" );
   std::cout << small. remove( "if" );

   std::cout << small << "\n";

   small. checksorted( );
   std::cout << small << "\n"; 
   std::cout << small. size( ) << "\n";
   std::cout << "Height is " << small. height( );
   std::cout << " should be approximately " << 
     log_base2( small. size( )) << "\n";
      // If the numbers differ much, the tree is badly balanced. 

   auto small2 = small; // Copy constructor. 
   std::cout << small2 << "\n";
   std::cout << "size = " << small2. size( ) << "\n";
   std::cout << "height = " << small2. height( ) << "\n";
   small2 = small;      // Assignment.
   small = small;       // Self assignment.

#endif 

#if 1
   // Measurements using int.

   timetable tab( std::string( "BST-based set" ));

   for( size_t s = 1000; s < 4096 * 1000; s = 2 * s )
   {
      std::cout << "----------------------------------------\n";

      // Create random test set of size s:

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

      // Uncomment to see the performance of a badly balanced tree:

      bool i_want_to_see_the_bad_performance_of_an_unbalanced_tree = false; 
      //bool i_want_to_see_the_bad_performance_of_an_unbalanced_tree = true; 
      if( i_want_to_see_the_bad_performance_of_an_unbalanced_tree )
      { 
         std::sort( values. begin( ), values. end( ));
      }
      set someset1;

      timer tt; 
      size_t nr_insertions = 0;
      size_t nr_deletions = 0;

      for( size_t i = 0; i != values. size( ); ++ i ) 
      {
         nr_insertions += someset1. insert( values[i] );
      }

      // We do some deletions too:

      for( const auto& s : values )
      {
         // Remove the odd values:

         if( s & 1 )
            nr_deletions += someset1. remove( s );

         nr_deletions += someset1. remove( s + 2 );  // Probably not there.
      }
    
      // std::cout << someset1 << "\n";
      std::cout << nr_insertions << " " << nr_deletions << "\n";

      auto someset2 = someset1;

      if( nr_insertions - nr_deletions != someset2. size( )) 
      {
         std::cout << "nr = " << nr_insertions << "\n";
         std::cout << "size( ) = " << someset2. size( ) << "\n"; 
         throw std::runtime_error( 
                       "something went wrong with counting insertions" );
      }

      // Don't use size( )! It is O(n), and will mess up your performance. 

      tab. insert( s, tt. time( )); 

      std::cout << "number of insertions " << nr_insertions << "\n";
      std::cout << "number of deletions " << nr_deletions << "\n"; 
      std::cout << "tree-height = " << someset2. height( ) << ", " << "log_base2 = " << log_base2( someset2. size( )) << "\n";

      std::cout << "finished test for " << s << "\n";
   } 

   std::cout << tab << "\n"; 
   std::cout << "totaltime " << tab. totaltime( ) << "\n";
#endif
}

/*
Performance table of BST-based set (inputsize/runtime in seconds) balanced:
     1000/3.2541e-04     2000/6.1827e-04     4000/1.5768e-03     8000/3.0137e-03     16000/9.9176e-03     32000/1.8101e-02     64000/4.1302e-02     128000/1.2726e-01     256000/4.0087e-01     512000/1.1806e+00     1024000/2.2147e+00     2048000/5.5686e+00

totaltime 9.5669e+00

Performance table of BST-based set (inputsize/runtime in seconds) unbalanced:
     1000/2.0429e-03     2000/1.0889e-02     4000/3.4447e-02     8000/1.3395e-01     16000/5.4899e-01     32000/2.3008e+00     64000/7.6416e+00

totaltime 1.0673e+01
*/
