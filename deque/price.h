
#ifndef PRICE_
#define PRICE_ 

struct price
{
   double p;

   price( ) 
      : p(0)
   { }

   // Keyword 'explicit' prevents accidental implicit conversions:

   explicit price( double p )
      : p(p)
   { }

   void print( std::ostream& out ) const
   {
      out << p << "tt";
   }

   price& operator += ( price other ) { p += other.p; return *this; }
   price& operator -= ( price other ) { p -= other.p; return *this; }
   price& operator *= ( double d ) { p *= d; return *this; }
   price& operator /= ( double d ) { p /= d; return *this; }

};

inline price operator + ( price p1, price p2 ) { return price( p1.p + p2.p ); }
inline price operator - ( price p1, price p2 ) { return price( p1.p - p2.p ); }
inline price operator - ( price p ) { return price( -p. p ); } 

inline price operator * ( price p, double d ) { return price( p.p * d ); }
inline price operator * ( double d, price p ) { return price( d * p.p ); }
inline price operator / ( price p, double d ) { return price( p.p / d ); }


inline bool operator < ( price p1, price p2 ) { return p1.p < p2.p; }
inline bool operator > ( price p1, price p2 ) { return p1.p > p2.p; }
inline bool operator <= ( price p1, price p2 ) { return p1.p <= p2.p; }
inline bool operator >= ( price p1, price p2 ) { return p1.p >= p2.p; }
inline bool operator == ( price p1, price p2 ) { return p1.p == p2.p; }
inline bool operator != ( price p1, price p2 ) { return p1.p != p2.p; }

inline price operator "" _kzt( long double d ) { return price(d); }
inline price operator "" _kzt( unsigned long long int i ) { return price(i); }
inline price operator "" _tt( long double d ) { return price(d); }
inline price operator "" _tt( unsigned long long int i ) { return price(i); } 

inline std::ostream& operator << ( std::ostream& out, price p )
{
   p. print( out );
   return out; 
}

#endif

