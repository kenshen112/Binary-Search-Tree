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
         deleteBinaryTree(root);
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

       iterator operator = (const iterator &rhs)
       {
          std::cerr << "iterator assignment operator\n";
          return this->p = rhs.p;
       }

	   
       bool operator!=(iterator it)
       {
          std::cerr << "not equeals operator\n";
          return this->p != it.p;
	  
       }
       
       bool operator==(iterator it)
       {
          return this->p == it.p;
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
          std::cerr << "we are in the dereference operator\n";
          if(p)
          {
             return p->data;
          }
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
      if(root == nullptr)
      {
         return iterator(nullptr);
      }
      BNode <T> *pNew;
      pNew = root;
      
      while(pNew->pRight)
      {
         pNew = pNew->pRight;
      }
      
      return iterator (pNew);
      
   }
   
   template <class T>  
      typename BST<T>::iterator BST<T>::rend()
   {
      return iterator(nullptr);
   }
   
/**************************************************
 *BST ITERATOR::INCREMENT PREFIX
 *so I copied the decrement operator above and
 *  just switched pLeft to pRight and vice versa
 *************************************************/
   template <class T>
   typename BST <T>::iterator BST<T>::iterator::operator++()
   {
      BNode<T> *pNode = p;

	  std::cerr << "MMM Prefix Donught" << std::endl;

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
      
      return pNode;
   }

