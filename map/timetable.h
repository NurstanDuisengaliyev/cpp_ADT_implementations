
// Written by Hans de Nivelle, February 2019, for CSCI 152.

#ifndef TIMETABLE_
#define TIMETABLE_  

#include <iostream>
#include <list>
#include <map>
#include <iomanip>

class timetable
{
   std::string algname; 
      // Name of algorithm used.

   std::map< size_t, double > times;
      // Maps input sizes to run times.

public: 
   timetable( ) = delete;  
      // There is no default constructor,
      // because you have to give a name. 

   // Examples: timetable tab( "heapsort" );
   // timetable tab( "quicksort 1.0" );

   timetable( const std::string& algname )
      : algname( algname )
   { }

   timetable( const char* algname, const std::list< double > & version = { } )
      : algname( std::string( algname ))
   { }

   void insert( size_t inputsize, double runtime )
   {
      times[ inputsize ] = runtime;
   }

   size_t size( ) const 
   {
      return times. size( ); 
   }

   void clear( ) 
   {
      times. clear( );
   }

   double totaltime( ) const
   {
      double t = 0;
      for( const auto& p : times )
         t += p. second;
      return t;
   }

   std::ostream& print( std::ostream& ) const;   

   using const_iterator = 
      std::map< size_t, double > :: const_iterator; 

   const_iterator begin( ) const { return times. begin( ); }
   const_iterator end( ) const { return times. end( ); } 
};


inline std::ostream& operator << ( std::ostream& out, const timetable& t )
{
   return t. print( out );
}

#endif 


