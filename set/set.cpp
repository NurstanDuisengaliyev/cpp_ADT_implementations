
#include "set.h"


int case_insensitive_cmp::operator( ) ( const std::string& s1, const std::string& s2 ) const
{
   for (size_t i = 0; i < std::min(s1.size(), s2.size()); i ++) {
      char a = s1[i], b = s2[i];

      if (a >= 'A' && a <= 'Z') a = char((int)a + 32);
      if (b >= 'A' && b <= 'Z') b = char((int)b + 32);


      if (a == b) continue;
      if (a < b) return -1;
      else return 1;

   }
   if (s1.size() == s2.size()) return 0;
   else if (s1.size() < s2.size()) return -1;
   else return 1;
}


const treenode* find( const treenode* n, const treenode::valtype& val )
{
   treenode::valcmp cmp;
   //case_insensitive_cmp cmp;
   const treenode* root = n;
   while (root != nullptr) {
      if (cmp (root->val, val) == 0) {
         return root;
      }
      if (cmp (root->val, val) < 0) {
         root = root->right;
      }
      else {
         root = root->left;
      }
   }
   return nullptr;
}


treenode** find( treenode** n, const treenode::valtype& val )
{
   treenode::valcmp cmp;
   //case_insensitive_cmp cmp;
   treenode** root = n;

   while((*root) != nullptr) {   
      if (cmp ((*root)->val, val) == 0) return root;
      if (cmp ((*root)->val, val) < 0) {
         root = &((*root)->right);
      }
      else {
         root = &((*root)->left); 
      }
   }
   return root;
}

size_t size( const treenode* n )
{
   if (n == nullptr) return 0;
   return 1 + ::size(n->left) + ::size(n->right);
}

size_t height( const treenode* n )
{
   if(n == nullptr) return 0;

   size_t left_h = ::height(n->left);
   size_t right_h = ::height(n->right);

   return 1 + (left_h > right_h ? left_h : right_h);
}

void deallocate( treenode* n )
{
   if (n == nullptr) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
}


treenode* makecopy( const treenode* n ) 
{  
   if (n == nullptr) return nullptr;

   treenode* new_root = new treenode(n->val);

   new_root->left = makecopy(n->left);
   new_root->right = makecopy(n->right);

   return new_root;
}


// Step to the right as long as possible. When we get
// stuck, we are in the rightmost node. Remove it, and
// return it. (Don't delete it.)
// *from cannot be the empty tree.

treenode* extractrightmost( treenode** from )
{
   while( (*from) -> right )
      from = & (*from) -> right;

   treenode* n = *from;
   *from = (*from) -> left;
   return n;
}

void print( std::ostream& out, const treenode* n, unsigned int indent )
{

   for( unsigned int i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> val ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}


// Both the upperbound and the lowerbound are strict.
// We use pointers, so that they can be absent. 
// Of course, this is a tasteless way of dealing with partiality.

void checkbetween( const treenode* n, 
                   const treenode::valtype* lowerbound, 
                   const treenode::valtype* upperbound ) 
{
   treenode::valcmp cmp;

   while(n) 
   {
      if( lowerbound && cmp( *lowerbound, n -> val ) >= 0 ) 
      {
         std::cout << "value " << ( n -> val );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         throw std::runtime_error( "tree not correct" ); 
      }

      if( upperbound && cmp( *upperbound, n -> val ) <= 0 ) 
      {
         std::cout << "value " << ( n -> val );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         throw std::runtime_error( "tree not correct" );  
      }

      checkbetween( n -> left, lowerbound, &( n -> val ));
      lowerbound = & ( n -> val );
      n = n -> right;
   }
} 


unsigned int log_base2( size_t s )
{
   if (s == 0) return 0;
   size_t cnt = 0;
   while (s > 0) {
      s /= 2;
      cnt ++;
   }
   return cnt - 1;
}

bool set::contains( const valtype& val ) const
{ 

   const treenode* node = find(tr, val);

   if (node == nullptr) {
      return false; 
   }
   else {
      return true;
   }
}

 
bool set::insert( const valtype& val )
{
   treenode** node = find (&tr, val);

   if (*node == nullptr) {
      *node = new treenode(val);
      return true; 
   }
   else {
      return false;
   }
}


bool set::remove( const valtype& val )
{
   treenode** node = find (&tr, val);

   if (*node == nullptr) {
      return false; 
   }
   else {

      if ((*node)->left == nullptr && (*node)->right == nullptr) {
         delete *node;
         *node = nullptr;
      }
      else if ((*node)->left && (*node)->right == nullptr) {
         treenode* child_left = (*node)->left;
         delete *node;
         *node = child_left;
      }
      else if ((*node)->left == nullptr && (*node)->right) {
         treenode* child_right = (*node)->right;
         delete *node;
         *node = child_right;
      }
      else {
         // both exist
         treenode* right_most = extractrightmost(&((*node)->left));
         (*node)->val = right_most->val;
         delete right_most;
      }
      return true;
   }
}


size_t set::size( ) const
{
   return ::size( tr );
}

size_t set::height( ) const
{
   return ::height( tr );
}

bool set::empty( ) const
{
   if(tr == nullptr) return true;
   else return false;
}

set:: ~set( )
{
   ::deallocate(tr);
}

void set::clear( )
{
   ::deallocate(tr);
   tr = nullptr;
}

set::set( const set& other ) 
   : tr(::makecopy(other.tr))
{ 

}


set& set::operator = ( const set& other )
{
   if (this == &other) return *this;

   this->clear();

   this->tr = ::makecopy(other.tr);

   return *this;
}



void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


void set::print( std::ostream& out, unsigned int indent ) const
{
   ::print( out, tr, indent );
}