/**************************************************
 *BST ITERATOR::INCREMENT POSTFIX
 *so I copied the decrement operator above and
 *  just switched pLeft to pRight and vice versa
 *************************************************/
   template <class T>
      typename BST <T>::iterator BST<T>::iterator::operator++(int)
   {
    
		  std::cerr << "MMM Postfix donught" << std::endl;

      // do nothing if we have nothing
      if (p == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left *right* node, take it
      if (nullptr != p->pRight)
      {
         // go left *right*
         p = p->pRight;
         
         //jig right *left?* - there might be more right*left*-most children
         while (p->pLeft)
            p = p->pLeft;
         return *this;
      }
      
      // there are no left *right* children, the right *left* are done
      assert(nullptr == p->pRight);
      BNode<T> * pSave = p;
      // go up
      p = p->pParent;
      
      // if the parent is the NULL, we are done!
      if (nullptr == p)
         return *this;
      
      // if we are the right*left*-child, got to the parent.
      if (pSave == p->pLeft)
         return *this;
      // we are the left*right*-child, go up as long as we are the left *right* child!
      while (nullptr != p && pSave == p->pRight)
      {
         pSave = p;
         p = p->pParent;
      }
      
      return p;
   }

/****************************************************
 *DELETE BINARY TREE
 *deletes an entire BST
 ****************************************************/
template <class T>
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

   /***************************************************
    * INSERT FOR BST
    ************************************************/
   template<class T>
      void BST<T>::insert(T item)
   {
      BNode <T> * pNew;
      try
      {
         //make a new node
         pNew = new BNode <T> (item);
      }
      catch (std::bad_alloc)
      {
         throw "Error: Unable to allocate a node";
      }
      
      //if the tree is currently empty
      if (root == nullptr) // case 1 tree is black
      {
         root = pNew; // This node is black yo!
         root->black = true;
         root->parent = true;
         numElements++;
         return;
      }
      
      //another pointer, to keep track of where we are as we find a home for pNew
      BNode <T> * pPlace = root;
      bool home = false; //to keep track of if we have found what we are looking for
      bool left; //to tell us if we are adding left or right
      
      while(!home)
      {
         if(item <= pPlace->data) //otherwise do we need to go left?
         {
            if(pPlace->pLeft == nullptr)
            {
               home = true;
               left = true;
			   pPlace->pLeft = pNew;
            }
            else
               pPlace = pPlace->pLeft;
         }
         else if(item >= pPlace->data) //or right?
         {
            if(pPlace->pRight == nullptr)
            {
               home = true;
               left = false;
			   pPlace->pRight = pNew;
            }
            else
               pPlace = pPlace->pRight;
         }
      }
      //attach the pointers to link the new item into the tree.
      
      if(left)
      {
         pPlace->pLeft = pNew;
         pNew->pParent = pPlace;
      }
      else
      {
         pPlace->pRight = pNew;
         pNew->pParent = pPlace;
      }
      numElements++;
      
      
/*      if (item > root->data)
      {
         BNode <T> * pNew = new BNode<T>(item);
         numElements++;
      }
      
      else if (item < root->data)
      {
         root->pLeft = new BNode<T>(item);
         numElements++;
      }*/         
   }

/*********************************************
 *ERASE
 *erases a node from the BST
 ********************************************/
   template <class T>
      void BST<T>::erase(iterator it)
   {

      //CASE 1: NO children
      if (it.p->pRight == nullptr && it.p->pLeft == nullptr) // there aint no children up in here mmm hmmm das what i'm sayin.
      {
         
         if (it.p->pParent != nullptr && it.p->pParent->pRight == it.p)
         {//we are on the right of a parent
            it.p->pParent->pRight = nullptr;
            delete it.p;
            it.p = nullptr;
         }
         else if (it.p->pParent != nullptr && it.p->pParent->pLeft == it.p)
         {//we are on the left of a parent
            it.p->pParent->pLeft = nullptr;
            delete it.p;
            it.p = nullptr;
         }
         else if (it.p->pParent == nullptr)
         {//there is no parent
            delete it.p;
            it.p = nullptr;
         }
      }

      //CASE 2: One Child
      if (it.p->pRight != nullptr && it.p->pLeft == nullptr)
      {//we have a left child, but no right children
         it.p->pRight->pParent = it.p->pParent;
         
         if (it.p->pParent != nullptr && it.p->pParent->pRight == it.p)
         {
            it.p->pParent->pRight = it.p->pRight;
         }
         
         if (it.p->pParent != nullptr && it.p->pParent->pLeft == it.p)
         {
            it.p->pParent->pLeft = it.p->pRight;
         }
      }
      
      if (it.p->pRight == nullptr && it.p->pLeft != nullptr)
      {//we have a right child but not a left one
         it.p->pLeft->pParent = it.p->pParent;
         
         if (it.p->pParent != nullptr && it.p->pParent->pRight == it.p)
         {
            it.p->pParent->pRight = it.p->pLeft;
         }
         
         if (it.p->pParent != nullptr && it.p->pParent->pLeft == it.p)
         {
            it.p->pParent->pLeft = it.p->pLeft;
         }
      }
      
      //CASE 3: Two Children
      if(it.p->pRight != nullptr && it.p->pLeft != nullptr)
      {
         iterator ios = it;
         ++ios;
         assert(ios.p->pLeft == nullptr); //ios should NOT have a left child

         if(ios.p->pRight != nullptr)
         {
            it.p->pRight->pParent = ios.p; //change it->p to ios
            ios.p->pRight->pParent = ios.p->pRight; //move ios's right child to ios's spot
            delete it.p;
         }
         else
         {
            it.p->pRight->pParent = ios.p;
            delete it.p;
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
            if(root == nullptr)
            {
               return iterator(nullptr);
            }
            BNode <T> *pNew;
            pNew = root;

            while(pNew->pLeft)
            {
               pNew = pNew->pLeft;
            }
            
            return iterator (pNew);
         }

	template<class T>
	typename BST<T>::iterator BST<T>::end()
	{
		return iterator(nullptr);
	}

   
/************************************************
* Find:
* Searches the Binary Search Tree for an item.
v************************************************/
        template <class T>
           typename BST<T>::iterator BST<T>::find(T itemToFind)
        {
           for (iterator it = begin(); it != nullptr; it++)
           {
              if (*it == itemToFind)
              {
                 return it;
              }
           }
           
           return nullptr;
        }
        

} // namespace custom

#endif // BST_H
