/***************************************************************************
* File name: AvlTree.t
* This file contains implementations of leftOfRight
*           and rightOfLeft methods for CS232_lab3.
* Programmer: Jian Zhong
* Date Written: 09/21/2020
* Date Last Revised: 09/22/2020
* **************************************************************************/

#ifndef AVLTREE_T
#define AVLTREE_T

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <cassert> 

#include <cstdio>

#ifndef leftChild
#define leftChild  firstChild
#endif

#ifndef rightChild
#define rightChild  sibling
#endif


template <class BaseData>
AvlTree<BaseData>::
AvlTree (  bool (*precedes)(const BaseData& x, const BaseData& y)    )
    : BinTree<BaseData> ()
{
  this->precedes = precedes;
}


template <class BaseData>
AvlTree<BaseData>::AvlTree (const AvlTree<BaseData> &initAvlTree)
{
  precedes=initAvlTree.precedes;
}


template < class BaseData>
bool AvlTree<BaseData>::add(BaseData item)
  {
    return addAux( (GenTree<BaseData>::root), item );
  }


template <class BaseData>
bool AvlTree<BaseData>::addAux(GtNode<BaseData> *& rt, BaseData item)
// Note that since the pointer rt will be altered by this
// function, it must be passed by reference.
{
  avlNode<BaseData> *temp;
  temp  = new avlNode<BaseData>;

  avlNode<BaseData> *p, *piv, *pivParent, *inp, *inParent, *q;

  p = new avlNode<BaseData>;
  assert(p != 0);
  p -> info = item;
  p -> leftChild = 0;
  p -> rightChild = 0;
  p -> bf = 0;



  if (rt == NULL)
    {
      rt = new avlNode<BaseData>;
      if (!rt)
        return false;
      else
        {
          rt = p;
          /// static_cast< avlNode<BaseData> * >( rt ) -> bf  = 0;
          return true;
        }
    }



  // Pointer inp keeps track of insertion point, with its
  // parent inparent.  Pointer piv keeps trace of pivot node,
  // with its parent pivParent.


  inp =  static_cast< avlNode<BaseData>*  >  (GenTree<BaseData>::root ) ;
  piv =  static_cast< avlNode<BaseData>*  >  (GenTree<BaseData>::root );
  inParent = NULL;
  pivParent = NULL;

  // Search for insertion point and pivot node
  do
    {
      if ( inp -> bf != 0)
        {
          piv = inp;
          pivParent = inParent;
        }
      inParent = inp;
      if (precedes(item, inp -> info))
        inp  =  static_cast< avlNode<BaseData>*  >( inp -> leftChild );
      else
        inp  =  static_cast< avlNode<BaseData>*  >( inp -> rightChild );
    }
  while (inp != 0);




  // Insert the node as the left or right child of inParent

  if (precedes(item, inParent -> info))
    inParent -> leftChild = p;
  else
    inParent -> rightChild = p;
  // Now recompute the balance factors between piv and inParent.
  // By definition of a pivot node, all these balance factors must
  // change by 1 in the direction of the insertion.

  q = piv;
  do
    {
      if ( precedes(item, q -> info) )
        {
          q -> bf++;
          q  =  static_cast< avlNode<BaseData>*  >( q -> leftChild );
        }
      else
        {
          q -> bf--;
          q  =  static_cast< avlNode<BaseData>*  >( q -> rightChild );
        }
    }
  while (q != p);

  // Need to rotate?  If not, then we're done!

  if (-1 <= piv -> bf && piv -> bf <= 1)
    return true;

  // AVL rotation is necessary.  Call on the appropriate
  // function, passing one of root, pivParent->leftChild, or
  // pivParent->rightChild as the pointer to the pivot node.

  if ( precedes(item, piv -> info) )
    if ( precedes(item, piv -> leftChild -> info) )
      if ( piv ==  AvlTree<BaseData>::root )
        leftOfLeft( AvlTree<BaseData>::root );
      else
        if ( piv == pivParent -> leftChild )
          {
            leftOfLeft( ( pivParent->leftChild ) );
          }
        else
          {
            leftOfLeft( ( pivParent->rightChild ) );
          }
    else
      if ( piv == GenTree<BaseData>::root )
        rightOfLeft( GenTree<BaseData>::root );
      else
        if ( piv == pivParent->leftChild )
          {
            rightOfLeft( pivParent -> leftChild );
          }
        else
          {
            rightOfLeft( pivParent->rightChild );
          }



  else
    // if (!precedes(item, piv->leftChild->info))   wrong
    if ( !precedes(item, piv -> rightChild -> info) )   //correct
      if ( piv == GenTree<BaseData>::root )
        rightOfRight( GenTree<BaseData>::root );
      else
        if ( piv == pivParent -> leftChild )
          {
            rightOfRight( pivParent -> leftChild );
          }
        else
          {
            rightOfRight( pivParent -> rightChild );
          }
    else
      if ( piv == GenTree<BaseData>::root )
        leftOfRight( GenTree<BaseData>::root );
      else
        if ( piv == pivParent -> leftChild )
          {
            leftOfRight( pivParent -> leftChild );
          }
        else
          {
            leftOfRight(pivParent->rightChild);
          }

  return true;

}


