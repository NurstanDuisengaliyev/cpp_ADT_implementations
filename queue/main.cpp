
#include <iostream>
#include <string>
#include "queue.h"

#include <list> 


int main( int argc, char* argv [ ] )
{

#if 1
   queue q;
   q. push(1);
   q. push(2);

   q. push(3);
   q. pop( );

   q. push(4);
   q. push(5);

   q. push(100);
   q. pop( );
   q. printstate( std::cout );

#else
   // Try this with string

   queue q3 = { "this", "is", "a", "queue" };
   std::cout << q3 << "\n";
   q3. pop( ); 
   q3. push( "round" ); 
   std::cout << q3. peek( ) << "\n";
   q3. pop( ); 
   q3. printstate( std::cout ); 
   auto q4 = q3; 

   return 0;
#endif
}

