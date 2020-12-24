/**************************************************************************************
 * File name: 234_tree.h
 * ------------------------------
 * This file contains codes for interface and implementation of generic 234 tree.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/30/2020
 * Date Last Revised: 10/31/2020
**************************************************************************************/

#include <vector>
#include <queue>
using namespace std;

template <class BaseData> class TwoThreeFourNode
{
public:
    BaseData firstInfo, secondInfo, thirdInfo;     // the data in the nodes
    TwoThreeFourNode *firstChild, *secondChild, *thirdChild, *fourthChild;
    TwoThreeFourNode();

};

template <class BaseData>
TwoThreeFourNode<BaseData>::TwoThreeFourNode()
{firstChild=NULL;
    secondChild=NULL;
    thirdChild=NULL;
    fourthChild=NULL;
    firstInfo=(BaseData) NULL;
    secondInfo=(BaseData) NULL;
    thirdInfo=(BaseData) NULL;
}



template <class BaseData>
class TwoThreeFourTree
{

protected:

    TwoThreeFourNode<BaseData> *root;
    int (*compare)(const BaseData& x, const BaseData& y);

private:         // internal auxillary functions

    // ------------------------------------------------------------------------
    // Interface for splitroot function
    // GIVEN:    t is a non-NULL pointer to a 2-3-4 tree node with
    //           active data items.
    // RETURN:   splitroot will create two new 2-3-4 nodes and use
    //           these to split the initial node into three nodes,
    //           each with one active data item.  t will be returned
    //           as a pointer to the root of a 2-3-4 subtree and will
    //           have two children.
    void splitRoot
            (TwoThreeFourNode<BaseData> *& t);




    // ------------------------------------------------------------------------
    // Interface for splitchildof2 function
    // GIVEN:    tree is a pointer to a 2-3-4 tree 4-node (which
    //           stores three data values) and whose parent node,
    //           accessible through the pointer parent, has one
    //           data value.
    // RETURN:   splitchildof2 will split the node pointed to by
    //           tree into two nodes, each of which will have one
    //           data value.  The middle value will be promoted
    //           to the parent node.  Upon return, tree will
    //           reference the same node as parent.
    //
    void splitChildOf2
            (TwoThreeFourNode<BaseData> *& tree,
             TwoThreeFourNode<BaseData> *& parent);



    // -------------------------------------------------------------
    // Interface for splitchildof3 function
    // GIVEN:    tree is a pointer to a 2-3-4 tree 4-node (which
    //           stores three data values) and whose parent node,
    //           accessible through the pointer parent, has two
    //           data values.
    // RETURN:   splitchildof3 will split the tree node pointed
    //           to by tree into two tree nodes, each of which
    //           will have one data value.  The middle value will
    //           be promoted to the parent node.  Upon return,
    //           tree will reference the same node as parent node.

    void splitChildOf3
            (TwoThreeFourNode<BaseData> *& tree,
             TwoThreeFourNode<BaseData> *& parent);
    // TwoThreeFourNode<BaseData> * makeTreeNode();



    // ------------------------------------------------------------------------
    // Interface for nodetype function
    // GIVEN:  t is a pointer to a 2-3-4 tree node, presumed to be non-NULL.
    // RETURN as value of function:  an integer value indicating the type of
    //                               node -- 2 for two-node, 3 for three-node,
    //                               4 for four-node
    //

    int nodeType
            (TwoThreeFourNode<BaseData> * t);



    // ------------------------------------------------------------------------
    // Interface for insertdata function
    // GIVEN:  t is a pointer to a non-NULL 2-3-4 tree node.  Node referenced by
    //         t is assumed to have values in one or two data fields.  newdata
    //         is to be inserted into the 2-3-4 tree node pointed to by T. It is
    //         assumed that NewData is not already in the node.
    // RETURN: Node referenced by t will have newdata inserted into a data
    //         field of this node at an appropriate info field, possibly
    //         requiring that existing records be moved to make room.
    //
    //

    void insertData
            (TwoThreeFourNode<BaseData> * t,
             BaseData newData);




    // ------------------------------------------------------------------------
    // Interface for leafnode function
    // GIVEN:   t is a pointer to a 2-3-4 tree node.
    // RETURN as value of function:  true if the node is a leaf node;
    //                               false otherwise.
    //

    bool leafNode
            (TwoThreeFourNode<BaseData> * t);




