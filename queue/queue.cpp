
#include "queue.h"
#include <algorithm>

void queue::checkinvariant( ) const
{
   if( current_capacity < 2 )
   {
      std::cout << "current capacity < 2\n";
      printstate( std::cout );
      std::abort( );
   }

   if( current_size > current_capacity )
   {
      std::cout << "current_size > current_capacity\n";
      printstate( std::cout );
      std::abort( );
   }

   if( current_front >= current_capacity )
   {
      std::cout << "current_front >= current_capacity\n";
      printstate( std::cout );
      std::abort( );
   }
}

void queue::printstate( std::ostream& out ) const
{
   size_t current_end = current_front + current_size;
   if( current_end >= current_capacity )
      current_end -= current_capacity;
   
   if( current_front + current_size < current_capacity )
   {
      for( size_t i = 0; i != current_front; ++ i )
         out << ".   ";
      out << "(front)   ";
      for( size_t i = current_front; i != current_end; ++ i )
         out << data[i] << "   ";
      for( size_t i = current_end; i != current_capacity; ++ i )
         out << ".   ";
   }
   else
   {
      for( size_t i = 0; i != current_end; ++ i )
         out << data[i] << "   ";
      for( size_t i = current_end; i != current_front; ++ i )
         out << "X   ";
      out << "(front)   ";
      for( size_t i = current_front; i != current_capacity; ++ i )
         out << data[i] << "   ";
   }
   out << "\n";
}


queue::queue( ):
   current_capacity(4),
   data(new valtype[4]),
   current_size(0),
   current_front(0)
{
}


queue::valtype* queue::makecopy( size_t c ) const
{
   if( c < current_size )
      throw std::logic_error( "makecopy: c is too small" );

   valtype* new_data = new valtype [c];
   size_t current_end = current_front + current_size;
   if (current_end <= current_capacity) { // unwrapped at the end 
      std::copy( (data + current_front), (data + current_end), new_data );
   }
   else { // wrapped at the end 
      std::copy( (data + current_front), (data + current_capacity), new_data );
      current_end -= current_capacity;
      std::copy( data, (data + current_end), (new_data + current_capacity - current_front));
   }
  
   return new_data;
}


void queue::ensure_capacity( size_t c )
{ 
   if (c <= current_capacity) return;
   size_t new_cap = current_capacity;

   while (c > new_cap) {
      new_cap *= 2;
   }

   valtype* new_data = makecopy (new_cap);
   delete[] data;
   data = new_data;
   current_front = 0;
   current_capacity = new_cap;
}
 

void queue::push( const valtype& val )
{  
   ensure_capacity(current_size + 1);
   size_t current_end = current_front + current_size;
   if (current_end < current_capacity) {
      *(data + current_end) = val;
      current_size ++;
   }
   else {
      current_end -= current_capacity;
      *(data + current_end) = val;
      current_size ++;
   }
}


void queue::pop( )
{ 
   if (current_size == 0) {
      throw std::logic_error( "pop: queue is empty" );
   }

   current_front ++;
   current_size --;
   if (current_front == current_capacity) {
      current_front = 0;
   }
}


const queue::valtype& queue::peek( ) const
{ 
   if (current_size == 0) {
      throw std::logic_error( "peek: queue is empty" );
   }
   return *(data + current_front);
}


queue::~queue( )
{ 
   delete[] data;
}


queue::queue( const queue& q ):
   current_capacity(q.current_capacity),
   data(q.makecopy(q.current_capacity)),
   current_size(q.current_size),
   current_front(0)
{
}


const queue& queue::operator = ( const queue& q )
{ 
   if (this != &q) {
      delete[] this->data;
      this->current_capacity = q.current_capacity;
      this->current_size = q.current_size;
      this->current_front = 0;
      this->data = q.makecopy(q.current_capacity);
   }
   return *this;
}


void queue::print( std::ostream& out ) const
{
   out << "[ "; 
   for (size_t i = 0; i < current_size; i ++) {
      size_t pos = current_front + i;
      if (pos >= current_capacity) {
         pos -= current_capacity;
      }
      out << *(data + pos);
      if (i != current_size - 1) {
         out << ", ";
      }
   }
   out << " ]";
}


void queue::clear( )
{ 
   current_front = 0;
   current_size = 0;
   
}


size_t queue::size( ) const
{ 
   return current_size;
}


bool queue::empty( ) const
{ 
   if (current_size == 0) return true;
   else return false;
} 

queue::queue( std::initializer_list< valtype > values ) : 
   current_capacity((values.size() > 4 ? values.size() : 4)),
   current_size(values.size()),
   current_front(0)
{
   data = new valtype [(values.size() > 4 ? values.size() : 4)];
   std::copy(values.begin(), values.end(), data);
}