template <typename BaseData>
void AvlTree<BaseData>::leftOfLeft( GtNode<BaseData>* &pivot )
{
  avlNode<BaseData> *p, *q;

  // Begin by altering the necessary pointers
  p = static_cast< avlNode<BaseData> * > ( pivot -> leftChild );
  q = static_cast< avlNode<BaseData> * > ( p -> rightChild );
  p -> rightChild = pivot;
  pivot -> leftChild = q;
  pivot = p;

  // Then readjust the balance factors that have been affected
  static_cast< avlNode<BaseData> * > ( pivot ) -> bf = 0;
  static_cast< avlNode<BaseData> * > ( pivot -> rightChild ) -> bf = 0;
}


template <typename BaseData>
void AvlTree<BaseData>::rightOfRight( GtNode<BaseData> *& pivot )
{
  avlNode<BaseData> *p, *q;

  // begin by altering the necessary pointers
  p =  static_cast< avlNode<BaseData> * > ( pivot -> rightChild );
  q =  static_cast< avlNode<BaseData> * > ( p -> leftChild );
  p -> leftChild = pivot;
  pivot -> rightChild = q;
  pivot = p;

  // then readjust the balance factors that have been affected
  static_cast< avlNode<BaseData> * > (pivot) -> bf = 0;
  static_cast< avlNode<BaseData> * > ( pivot -> leftChild ) -> bf = 0;
}


/****************************************************************************************** *
* Function Name: rotateRightOfLeft()
* Purpose: function to perform a double rotation for right of left case in an AVL tree,
*            called by rightOfLeft().
* Input Parameters:
*          pivot: node pointer to an unbalanced node
*          t1: pointer to left child of pivot node
*          t2: pointer to right child of t1 node
* Output parameters: pivot, t1 and t2 have been rearranged to achieve right of left rotation.
* Return Value: none.
* ******************************************************************************************/
template < typename BaseData>
void rotateRightOfLeft(GtNode<BaseData>* & pivot, avlNode<BaseData>* t1, avlNode<BaseData>* t2) {
    pivot->leftChild = t2->rightChild;
    t2->rightChild = pivot;
    t1->rightChild = t2->leftChild;
    t2->leftChild = t1;
}


