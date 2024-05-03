
#ifndef ORDER_
#define ORDER_  

#include <string>
#include "price.h" 

struct order
{
   std::string product;
   price unitprice;
   unsigned int nr; 

   order( ) = delete;
    
   order( const std::string& product, price unitprice, unsigned int nr = 1 )
      : product( product ),
        unitprice( unitprice ),
        nr( nr )
   { }

   void print( std::ostream& out ) const
   {
      out << product << " " << unitprice;
      if( nr != 1 )
         out << " (" << nr << " times)";

   }  

   price totalprice( ) const { return nr * unitprice; } 
};

inline std::ostream& operator << ( std::ostream& out, const order& ord )
{
   ord. print( out );
   return out;
}

#endif

