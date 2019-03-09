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
      BNode <T> *root;
      
      
     public:
      
      class iterator; // Always remeber dear knights always forward declare thine classes!
      
      iterator find(T itemToFind);
      iterator begin();
      iterator end();
	  iterator rbegin();
	  iterator rend();


      BST()
      {
         root = nullptr;
         numElements = 0;
      }
      ~BST()
      {
         //deleteBinaryTree(root);
		 numElements = 0;
      }
      BST(const BST <T> *rhs)
       {
          
          BST <T> *destination = new BST<T> *;
          
          if(rhs == nullptr)
          {
             destination->root = nullptr;
          }
          
          numElements = rhs.numElements;
          
          for(BST <T> :: iterator it = rhs.begin(); it != rhs.end(); ++it)
          {
             destination.insert(*it);
          }
          
       }

      BST operator = (const BST <T> *rhs)
      {
         
         if(rhs == nullptr)
         {
            return nullptr;
         }
         
         BST <T> * destination = new BST <T>(rhs->root);
         numElements = rhs.numElements;
         
         for(BST <T> :: iterator it = rhs.begin(); it != rhs.end(); ++it)
         {
            destination.insert(*it);
         }
         
         return *this;
           
      }
      
      int size()   { return numElements; }
      bool empty() { return numElements == 0; }
      void clear();
      void insert(T item); // The Big Mac on the plate though this won't be too difficult equation wise if (item > left == true)  isRight = true;
      void erase(iterator it);
      void deleteNode(BNode <T> *nodeToDelete, bool isRight);
      void deleteBinaryTree(BNode <T> *deletor);
      void copyBinaryTree(BNode<T> *copySource, BNode <T> *copyDest);
	  void balence(BST<T>* tree);

	  };

    template <class T>
       class BST <T> ::iterator
    {

      public:
       BNode <T> *p;


       //Constructors/Destructor
       iterator()
       {
          p = nullptr;
       }

       iterator(BNode <T> *pNewit)
       {
          this->p = pNewit;

       }

       iterator(const iterator &rhs)
       {
          this->p = rhs.p;
       }

	   
	   bool operator!=(iterator it)
	   {
		   return *this != it;
	  
	   }


       //OPERATORS, delcare em, stub em, define em right here.
       // even you couldn't say no to that.
       //                     OH YES WE COULD

       iterator operator++();
       iterator operator++(int);//postfix
       iterator operator--();
       iterator operator--(int);//postfix
	   
	   T& operator*()
	   {
		   return p->data;
	   }
       
    };
       

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. 
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
   template <class T>
      typename BST<T>::iterator BST<T>::iterator::operator--()
   {
		  BNode<T> *pNode = p;


      // do nothing if we have nothing
      if (pNode == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left node, take it
      if (nullptr != pNode->pLeft)
      {
         // go left
         pNode = pNode->pLeft;
         
         //jig right - there might be more right-most children
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

/**************************************************
 * BST ITERATOR :: DECREMENT POSTFIX
 *     advance by one.
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
   template <class T>
      typename BST<T>::iterator BST<T>::iterator::operator--(int)
   {
      BNode<T> *pNode = p;
      
      
      // do nothing if we have nothing
      if (pNode == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left node, take it
      if (nullptr != pNode->pLeft)
      {
         // go left
         pNode = pNode->pLeft;
         
         //jig right - there might be more right-most children
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
   
/**************************************************
* Reverse Begin
***************************************************/

      template <class T>
	  typename BST<T>::iterator BST<T>::rbegin()	  
	  { 
		   return iterator(nullptr);		  
	  }
	   
	  template <class T>  
	  typename BST<T>::iterator BST<T>::rend()
	   {
		   return iterator(root);
	   }

/**************************************************
 *BST ITERATOR::INCREMENT PREFIX
 *so I copied the decrement operator above and
 *  just switched pLeft to pRight and vice versa
 *************************************************/
   template <class T>
   typename BST <T>::iterator BST<T>::iterator::operator++()
   {
	   BNode<T> *pNode = root;


      // do nothing if we have nothing
      if (pNode == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left *right* node, take it
      if (nullptr != pNode->pRight)
      {
         // go left *right*
         pNode = pNode->pRight;
            
         //jig right *left?* - there might be more right*left*-most children
         while (pNode->pLeft)
            pNode = pNode->pLeft;
         return *this;
      }
      
      // there are no left *right* children, the right *left* are done
      assert(nullptr == pNode->pRight);
      BNode<T> * pSave = pNode;
      
      // go up
      pNode = pNode->pParent;
      
      // if the parent is the NULL, we are done!
      if (nullptr == pNode)
         return *this;
      
      // if we are the right*left*-child, got to the parent.
      if (pSave == pNode->pLeft)
         return *this;
      // we are the left*right*-child, go up as long as we are the left *right* child!
      while (nullptr != pNode && pSave == pNode->pRight)
      {
         pSave = pNode;
         pNode = pNode->pParent;
      }
      
      return *this;
   }

/**************************************************
 *BST ITERATOR::INCREMENT POSTFIX
 *so I copied the decrement operator above and
 *  just switched pLeft to pRight and vice versa
 *************************************************/
   template <class T>
      typename BST <T>::iterator BST<T>::iterator::operator++(int)
   {
      BNode<T> *pNode = p;
      
      
      // do nothing if we have nothing
      if (pNode == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left *right* node, take it
      if (nullptr != pNode->pRight)
      {
         // go left *right*
         pNode = pNode->pRight;
         
         //jig right *left?* - there might be more right*left*-most children
         while (pNode->pLeft)
            pNode = pNode->pLeft;
         return *this;
      }
      
      // there are no left *right* children, the right *left* are done
      assert(nullptr == pNode->pRight);
      BNode<T> * pSave = pNode;
      // go up
      pNode = pNode->pParent;
      
      // if the parent is the NULL, we are done!
      if (nullptr == pNode)
         return *this;
      
      // if we are the right*left*-child, got to the parent.
      if (pSave == pNode->pLeft)
         return *this;
      // we are the left*right*-child, go up as long as we are the left *right* child!
      while (nullptr != pNode && pSave == pNode->pRight)
      {
         pSave = pNode;
         pNode = pNode->pParent;
      }
      
      return *this;
   }

/****************************************************
 *DELETE BINARY TREE
 *deletes an entire BST
 ****************************************************/
   void BST <T> :: deleteBinaryTree(BNode <T> *deletor)
   {
      
      if(deletor == nullptr)
      {
         return;
      }
      
      deleteBinaryTree(deletor->pLeft);
      deleteBinaryTree(deletor->pRight);

      delete deletor;

      deletor = nullptr;
      if(deletor == NULL)
      {
         std::cerr << "its null now\n";
      }
      
      
   }   

   
   template<class T>
   void BST<T>::clear()
   {
	   deleteBinaryTree(root);
	   numElements = 0;
   }

   template<class T>
   void BST<T>::insert(T item)
   {   
	   if (root == nullptr) // case 1 tree is black
	   {
		   root = new BNode<T>(item); // This node is black yo!
		   root->black = true;
		   root->parent = true;
		   numElements++;
      }
      
      if (item > root->data)
      {
         root->pRight = new BNode<T>(item); // need a loop to search for nullptr or something along those lines.
		 numElements++;
      }
      
      else if (item < root->data)
      {
         root->pLeft = new BNode<T>(item);
		 numElements++;
      }               
   }

/*********************************************
 *ERASE
 *erases a node from the BST
 ********************************************/
   template <class T>
      void BST<T>::erase(iterator it)
   {

      //CASE 1: NO children
      if (it->p->pRight == nullptr && it->p->pLeft == nullptr) // there aint no children up in here mmm hmmm das what i'm sayin.
      {
         
         if (it->p->pParent != nullptr && it->p->pParent->pRight == it->p)
         {//we are on the right of a parent
            it->p->pParent->pRight = nullptr;
            delete it->p;
            it->p = nullptr;
         }
         else if (it->p->pParent != nullptr && it->p->pParent->pLeft == it->p)
         {//we are on the left of a parent
            it->p->pParent->pLeft = nullptr;
            delete it->p;
            it->p = nullptr;
         }
         else if (it->p->pParent == nullptr)
         {//there is no parent
            delete it->p;
            it->p = nullptr;
         }
      }

      //CASE 2: One Child
      if (it->p->pRight != nullptr && it->p->pLeft == nullptr)
      {//we have a left child, but no right children
         it->p->pRight->pParent = it->p->pParent;
         
         if (it->p->pParent != nullptr && it->p->pParent->pRight == it->p)
         {
            it->p->pParent->pRight = it->p->pRight;
         }
         
         if (it->p->pParent != nullptr && it->p->pParent->p->pLeft == it->p)
         {
            it->p->pParent->pLeft = it->p->pRight;
         }
      }
      
      if (it->p->pRight == nullptr && it->p->pLeft != nullptr)
      {//we have a right child but not a left one
         it->p->pLeft->pParent = it->p->pParent;
         
         if (it->p->pParent != nullptr && it->p->pParent->pRight == it->p)
         {
            it->p->pParent->pRight = it->p->pLeft;
         }
         
         if (it->p->pParent != nullptr && it->p->pParent->pLeft == it->p)
         {
            it->p->pParent->p->pLeft = it->p->pLeft;
         }
      }
      
      //CASE 3: Two Children
      if(it->p->pRight != nullptr && it->p->pLeft != nullptr)
      {
         iterator ios = it;
         ++ios;
         assert(ios->p->pLeft == nullptr); //ios should NOT have a left child

         if(ios->p->pRight != nullptr)
         {
            it->p->pRight->pParent = ios->p; //change it->p to ios
            ios->p->pRight->pParent = ios->pRight; //move ios's right child to ios's spot
            delete it->p;
         }
         else
         {
            it->p->pRight->pParent = ios->p;
            delete it->p;
         }
      }
   }

	  template<class T>
	 void BST<T>::balence(BST<T>* tree)
	  {
	  
		 if (tree->root == nullptr) // case 1 tree is black
		 {
			 tree->root->black = true;
			 tree->root->parent = true;
		 }

		 //   A Baisc structure of Red Black Balencing 	   
		 if (tree->black == true && tree->parent == true) //case 2 Might we be missing a circumstance here?
		 {
			 tree->root->pParent->red = true;
		 }


		 if (tree->root->black && root->pParent->red && root->pRight->red) // Case 3 the recolor
		 {
			 tree->root->black = false;
			 tree->root->red = true;
			 tree->root->pParent->red = false;
			 tree->root->pParent->black = true;
			 tree->root->pRight->red = false;
			 tree->root->pRight->black = true;
		 } 
	 }

	template<class T>
	typename BST<T>::iterator BST<T>::begin()
	 {
		return iterator(root);
	}

	template<class T>
	typename BST<T>::iterator BST<T>::end()
	{
		return iterator(nullptr);
	}

   
/************************************************
* Find:
* Searches the Binary Search Tree for an item.
************************************************/
	  template <class T>
	  typename BST<T>::iterator find(T itemToFind) {
		  for (typename BST<T>::iterator it = itemToFind; it; it = it->p->pNext)
		  {
			  if (it->p->data == itemToFind)
			  {
				  return it;
			  }
		  }

		  return nullptr;
	  }


} // namespace custom

#endif // BST_H