    // ------------------------------------------------------------------------
    // Interface for whichchild function
    // GIVEN:   t pointer to a non-NULL 2-3-4 tree node.
    //          data is a value to be compared to the data items stored in
    //          node T.
    // RETURN as value of function:  a n integer value indicating whether the
    //                               given data value occurs in the current node
    //                               or not. If a match, returns the value -1;
    //                               if not, returns the value 0 if the current
    //                               node is a leaf, otherwise returns a value
    //                               indicating which child to follow to the
    //                               appropriate next node where the data value
    //                               may occur. Here 1 implies firstchild, 2
    //                               implies secondchild, 3 implies thirdchild,
    //                               4 implies fourthchild.
    //

    int whichChild
            (TwoThreeFourNode<BaseData> * t,
             BaseData data);




    // ------------------------------------------------------------------------
    // Interface for privSearch function
    // GIVEN:   rt is a pointer to root of two-three-four tree,
    //          target is of type BaseData and contains, perhaps in a special
    //          key field, a value to be searched for according to the precedes
    //          relationship underlying the tree.
    // RETURN:  If target can be found in the tree,
    //          item contains the entire contents of the tree node (key value
    //          and all associated data) that matches target.  If target is not
    //          found, item is unreliable.
    // RETURN as value of function:  true if target could be found in the
    //                               two-three-four tree.  false if target is
    //                               not in the tree
    //
    bool privSearch(TwoThreeFourNode<BaseData> * rt, BaseData target,
                    BaseData& item);

    void inord (TwoThreeFourNode<BaseData> *rt, vector<BaseData>& In);
    void preord (TwoThreeFourNode<BaseData> *rt, void (*processNode)(BaseData& item));
    void postord (TwoThreeFourNode<BaseData> *rt, void (*processNode)(BaseData& item));
    void delaux(TwoThreeFourNode<BaseData> *&rt);
    void copyAux(TwoThreeFourNode<BaseData> * src, TwoThreeFourNode<BaseData> * dest);

    /* Function to get index of a specified node data in vector In */
    int posOf(const BaseData& data, const vector<BaseData>& In);

public:
    /* Function to draw a “pseudo-graphical” form of the 234 tree. */
    void drawGraph(void (*processNode)(BaseData &item) );

    // ------------------------------------------------------------------------
    // Interface for two-three-four tree constructor
    // GIVEN:   An uninitialized two-three-four tree object, and
    //          precedes -- a function to compare BaseData values:
    //             GIVEN:   x and y -- values to compare
    //             RETURN as function value:
    //                 int less than 0     if x is precedes y,  x < y
    //                 0                   if x and y are equal, or
    //                 int greater than 0  if y is precedes x
    // RETURN:  The two-three-four tree object is initialized to the empty tree
    //          with precedes establishing the hierarchical ordering of the
    //          tree
    //

    TwoThreeFourTree (int  (*precedes)(const BaseData& x, const BaseData& y));

    // CopyConstructor
    TwoThreeFourTree(const TwoThreeFourTree<BaseData> & initTwoThreeFourTree);


    // assign
    void operator =(const TwoThreeFourTree<BaseData> & initTwoThreeFourTree);


    // destructor
    ~TwoThreeFourTree();



    // ------------------------------------------------------------------------
    // Interface for add operation
    // GIVEN:   A two-three-four tree object,
    //          item is of type BaseData.
    // RETURN:  item is added to the two-three-four tree in fashion that
    //          retains the ordering of the tree according to its precedes
    //          relation
    // RETURN as value of function:  true if item could be added to the
    //                               two-three-four tree.  false if item was not
    //                               added because it was already in the tree
    //


    bool add (BaseData item);




    // ------------------------------------------------------------------------
    // Interface for search operation
    // GIVEN:   A two-three-four tree object,
    //          target is of type BaseData and contains, perhaps in a special
    //          key field, a value to be searched for according to the precedes
    //          relationship underlying the tree.
    // RETURN:  If target can be found in the tree,
    //          item contains the entire contents of the tree node (key value
    //          and all associated data) that matches target.
    // RETURN as value of function:  true if target could be found in the
    //                               two-three-four tree.  false if target is
    //                               not in the tree
    //


    bool search(BaseData target, BaseData& item);


    void inOrderTrav(vector<BaseData>& In);

    // dumps all non-empty info fields first, before recursing on children
    void preOrderTrav(void (*processNode)(BaseData& item));

