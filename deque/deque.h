
#ifndef DEQUEUE_ 
#define DEQUEUE_  

#include <iostream>
#include <initializer_list>

#include "order.h"

class deque
{
   using valtype = double;

   struct node
   {
      valtype val;
      node* prev;  
      node* next;     

      node( const valtype& val, node* prev = nullptr, node* next = nullptr ) :
         val( val ), 
         prev( prev ),  
         next( next )  
      { } 

   };

   size_t deq_size; 

   node* deq_front;       
   node* deq_back; 
      // The fields are preceeded by deq_ to avoid clashes
      // with the interface methods. 

      // Class invariant:
      // 
      // If deq_size > 0, then
      //    both deq_front and deq_back are not nullptr,  
      //    deq_front starts a linked list of size deq_size, 
      //    connected through the next pointers.
      //    deq_back also starts a linked list of size deq_size, connected
      //    by the prev pointers. 
      //    The two linked lists are reversals of each other.
      // 
      // If deq_size == 0, then deq_front == deq_back == nullptr.
      //
      // Global Invariant :  A deque never shares nodes with another deque,
      // or any other data structure.

   void check_invariant( ) const;
      // You can use this method when testing, but be sure that 
      // your final submission does not call this method anywhere
      // in file deque.cpp, because it is O(n). 
      
public: 
   deque( ) noexcept;
      
   deque( const deque& q );
   const deque& operator = ( const deque& q );
   ~deque( );

   deque( std::initializer_list< valtype > init );

   void push_front( const valtype& val );  
   void push_back( const valtype& val );

   void pop_front( );
   void pop_back( );

   void reset_front( size_t s );
   void reset_back( size_t s );
     
   void clear( ) { reset_front(0); }

   const valtype& front( ) const;
   valtype& front( ); 
   const valtype& back( ) const;
   valtype& back( );

   size_t size( ) const;
   bool empty( ) const;  

   operator bool( ) const { return ! empty( ); }
 
   deque( deque&& q ) noexcept;
   const deque& operator = ( deque&& q ) noexcept;

   void print( std::ostream& out ) const;
      // Print the deque starting at front.
 
   friend int main( int argc, char* argv[] );
}; 


inline 
std::ostream& operator << ( std::ostream& out, const deque& deq )
{
   deq. print( out );
   return out;
}

#endif


