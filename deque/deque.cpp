
#include "deque.h"
#include <utility>

void deque::check_invariant( ) const
{
   if( deq_size == 0 )
   {
      if( deq_front )
         throw std::logic_error( "size == 0, but front != nullptr" );
      if( deq_back )
         throw std::logic_error( "size == 0, but back != nullptr" );
   }
   else
   {
      size_t truesize = 0;

      if( deq_front -> prev )
         throw std::logic_error( "prev of front not nullptr " );
      if( deq_back -> next )
         throw std::logic_error( "next of back not nullptr" );

      for( auto p = deq_front; p; p = p -> next ) 
      {
         // If p has a next, its prev must be p.
         // If p has no next, p must be the back of the deque. 

         if( p -> next )
         {
            if( p -> next -> prev != p )
               throw std::logic_error( "prev or next is wrong" );
         }
         else
         {
            if( p != deq_back )
               throw std::logic_error( "deq_back is wrong" );
         } 
         ++ truesize;
      } 

      if( truesize != deq_size )
         throw std::logic_error( "deq_size is wrong" ); 
   }
}


deque::deque( ) noexcept
: deq_size(0), deq_front(nullptr), deq_back(nullptr) { }



void deque::push_back( const valtype& val )
{
   node* new_node = new node (val);
   if (this->deq_back) {
      this->deq_back->next = new_node;
      new_node->prev = this->deq_back;
      this->deq_back = new_node;
   } 
   else {
      this->deq_front = new_node;
      this->deq_back = new_node;
   }
   this->deq_size ++;
}

void deque::pop_back( )
{
   if (this->deq_size == 0) {
      throw std::logic_error( "size == 0!" );
   }
   if (this->deq_size == 1) {
      delete deq_front;
      deq_front = nullptr;
      deq_back = nullptr;
   }
   else {
      delete std::exchange(this->deq_back, this->deq_back->prev);
      this->deq_back->next = nullptr;
   }
   this->deq_size --;
}

const deque::valtype& deque::back( ) const
{
   if (this->deq_size == 0) {
      throw std::logic_error( "size == 0!" );
   }
   return this->deq_back->val;
}

deque::valtype& deque::deque::back( )
{
   if (this->deq_size == 0) {
      throw std::logic_error( "size == 0!" );
   }
   return this->deq_back->val;
}

// front methods:

void deque::push_front( const valtype& val ) 
{  
   node* new_node = new node (val);
   if (this->deq_front) {
      this->deq_front->prev = new_node;
      new_node->next = this->deq_front;
      this->deq_front = new_node;
   }
   else{
      this->deq_front = new_node;
      this->deq_back = new_node;  
   }
   this->deq_size ++;
}

void deque::pop_front( )
{

   if (this->deq_size == 0) {
      throw std::logic_error( "size == 0!" );
   }
   if (this->deq_size == 1) {
      delete deq_front;
      deq_front = nullptr;
      deq_back = nullptr;
   }
   else {
      delete std::exchange(this->deq_front, this->deq_front->next);
      this->deq_front->prev = nullptr;
   }
   this->deq_size --;
}


const deque::valtype& deque::front( ) const
{
   if (this->deq_size == 0) {
      throw std::logic_error( "size == 0!" );
   }
   else return this->deq_front->val;
}

deque::valtype& deque::deque::front( )
{
   if (this->deq_size == 0) {
      throw std::logic_error( "size == 0!" );
   }
   else return this->deq_front->val;
}

void deque::print( std::ostream& out ) const
{
   node* current_node = this->deq_front;
   out << "[ ";
   bool check = 0;
   while (current_node) {
      if (check == 0) {
         out << current_node->val;
         check = 1;
      }
      else {
         out << ", " << current_node->val;
      }
      current_node = current_node->next;
   }
   out << " ]";
}


deque::deque( const deque& q ) : deque( )
{
   this->deq_size = 0;
   this->deq_front = nullptr;
   this->deq_back = nullptr;
   
   node* current_node = q.deq_front;

   while (current_node) {
      this->push_back(current_node->val);
      current_node = current_node->next;
   }

}

deque::deque( std::initializer_list< valtype > init )
   : deque( ) 
{
   for (auto value : init) {
      this->push_back(value);
   }
}

deque:: ~deque( ) 
{
   node* current_node = this->deq_front;

   while (current_node) {
      delete std::exchange(current_node, current_node->next);
   }

   deq_size = 0;

}


void deque::reset_front( size_t s )
{
   if (this->deq_size < s) {
      throw std::logic_error( "The deque size is less than the given number!" );
   }
   while (this->deq_size > s) {
      this->pop_front();
   }
}

void deque::reset_back( size_t s )
{
   if (this->deq_size < s) {
      throw std::logic_error( "The deque size is less than the given number!" );
   }
   while (this->deq_size > s) {
      this->pop_back();
   }
}


const deque& deque::operator = ( const deque& q )
{
   if (this == &q) {
      return *this;
   }
   this->reset_back(0);

   node* current_node = q.deq_front;

   while (current_node) {
      this->push_back(current_node->val);
      current_node = current_node->next;
   }

   return *this;
}

size_t deque::size( ) const 
{
   return this->deq_size;
}

bool deque::empty( ) const
{
   return (this->deq_size == 0);
}


deque::deque( deque&& q ) noexcept 
:  deq_size( q.deq_size ),
   deq_front( q.deq_front ),
   deq_back( q.deq_back )
{
   q.deq_size = 0;
   q.deq_front = nullptr;
   q.deq_back = nullptr;
}


const deque& deque::operator = ( deque&& q ) noexcept
{

   this->reset_back (0);
   this->deq_front = q.deq_front;
   this->deq_back = q.deq_back;
   this->deq_size = q.deq_size;

   q.deq_front = nullptr;
   q.deq_back = nullptr;
   q.deq_size = 0;

   return *this;
}