    // dumps all non-empty info fields last, aftering from processing children
    void postOrderTrav(void (*processNode)(BaseData& item));

};

template <class BaseData>
TwoThreeFourTree<BaseData>::TwoThreeFourTree(int(*precedes)(const BaseData& x, const BaseData& y))
{
    root = NULL;
    compare = precedes;
}
template <class BaseData>
void TwoThreeFourTree<BaseData>::copyAux(TwoThreeFourNode<BaseData> *src, TwoThreeFourNode<BaseData> *dest)
{
    if (src !=NULL)
    {dest->firstInfo=src->firstInfo;
        dest->secondInfo=src->secondInfo;
        dest->thirdInfo=src->thirdInfo;
        if (src->firstChild != NULL)
        {
            TwoThreeFourNode<BaseData> *temp;
            temp=new TwoThreeFourNode<BaseData>;
            dest->firstChild=temp;

            copyAux(src->firstChild,temp);
        }
        if (src->secondChild != NULL)
        {
            TwoThreeFourNode<BaseData> *temp;
            temp=new TwoThreeFourNode<BaseData>;
            dest->secondChild=temp;

            copyAux(src->secondChild,temp);
        }
        if (src->thirdChild != NULL)
        {
            TwoThreeFourNode<BaseData> *temp;
            temp=new TwoThreeFourNode<BaseData>;
            dest->thirdChild=temp;

            copyAux(src->thirdChild,temp);
        }
        if (src->fourthChild != NULL)
        {
            TwoThreeFourNode<BaseData> *temp;
            temp=new TwoThreeFourNode<BaseData>;
            dest->fourthChild=temp;

            copyAux(src->fourthChild,temp);
        }
    }
}

