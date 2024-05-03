
#include "deque.h"
#include <utility>

int main( int argc, char* argv [] )
{
   // Examples with exchange:

   std::string s = "hallo"; 
   std::cout << std::exchange( s, "goodbye" ) << "\n";
   std::cout << std::exchange( s, "hello again" ) << "\n";
   std::cout << s << "\n";

#if 1
   deque q;
   std::cout << q. deq_size << "\n";

   q. push_back( 1 );
   q. push_front( 2 );
   q. push_front( 3 );
   q. push_front( 4 );

   q. check_invariant( );

   while( q && false )
   {
      std::cout << q. back( ) << "\n"; 
      std::cout << q << "\n";
      q. pop_back( );
      q. check_invariant( ); 
   }
   q. check_invariant( );
   std::cout << q << "\n";

   deque q2 = { 3.16, 2.718, 3.16 };

   std::cout << q << "\n";
   std::cout << q2 << "\n\n";

   q = std::move(q2); 
   std::cout << q << "\n";
   std::cout << q2 << "\n";

   // Open this when you have rvalue-reference CC and assignment:

   // Exchanges q and q2:

   q2 = std::exchange( q, std::move(q2) );
   std::cout << q << "\n";
   std::cout << q2 << "\n";
 
#else
   std::cout << price(1000) << " " << 1000_kzt << " " << 1000_tt << "\n";

   std::cout << 5 * 500_kzt << "\n";
   std::cout << 300_tt + 400_kzt << "\n";
   std::cout << ( 250_tt == 200_tt + 50_tt ) << "\n";
   std::cout << order( "tiramisu", 1790_tt ) << "\n";
   std::cout << order( "medowik", 1590_tt, 3 ) << "\n";

   deque q;
   q. push_back( { "espresso", 750_tt } );
   std::cout << q << "\n";
   q. push_back( { "esterhazy", 1690_kzt } );
   std::cout << q << "\n"; 
   q. push_back( { "latte macchiato", 1170_tt, 2 } );
   std::cout << q << "\n";

   while( q. size( ) > 3 )
   {
      auto s = std::move( q. front( ));
      std::cout << s << "\n";
      q. pop_front( );
   }

   deque many_orders = 
      {  { "cake", 500_tt }, { "cappuccino", 1170_tt }, 
         { "pavlova", 1990_tt }} ;

   q = many_orders;

   while( q. size( ))
   {
      std::cout << q. front( ) << "\n";
      q. pop_front( );
   }
#endif

   return 0;
}



