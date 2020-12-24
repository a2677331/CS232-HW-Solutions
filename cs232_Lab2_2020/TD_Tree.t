// Jian Zhong
// Prof. Streller
// CS232 Lab2
// 09/15/2020
// cs232_lab2_ZHONG.cpp

#ifndef TDTREE_T
#define TDTREE_T

#include <cstdio>


template <class BaseData>
TDTree<BaseData>::TDTree(int (*precedes)(const BaseData& x, const BaseData& y))
        : GenTree<BaseData> ()
{
    compare = precedes;
}

template <class BaseData>
TDTree<BaseData>::TDTree(const TDTree<BaseData> & initTopDownTree)
        : GenTree<BaseData> (initTopDownTree)
{
    compare = initTopDownTree.compare;
}


template < class BaseData>
bool TDTree<BaseData>::add(BaseData parent, BaseData item, int childnum)
{
    if ( GenTree<BaseData>::root == 0 )
    {
        GenTree<BaseData>::root = new GtNode<BaseData>;
        GenTree<BaseData>::root->info = item;
        GenTree<BaseData>::root->firstChild = NULL;
        GenTree<BaseData>::root->sibling = NULL;
        return(true);
    }
    else
        return(add_aux( GenTree<BaseData>::root, parent, item, childnum) );
}



template < class BaseData>
bool TDTree<BaseData>::add_aux(GtNode<BaseData> * rt, BaseData parent,
                               BaseData item, int childnum)
{
    GtNode<BaseData> *temp;
    GtNode<BaseData> *prev;
    int c ;

    if ( rt !=  0 )
        if (compare(parent,rt->info) == 0)
        {
            temp = new GtNode<BaseData>;
            temp->info = item;
            temp->firstChild = 0;
            if (childnum == 1 || rt->firstChild == 0)
            {
                temp->sibling = rt->firstChild;
                rt->firstChild = temp;
            }
            else
            {
                for ( c = 2, prev = rt -> firstChild; ( c<childnum && prev != 0 );
                      ++c, prev = prev -> sibling) ;
                temp -> sibling = prev -> sibling;
                prev -> sibling = temp;
            }
            return(true);
        }
        else if (!add_aux(rt->firstChild,parent,item,childnum))
            return(add_aux(rt->sibling,parent,item,childnum));
        else
            return(true);
    else
        return(false);
}



/// Function to add a node and its sibling nodes into a Queue by recursion.
/// Called by breadthFirstTraversal().
/// @param node: ptr to tree node
/// @param nodeQueue: a Queue of nodes ptrs
template <class BaseData>
void addChildrenNodes(GtNode<BaseData>* node, std::queue<GtNode<BaseData>* > & nodeQueue)
{
    if (node)
    {
        nodeQueue.push(node);
        addChildrenNodes(node->sibling, nodeQueue);
    }
}



/// Function to do a breadth first traversal of a TD tree.
template <class BaseData>
void TDTree<BaseData>::breadthFirstTraversal( void (*processnode)(BaseData &value) )
{
    std::queue< GtNode<BaseData>* > nodeQueue;            // queue for nodes to visit
    GtNode<BaseData>* node = GenTree<BaseData>::root;     // tree node

    if (node)   // don't want to traverse an empty tree
    {
        nodeQueue.push(node);          // initialize a queue with the root node

        /* Breadth First Traversal algorithm */
        while (!nodeQueue.empty())     // traverse while have nodes in Queue
        {
            node = nodeQueue.front();  // dequeue a node from Queue
            nodeQueue.pop();
            processnode(node->info);   // visit node
            addChildrenNodes(node->firstChild, nodeQueue); // enqueue children nodes to Queue, if any.
        }
    }
}

/********** Sample Runs from driver.cpp **************

 t1 printing breadth first traversal
Hit hreE

 oops ... let's try that again

 t1 printing depth first traversal
Hi thEre

 *****************************************************/

#endif