/****************************************************************************************** *
* Function Name: rightOfLeft()
* Purpose: function is to perform double rotation and reset balance factors
*            for the case of Right of Left in an AVL tree.
*
* Input Parameters:
*          pivot: node pointer to an unbalanced node
* Output parameters: balance factor of pivot and its subtree have been reset.
* Return Value: none.
* ******************************************************************************************/
template < typename BaseData>
void AvlTree<BaseData>::rightOfLeft(GtNode<BaseData>* &pivot)
{
    avlNode<BaseData> *t1, *t2;

 /* first adjust pointers in fashion to perform avl rotation */
    t1 = static_cast<avlNode<BaseData>* >(pivot->leftChild);
    t2 = static_cast<avlNode<BaseData>* >(t1->rightChild);

 /* then perform rotation and reset the balance factors according to the subcase */
    // subcase #1: right of left of pivot
    if (pivot->rightChild == NULL) {
        rotateRightOfLeft(pivot, t1, t2);
        static_cast<avlNode<BaseData>* >(pivot)->bf = 0;
        t1->bf = 0;
    }

    // subcase #2: right of right of left of pivot
    if (t2->leftChild == NULL && t2->rightChild != NULL) {
        rotateRightOfLeft(pivot, t1, t2);
        static_cast<avlNode<BaseData>* >(pivot)->bf = 0;
        t1->bf = 1;
        t2->bf = 0;
    }

    // subcase #3: left of right of left of pivot
    if (t2->leftChild != NULL && t2->rightChild == NULL) {
        rotateRightOfLeft(pivot, t1, t2);
        static_cast<avlNode<BaseData>* >(pivot)->bf = -1;
        t1->bf = 0;
        t2->bf = 0;
    }

    pivot = t2;    // readjust pivot after rotation.
}


/****************************************************************************************** *
* Function Name: rotateLeftOfRight()
* Purpose: function to perform a double rotation for left of right case in an AVL tree,
*             called by leftOfRight().
* Input Parameters:
*         pivot: pointer to the pivot node
*         t1: pointer to right child of pivot node
*         t2: pointer to left child of t1 node
* Output parameters: pivot, t1 and t2 have been rearranged to achieve left of right rotation.
* Return Value: none.
* ******************************************************************************************/
template < typename BaseData>
void rotateLeftOfRight(GtNode<BaseData>* & pivot, avlNode<BaseData>* t1, avlNode<BaseData>* t2) {
    pivot->rightChild = t2->leftChild;
    t2->leftChild = pivot;
    t1->leftChild = t2->rightChild;
    t2->rightChild = t1;
}


/****************************************************************************************** *
* Function Name: leftOfRight()
* Purpose: function is to perform double rotation and reset balance factors
*            for the Case of Left of Right in an AVL tree.
*
* Input Parameters:
*          pivot: node pointer to an unbalanced node
* Output parameters: balance factor of pivot and its subtree have been reset.
* Return Value: none.
* ******************************************************************************************/
template < typename BaseData>
void AvlTree<BaseData>::leftOfRight(GtNode<BaseData>* & pivot)
{
    avlNode<BaseData> *t1, *t2;

 /* first adjust pointers in fashion to perform avl rotation */
    t1 = static_cast<avlNode<BaseData>* >(pivot->rightChild);
    t2 = static_cast<avlNode<BaseData>* >(t1->leftChild);

 /* then perform rotation and reset the balance factors according to the subcase */
    // subcase #1: left of right of pivot
    if (pivot->leftChild == NULL) {
        rotateLeftOfRight(pivot, t1, t2);
        static_cast<avlNode<BaseData>* >(pivot)->bf = 0;
        t1->bf = 0;
    }

    // subcase #2: left of left of right of pivot
    if (t2->leftChild != NULL && t2->rightChild == NULL) {
        rotateLeftOfRight(pivot, t1, t2);
        static_cast<avlNode<BaseData>* >(pivot)->bf = 0;
        t1->bf = -1;
        t2->bf = 0;
    }

    // subcase #3: right of left of right of pivot
    if (t2->leftChild == NULL && t2->rightChild != NULL) {
        rotateLeftOfRight(pivot, t1, t2);
        static_cast<avlNode<BaseData>* >(pivot)->bf = 1;
        t1->bf = 0;
        t2->bf = 0;
    }

    pivot = t2;    // readjust pivot after rotation.
}

#endif
