/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    Create a binary search tree
 ************************************************************************/
#include "bnode.h"
#ifndef BST_H
#define BST_H

namespace custom
{

template <class T>
class BST{

  public:
   BST();
   BST(const BST <T> & rhs);
   ~BST();
   BST & operator= (const BST & rhs) throw (const char *);
   
   
  private:
   BNode <T> * root; 
   

};
   
/*************************************************
 *BST CONSTRUCTOR
 *assigns default values to the objects
 ************************************************/
BST()
{
   root = nullptr;
}

/*************************************************
*BST DESTRUCTOR
*destroys each node using deleteBTree from bnode.h 
************************************************/
~BST()
{
   deleteBTree(root);
}

/*************************************************
 *BST COPY CONSTRUCTOR
 *copies data from one BST to another
************************************************/
template <class T>
BST(const BST <T> & rhs)
{
   if(rhs == nullptr)
   {
      return nullptr;
   }

   BST <T> *destination = new BST<T>(rhs->root)
}
/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. 
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
   // do nothing if we have nothing
   if (NULL == pNode)
      return *this;

   // if there is a left node, take it
   if (NULL != pNode->pLeft)
   {
      // go left
      pNode = pNode->pLeft;

      // jig right - there might be more right-most children
      while (pNode->pRight)
         pNode = pNode->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == pNode->pLeft);
   BNode * pSave = pNode;

   // go up
   pNode = pNode->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == pNode)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == pNode->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != pNode && pSave == pNode->pLeft)
   {
      pSave = pNode;
      pNode = pNode->pParent;
   }

   return *this;
}

} // namespace custom

#endif // BST_H
