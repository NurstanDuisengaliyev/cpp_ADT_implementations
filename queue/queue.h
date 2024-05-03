
#ifndef QUEUE_ 
#define QUEUE_

#include <iostream>
#include <initializer_list>

class queue
{
public:
   using valtype = double;
      // Value type in the queue. Don't mention double in the
      // rest of the code, so that it can be replaced. 

   size_t current_capacity;
   valtype* data; 

   size_t current_size;
   size_t current_front; 
      // Front is the point where will be served next.

   // INVARIANT:
   // current_size <= current_capacity
   // current_front < current_capacity
   // 4 <= current_capacity 
   // data is allocated with a memory segment of size current_size.
   // 
   // No two queues share allocated memory.
   // There is no forgotten memory in the system that was allocated by a queue.

   void checkinvariant( ) const;
      // Check the invariants. Use this function in your tests!

   void printstate( std::ostream& ) const;
      // Prints internal state. Use this method for debugging.

   valtype* makecopy( size_t c ) const;
      // Make a copy of our data, in such a way that the
      // front is at index 0 in the copy. 

   void ensure_capacity( size_t c );
      // Ensure that queue has capacity of at least c.

public: 
   queue( );             
      // Constructs empty queue. 

   queue( const queue& q );

   ~queue( );

   const queue& operator = ( const queue& q );

   queue( std::initializer_list< valtype > init );
      // So that you can write q = { 1,2,3 };
      // You can use init. size( ) to see the size, and
      // for( const valtype& val : init ) to go through all
      // elements in the initializer_list.

   void push( const valtype& val );  
   void pop( );

   void clear( );

   const valtype& peek( ) const;

   size_t size( ) const;
   bool empty( ) const;

   void print( std::ostream& out ) const;
      // MUST print [ q0, ... q_{current_size-1} ].
      // Starting with the front.
   
}; 


inline std::ostream& operator << ( std::ostream& out, const queue& q )
   { q. print( out ); return out; } 

#endif

