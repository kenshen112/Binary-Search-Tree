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
      
     private:
      int numElements;
      BNode <T> *root; //does this need to be a pointer?? Yes, Tim. :)
      
      
     public:
      
      class iterator; // Always remeber dear knights always forward declare thine classes!
      
      iterator find(T itemToFind);
      iterator begin();
      iterator end();
      
      BST();
      ~BST();
      BST(const BST <T> *rhs);
      BST operator = (const BST <T> *rhs);
      
      int size()   { return numElements; }
      bool empty() { return numElements == 0; }
      void clear();
      void insert(T item); // The Big Mac on the plate though this won't be too difficult equation wise if (item > left == true)  isRight = true;
      void erase(iterator it);
      void deleteNode(BNode <T> *nodeToDelete, bool isRight);
      void deleteBinaryTree(BNode <T> *deletor);
      void copyBinaryTree(BNode<T> *copySource, BNode <T> *copyDest);
      
   };
   
/*************************************************
 *BST CONSTRUCTOR
 *assigns default values to the objects
 ************************************************/
BST()
{
   root = nullptr;
   numElements = 0;
}

/*************************************************
*BST DESTRUCTOR
*destroys each node using deleteBTree from bnode.h 
************************************************/
~BST()
{
   deleteBinaryTree(root);
}

/*************************************************
 *BST COPY CONSTRUCTOR
 *copies data from one BST to another
 ************************************************/
template <class T>
   BST <T> (const BST <T> & rhs)
{
   if(rhs == nullptr)
   {
      return nullptr;
   }
   
   
   BST <T> *destination = new BST<T>(rhs->root);
   numElements = rhs.numElements;
   
   
}
/*************************************************
 *BST OPERATOR =
 *assignment operator overloader
 ************************************************/
template <class T>
   BST operator=(const BST <T> & rhs)
   {
      return *this;
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
      if (pNode == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left node, take it
      if (nullptr != pNode->pLeft)
      {
         // go left
         pNode = pNode->pLeft;
         
         //        jig right - there might be more right-most children
         while (pNode->pRight)
            pNode = pNode->pRight;
         return *this;
      }
      
      // there are no left children, the right are done
      assert(nullptr == pNode->pLeft);
      BNode<T> * pSave = pNode;

      // go up
      pNode = pNode->pParent;

      // if the parent is the NULL, we are done!
      if (nullptr == pNode)
         return *this;

      // if we are the right-child, got to the parent.
      if (pSave == pNode->pRight)
         return *this;

      // we are the left-child, go up as long as we are the left child!
      while (nullptr != pNode && pSave == pNode->pLeft)
      {
         pSave = pNode;
         pNode = pNode->pParent;
      }
      
      return *this;
   }
   
   template <class T>
      void BST<T>::erase(iterator it)
   {
      
      if (it.pRight == nullptr && it.pLeft == nullptr) // there aint no children up in here mmm hmmm das what i'm sayin.
      {
         if (it.pParent != nullptr && it.pParent.pRight == it)
         {
            it.pParent.pRight = nullptr;
         }
         
         else if (it.pParent != nullptr && it.pParent.pLeft == it)
         {
            it.pParent.pRight = nullptr;
         }
      }
      
      if (it.pRight != nullptr && it.pLeft == nullptr)
      {
         it.pRight.pParent = it.pParent;
         
         if (it.pParent != nullptr && it.pParent.pRight == it)
         {
            it.pParent.pRight = it.pRight;
         }
         
         if (it.pParent != nullptr && it.pParent.pLeft == it)
         {
            it.pParent.pLeft = it.pRight;
         }
      }
      
      if (it.pRight == nullptr && it.pLeft != nullptr)
      {
         it.pLeft.pParent = it.pParent;
         
         if (it.pParent != nullptr && it.pParent->pRight == it)
         {
            it.pParent->pRight = it.pLeft;
         }
         
         if (it.pParent != nullptr && it.pParent->pLeft == it)
         {
            it.pParent.pLeft = it.pLeft;
         }
      }
      
   }
   
} // namespace custom

#endif // BST_H
