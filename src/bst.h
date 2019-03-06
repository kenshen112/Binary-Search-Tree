/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    Create a binary search tree
 ************************************************************************/
#include "bst.h"
#ifndef BST_H
#define BST_H

namespace custom
{

templete <class T>
class BST{

private:
	int numElements;
	BNode <T> *root; //does this need to be a pointer?? Yes, Tim. :)


  public:

	  class iterator; // Always remeber dear knights always forward declare thine classes!

	  iterator find(T itemToFind);
	  iterator begin();
	  iterator end();

	  BST()
	  {
		  root = nullptr;
		  numElements = 0;
	  }

	  BST(BST <T> *rhs)
	  {

	  }


	  BST operator=();

	  int size{ return numElements; }
	  bool empty() { return numElements == 0; }
	  void clear();
	  void insert(T item); // The Big Mac on the plate though this won't be too difficult equation wise if (item > left == true)  isRight = true;
	  void erase(iterator it);
	  void deleteNode(BNode <T> *nodeToDelete, bool isRight);
	  void deleteBinaryTree(BNode <T> *deletor);
	  void copyBinaryTree(BNode<T> *copySource, BNode <T> *copyDest);
	  ~BST()
	  {

	  }

};
   
/*************************************************
 *BST CONSTRUCTOR
 *assigns default values to the objects
 ************************************************/
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