template <class BaseData>
TwoThreeFourTree<BaseData>::TwoThreeFourTree(const TwoThreeFourTree<BaseData> & initTwoThreeFourTree)
{
    compare=initTwoThreeFourTree.compare;
    if (initTwoThreeFourTree.root == NULL) root=NULL;
    else
    {
        root=new TwoThreeFourNode<BaseData>;
        copyAux(initTwoThreeFourTree.root,root);
    }
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::operator =(const TwoThreeFourTree<BaseData> & initTwoThreeFourTree)
{
    if (root != NULL)
    {
        delaux(root);
    }
    compare=initTwoThreeFourTree.compare;
    if (initTwoThreeFourTree.root == NULL) root=NULL;
    else
    {
        root=new TwoThreeFourNode<BaseData>;
        copyAux(initTwoThreeFourTree.root,root);
    }
}

// Implementation of add operation, given the preceding
// subordinate functions
template <class BaseData>
bool TwoThreeFourTree<BaseData>::add(BaseData item)
{
    bool done;
    TwoThreeFourNode<BaseData> *p, *prev;
    int w;

    if (root == NULL)                                     //  First time adding into a empty tree, NULL Root node.
    {
        root = new TwoThreeFourNode<BaseData> ;
        root->firstInfo = item;
        return (true);
    }
    if (nodeType(root) == 4)                              //  if root is 4-node, then split the root.
        splitRoot(root);                                            // Case A: insert into a 4-node root.
    p = root;       // always start from root to add item.
    prev = NULL;   // prev is parent of p
    done = false;
    while (!done)  // start descending down to the proper position in a tree
    {
        if (nodeType(p) == 4)                            // check if current pointing node is a 4-node.
            if (nodeType(prev) == 2)                            // if previous of current node is 2-node.
                splitChildOf2(p, prev);                         // ⚠️ Case B: parent of the 4-node is a 2-node ⚠️
            else                                                // if previous of current node is 3-node.
                splitChildOf3(p, prev);                         // ⚠️ Case C: parent of the 4-node is a 3-node ⚠️
        // After return from split function, p has been reset to its parent
        w = whichChild(p, item);
        switch (w)                          // follow which node to descend!
        {
            case -1:        // item is already in the tree
                return(false);

            case 0:         // p is a leaf node, 234 tree always adds item into the leaf node.
                insertData(p, item); // now can add！
                return(true);

            case 1:         // follow firstChild
                prev = p;
                p = p->firstChild;
                break;
            case 2:         // follow second child
                prev = p;
                p = p->secondChild;
                break;
            case 3:         // follow third child
                prev = p;
                p = p->thirdChild;
                break;
            case 4:         // follow fourth child
                prev = p;
                p = p->fourthChild;
                break;
        }  // switch
    }  // End of while(!done)
}


template <class BaseData>
bool TwoThreeFourTree<BaseData>::privSearch(TwoThreeFourNode<BaseData> *rt,
                                            BaseData target, BaseData& item)
{
    if (rt == NULL)                     // target will not be in empty tree
        return(false);
    if (compare(target, rt->firstInfo) == 0)  // check firstInfo's data
    {
        item = rt->firstInfo;
        return(true);
    }
    if (compare(target, rt->firstInfo) < 0)  // recursively search 1st subtree
        return (privSearch(rt->firstChild, target, item));
    // If reach this point, target must follow rt-> firstInfo,
    // so check to see if secondInfo is empty flag (i.e., NULL)
    if (((int)(rt->secondInfo)) != NULL)     // then rt references a 3- or 4-node
    {
        if (compare(target, rt->secondInfo) == 0)  // check secondInfo's data
        {
            item = rt->secondInfo;
            return(true);
        }
        if (compare(target, rt->secondInfo) < 0) // recursively search 2nd subtree
            // of a 3- or 4-node
            return (privSearch(rt->secondChild, target, item));
        if (((int)(rt->thirdInfo)) != NULL)     // then rt references a 4-node
        {
            if (compare(target, rt->thirdInfo) == 0)  // check thirdInfo's data
            {
                item = rt->thirdInfo;
                return(true);
            }
            if (compare(target, rt->thirdInfo) < 0) // recursively search 3rd subtree
                // of a 4-node
                return (privSearch(rt->thirdChild, target, item));
            else                                   // recursively search 4th subtree
                return (privSearch(rt->fourthChild, target, item)); // of a 4-node
        }
        else   // recursively search third subtree of a 3-node, as referenced
            return (privSearch(rt->fourthChild, target, item)); // by fourthChild
    }
    else // recursively search second subtree of a 4-node, as referenced
        return (privSearch(rt->fourthChild, target, item)); // by fourthChild
}


template <class BaseData>
bool TwoThreeFourTree<BaseData>::search(BaseData target, BaseData& item)
{
    // Just pass the root pointer to the recursive workhorse
    return(privSearch(root, target, item));
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::splitRoot(TwoThreeFourNode<BaseData> * & t)  // ⚠️ Case A ⚠️
{
    TwoThreeFourNode<BaseData> *c1, *c2;
    c1=new TwoThreeFourNode<BaseData>;
    c2=new TwoThreeFourNode<BaseData>;
    c1->firstInfo=t->firstInfo;
    c1->firstChild=t->firstChild;
    c1->fourthChild=t->secondChild;
    c2->firstInfo=t->thirdInfo;
    c2->firstChild=t->thirdChild;
    c2->fourthChild=t->fourthChild;
    t->firstInfo=t->secondInfo;
    t->secondInfo=(BaseData)NULL;
    t->thirdInfo=(BaseData)NULL;
    t->firstChild=c1;
    t->secondChild=NULL;
    t->thirdChild=NULL;
    t->fourthChild=c2;
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::splitChildOf2
        (TwoThreeFourNode<BaseData> *& tree,
         TwoThreeFourNode<BaseData> *& parent)
// added &
{TwoThreeFourNode<BaseData> *q;
    q = new TwoThreeFourNode<BaseData>;
    if (tree == parent->firstChild)                         // ⚠️ Case B1: the 4-node is its parent's 1st child ⚠️
    {
        q->firstChild=tree->thirdChild;
        q->fourthChild=tree->fourthChild;
        q->firstInfo=tree->thirdInfo;
        parent->secondInfo=parent->firstInfo;
        parent->firstInfo=tree->secondInfo;
        parent->secondChild=q;
        tree->fourthChild=tree->secondChild;
        tree->secondChild=NULL;
        tree->thirdChild=NULL;
        tree->secondInfo=(BaseData)NULL;
        tree->thirdInfo=(BaseData)NULL;
    }
    else                                                    // ⚠️ Case B2: the 4-node is its parent's 4th child.⚠️
    {
        q->firstChild=tree->firstChild;
        q->fourthChild=tree->secondChild;
        q->firstInfo=tree->firstInfo;
        parent->secondChild=q;
        parent->secondInfo=tree->secondInfo;
        tree->firstChild=tree->thirdChild;
        tree->secondChild=NULL;
        tree->thirdChild=NULL;
        tree->firstInfo=tree->thirdInfo;
        tree->secondInfo=(BaseData)NULL;
        tree->thirdInfo=(BaseData)NULL;
    }
    tree = parent;
}

template <class BaseData>
void TwoThreeFourTree<BaseData>:: splitChildOf3
        (TwoThreeFourNode<BaseData> *& tree,
         TwoThreeFourNode<BaseData> *& parent)

{TwoThreeFourNode<BaseData> *q;
    q=new TwoThreeFourNode<BaseData>;
    if (tree == parent->firstChild)                             // ⚠️ Case C1: the 4-node is its parent's 1st child.⚠️
    {
        q->firstChild=tree->thirdChild;
        q->fourthChild=tree->fourthChild;
        q->firstInfo=tree->thirdInfo;
        parent->thirdChild=parent->secondChild;
        parent->secondChild=q;
        parent->thirdInfo=parent->secondInfo;
        parent->secondInfo=parent->firstInfo;
        parent->firstInfo=tree->secondInfo;
        tree->fourthChild=tree->secondChild;
        tree->thirdChild=NULL;
        tree->secondChild=NULL;
        tree->secondInfo=(BaseData)NULL;
        tree->thirdInfo=(BaseData)NULL;
    }
    else if (tree == parent->secondChild)                       // ⚠️ Case C2: the 4-node is its parent's 2nd child.⚠️
    {
        q->firstChild=tree->thirdChild;
        q->fourthChild=tree->fourthChild;
        q->firstInfo=tree->thirdInfo;
        parent->thirdInfo=parent->secondInfo;
        parent->secondInfo=tree->secondInfo;
        parent->thirdChild=q;
        tree->fourthChild=tree->secondChild;
        tree->secondChild=NULL;
        tree->thirdChild=NULL;
        tree->secondInfo=(BaseData)NULL;
        tree->thirdInfo=(BaseData)NULL;
    }
    else //tree==parent->fourthChild                            // ⚠️ Case C3: the 4-node is its parent's 4th child.⚠️
    {
        q->firstChild=tree->thirdChild;
        q->fourthChild=tree->fourthChild;
        q->firstInfo=tree->thirdInfo;
        parent->thirdInfo=tree->secondInfo;
        parent->thirdChild=tree;
        parent->fourthChild=q;
        tree->fourthChild=tree->secondChild;
        tree->secondChild=NULL;
        tree->thirdChild=NULL;
        tree->secondInfo=(BaseData)NULL;
        tree->thirdInfo=(BaseData)NULL;
    }
    tree=parent;
}

template <class BaseData>
int TwoThreeFourTree<BaseData>::nodeType (TwoThreeFourNode<BaseData> * t)
{
    if (t->thirdInfo != NULL) return(4);                                  // 4: adding into a 4-node
    else
    if (t->secondInfo != NULL) return(3);                                 // 3: adding into a 3-node
    else
        return(2);                                                        // 2: adding into a 2-node
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::insertData (TwoThreeFourNode<BaseData> * t,
                                             BaseData newData)
{
    switch (nodeType(t))
    {
        case 2:
        {
            if (compare (newData, t->firstInfo)<0)
            {
                t->secondInfo=t->firstInfo;
                t->firstInfo=newData;
            }
            else
                t->secondInfo=newData;
            break;
        }
        case 3:
        {
            if (compare (newData,t->firstInfo)<0)
            {
                t->thirdInfo=t->secondInfo;
                t->secondInfo=t->firstInfo;
                t->firstInfo=newData;
            }
            else
            if (compare (newData,t->secondInfo)<0)
            {
                t->thirdInfo=t->secondInfo;
                t->secondInfo=newData;
            }
            else
                t->thirdInfo=newData;
            break;
        }
    } // switch
} // insert data

template <class BaseData>
bool TwoThreeFourTree<BaseData>::leafNode(TwoThreeFourNode<BaseData> * t)
{
    if (t != NULL)
        return((t->firstChild==NULL) && (t->secondChild==NULL) && (t->thirdChild==NULL)
               && (t->fourthChild==NULL));
    else return(false);
}

template <class BaseData>
int TwoThreeFourTree<BaseData>::whichChild (TwoThreeFourNode<BaseData> * t,
                                            BaseData data)
// -1：item already exists, 1: first child, 2: second child
// 3: 3rd child, 4: fourth child.
{
    switch(nodeType(t))
    {
        case 2:
        {
            if (compare(data,t->firstInfo)==0) return(-1);
            else
            if(leafNode(t)) return(0);
            else
            if (compare (data, t->firstInfo) < 0) return(1);
            else return(4);

        }
        case 3:
        {
            if (compare(t->firstInfo,data)==0) return(-1);
            else
            if (compare(t->secondInfo,data)==0) return(-1);
            else
            if (leafNode(t)) return(0);
            else
            if (compare(data, t->firstInfo)< 0) return(1);
            else
            if (compare(data, t->secondInfo)< 0) return(2);
            else return(4);

        }
        case 4:
        {
            if (compare(t->firstInfo,data)==0) return(-1);
            else
            if (compare(t->secondInfo,data)==0) return(-1);
            else
            if (compare(t->thirdInfo,data)==0) return(-1);
            else
            if (leafNode(t)) return(0);
            else
            if (compare(data, t->firstInfo)<0) return(1);
            else
            if (compare(data, t->secondInfo)<0) return(2);
            else
            if (compare(data, t->thirdInfo)<0) return(3);
            else return(4);

        }
    } //switch
}

/*******************************************************************************************
* Function Name: posOf()
*
* Purpose: Function to get index of a specified node data in vector In.
*
* Input Parameters:
*          data: data to be looked for.
*          In: a vector of node data type.
*
* Output parameters: none.
*
* Return Value:
*          -1: item does not exists
 *         other non-negative integer: index of the item in vector In.
*******************************************************************************************/
template <class BaseData>
int TwoThreeFourTree<BaseData>::posOf(const BaseData& data, const vector<BaseData>& In)
{
    for (int pos = 0; pos < In.size(); pos++)
        if (In[pos] == data) return pos;
    return -1;    // -1 means item not exists
}

/*******************************************************************************************
 * Function Name: drawGraph()
 *
 * Purpose: Function to draw a “pseudo-graphical” form of the 234 tree.
 *
 * Input Parameters:
 *          processNode: function pointer to how node data should be processed.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
template <class BaseData>
void TwoThreeFourTree<BaseData>::drawGraph(void (*processNode)(BaseData &item) )
{
    queue<TwoThreeFourNode<BaseData>* > queue;  // queue of nodes for by-level traversal
    vector<BaseData> In;                        // Inorder-nodes vector
    inord(root, In);              // construct in-order vector of the tree
    queue.push(root);                             // enqueue the first node for BFT

    // BFT algorithm:
    while (!queue.empty() )
    {
        vector<TwoThreeFourNode<BaseData>* > levelNodes;  // vector of nodes in the same level
        while (!queue.empty())                            // Store all nodes of current level
        {
            levelNodes.push_back(queue.front());
            queue.pop();
        }

        char lineToPrint[30] { char(0) };          // initialize printing line with empty char
        for (TwoThreeFourNode<BaseData>* node: levelNodes) // for each node in current level
            if (node)                                      // Enqueue all children of current node(if any)
            {
                // get the position of node's info
                int firstInfoPos = posOf(node->firstInfo, In);
                int secondInfoPos = posOf(node->secondInfo, In);
                int thirdInfoPos = posOf(node->thirdInfo, In);

                // place node's data into the same pos in data line
                if (firstInfoPos != -1)
                    lineToPrint[firstInfoPos] = node->firstInfo;
                if (secondInfoPos != -1)
                    lineToPrint[secondInfoPos] = node->secondInfo;
                if (thirdInfoPos != -1)
                    lineToPrint[thirdInfoPos] = node->thirdInfo;

                // enqueue 4 child pointers for next level traversal
                if (node->firstChild)
                    queue.push(node->firstChild);
                if (node->secondChild)
                    queue.push(node->secondChild);
                if (node->thirdChild)
                    queue.push(node->thirdChild);
                if (node->fourthChild)
                    queue.push(node->fourthChild);
            }

        // Now for each line:
        for (BaseData ch : lineToPrint)
            if (ch)
                processNode(ch);    // if there is data, print it.
            else
                cout << "  ";        // if no data, print whitespace.
        cout << endl;
    }
}

/*******************************************************************************************
 * Function Name: inord()
 *
 * Purpose: Function to store all nodes in in-order fashion into a vector In.
 *
 * Input Parameters:
 *          rt: root pointer.
 *          In: a vector of node data.
 *
 * Output parameters:
 *          In: the vector has been loaded with nodes in inorder order.
 *
 * Return Value: none.
 *******************************************************************************************/
template <class BaseData>
void TwoThreeFourTree<BaseData>::inord(TwoThreeFourNode<BaseData>* rt,
                                       vector<BaseData>& In)
{
    if (rt != NULL)
    {int nodetype;
        nodetype=nodeType(rt);

        switch (nodetype)
        {
            case 2:
                inord(rt->firstChild, In);
                In.push_back(rt->firstInfo);  // replaced processNode with In.push_back() for drawGraph()
                inord(rt->fourthChild, In);
                break;
            case 3:
                inord(rt->firstChild, In);
                In.push_back(rt->firstInfo);  // replaced processNode with In.push_back() for drawGraph()
                inord(rt->secondChild, In);
                In.push_back(rt->secondInfo); // replaced processNode with In.push_back() for drawGraph()
                inord(rt->fourthChild, In);
                break;
            case 4:
                inord(rt->firstChild, In);
                In.push_back(rt->firstInfo);  // replaced processNode with In.push_back() for drawGraph()
                inord(rt->secondChild, In);
                In.push_back(rt->secondInfo); // replaced processNode with In.push_back() for drawGraph()
                inord(rt->thirdChild, In);
                In.push_back(rt->thirdInfo);  // replaced processNode with In.push_back() for drawGraph()
                inord(rt->fourthChild, In);
                break;
        } // switch

    } // if
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::preord(TwoThreeFourNode<BaseData> * rt,
                                        void (*processNode)(BaseData& item))

{
    if (rt != NULL)
    {int nodetype;
        nodetype=nodeType(rt);

        switch (nodetype)
        {
            case 2:
                processNode(rt->firstInfo);
                preord(rt->firstChild,processNode);
                preord(rt->fourthChild,processNode);
                break;
            case 3:
                processNode(rt->firstInfo);
                processNode(rt->secondInfo);
                preord(rt->firstChild,processNode);
                preord(rt->secondChild,processNode);
                preord(rt->fourthChild,processNode);
                break;
            case 4:
                processNode(rt->firstInfo);
                processNode(rt->secondInfo);
                processNode(rt->thirdInfo);
                preord(rt->firstChild,processNode);
                preord(rt->secondChild,processNode);
                preord(rt->thirdChild,processNode);
                preord(rt->fourthChild,processNode);
                break;
        } // switch

    } // if
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::postord(TwoThreeFourNode<BaseData> * rt,
                                         void (*processNode)(BaseData& item))
{
    if (rt != NULL)
    {int nodetype;
        nodetype=nodeType(rt);

        switch (nodetype)
        {
            case 2:

                postord(rt->firstChild,processNode);
                postord(rt->fourthChild,processNode);
                processNode(rt->firstInfo);
                break;
            case 3:

                postord(rt->firstChild,processNode);
                postord(rt->secondChild,processNode);
                postord(rt->fourthChild,processNode);
                processNode(rt->firstInfo);
                processNode(rt->secondInfo);
                break;
            case 4:

                postord(rt->firstChild,processNode);
                postord(rt->secondChild,processNode);
                postord(rt->thirdChild,processNode);
                postord(rt->fourthChild,processNode);
                processNode(rt->firstInfo);
                processNode(rt->secondInfo);
                processNode(rt->thirdInfo);
                break;
        } // switch

    } // if
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::inOrderTrav(vector<BaseData>& In)
{
    inord(root, In);
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::preOrderTrav(void (*processNode)(BaseData& item))
{
    preord(root, processNode);
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::postOrderTrav(void (*processNode)(BaseData& item))
{
    postord(root, processNode);
}

template <class BaseData>
void TwoThreeFourTree<BaseData>::delaux(TwoThreeFourNode<BaseData> * & rt)
{
    if (rt != NULL)
    {int nodetype;
        nodetype=nodeType(rt);

        switch (nodetype)
        {
            case 2:

                delaux(rt->firstChild );
                delaux(rt->fourthChild );
                delete rt;
                break;
            case 3:

                delaux(rt->firstChild );
                delaux(rt->secondChild );
                delaux(rt->fourthChild );
                delete rt;
                break;
            case 4:

                delaux(rt->firstChild );
                delaux(rt->secondChild );
                delaux(rt->thirdChild );
                delaux(rt->fourthChild );
                delete rt;
                break;
        } // switch

    } // if
}

template <class BaseData>
TwoThreeFourTree<BaseData>::~TwoThreeFourTree()
{
    delaux(root);
}


