/**************************************************************************************
 * File name: splay.h
 * ------------------
 * This file contains codes for interface and implementation of   splaying tree.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/21/2020
 * Date Last Revised: 10/23/2020
**************************************************************************************/

#ifndef SPLAYING
#define SPLAYING

#include <queue>
#include <vector>

using namespace std;

template<class T> class SplayTree;

template<class T>
class SplayingNode
{
public:

    SplayingNode()
    {
        left = right = parent = 0;
    }

    SplayingNode(const T& el, SplayingNode *l = 0, SplayingNode *r = 0,
                 SplayingNode *p = 0)
    {
        info = el;
        left = l;
        right = r;
        parent = p;
    }

    T info;
    SplayingNode *left, *right, *parent;
};



template<class T>
class SplayTree
{

public:
    SplayTree()
    {
        root = 0;
    }
    void inorder()
    {
        inorder(root);
    }
    T* search(const T&);
    void insert(const T&);

    // A wrapper functino that wraps the drawGraph function.
    void drawGraph()
    {
        drawGraph(root);
    }

protected:
    SplayingNode<T> *root;
    void rotateR(SplayingNode<T>*);
    void rotateL(SplayingNode<T>*);
    void continueRotation(SplayingNode<T>* gr, SplayingNode<T>* par,
                          SplayingNode<T>* ch, SplayingNode<T>* desc);
    void semisplay(SplayingNode<T>*);
    void fullsplay(SplayingNode<T>*);

    // Function to draw a “pseudo-graphical” form of the splay tree.
    void drawGraph(SplayingNode<T>* root);

    // Function to get index of a specified node data in vector In.
    int posOf(const T& data, const vector<T>& In);

    // Function to store all nodes in terms of inorder into vector In.
    void InOrder(SplayingNode<T>* root, vector<T>& In);
};


/*******************************************************************************************
 * Function Name: drawGraph()
 *
 * Purpose: Function to draw a “pseudo-graphical” form of the splay tree.
 *
 * Input Parameters:
 *          root: tree root pointer.
 *
 * Output parameters: none.
 *
 * Return Value: none.
 *******************************************************************************************/
template<class T>
void SplayTree<T>::drawGraph(SplayingNode<T>* root)
{
    queue<SplayingNode<T> *> Queue; // Queue of nodes for traversal.
    Queue.push(root);               // enqueue initial node before BFS traversal.

    vector<T> inOrd;                // collection that stores node data in an inorder fashion.
    InOrder(root, inOrd);       // load node data from in-order traversal.

    // BFS algorithm:
    while (!Queue.empty())
    {
        vector<SplayingNode<T> *> nodesCount; // # of nodes at each level

        // Get all nodes of the same level
        while (!Queue.empty())
        {
            nodesCount.push_back(Queue.front()); // dequeue node from Queue.
            Queue.pop();
        }

        // Construct lines for printing:
        T dataLine[30]{T(0)};                       // line to print for node data
        char labelLine[30]{char(0)};                // line to print for '/' and '\' labels
        for (SplayingNode<T> *node: nodesCount)     // for each node at the same level
            if (node)                                     // if node exists
            {
                int nodePos = posOf(node->info, inOrd);   // get the pos of the node's inorder pos
                dataLine[nodePos] = node->info;           // place node's data into the same pos in data line

                // Enqueue all children of current node(if any)
                if (node->left)
                {
                    labelLine[nodePos - 1] = '/';   // place a '/' label in label line.
                    Queue.push(node->left);
                }
                if (node->right)
                {
                    labelLine[nodePos + 1] = '\\';  // place a '\' label in label line.
                    Queue.push(node->right);
                }
            }

        // Now lines have already constructed, just print lines:
        for (T data : dataLine)      // Print the line with node data.
            if (data != T(0))
                cout << data;
            else
                cout << " ";
        cout << endl;

        for (char label : labelLine) // Print the line with labels '/' and '\'.
            if (label != char(0))
                cout << label;
            else
                cout << " ";
        cout << endl;
    }
}


/*******************************************************************************************
 * Function Name: InOrder()
 *
 * Purpose: Function to store all nodes in terms of inorder into vector In.
 *
 * Input Parameters:
 *          root: root pointer.
 *          In: a vector of node data type.
 *
 * Output parameters:
 *          In: the vector has been loaded with nodes in inorder traversal order.
 *
 * Return Value: none.
 *******************************************************************************************/
template<class T>
void SplayTree<T>::InOrder(SplayingNode<T>* root, vector<T>& In)
{
    if (root)
    {
        InOrder(root->left, In);
        In.push_back(root->info);
        InOrder(root->right, In);
    }
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
 *          An int representing the index of the specific node data in In vector.
 *******************************************************************************************/
template<class T>
int SplayTree<T>::posOf(const T& data, const vector<T>& In)
{
    for (int pos = 0; pos < In.size(); pos++)
        if (In[pos] == data) return pos;

    // else, item not found, exit the program.
    std::cout << "Error: Item not found.";
    exit(-1);
}





template<class T>
void SplayTree<T>::continueRotation(SplayingNode<T>* gr, SplayingNode<T>* par,
                                    SplayingNode<T>* ch, SplayingNode<T>* desc)
{
    if (gr != 0)   // if p has a grandparent;
    {
        if (gr->right == ch->parent)
            gr->right = ch;
        else gr->left  = ch;
    }
    else root = ch;
    if (desc != 0)
        desc->parent = par;
    par->parent = ch;
    ch->parent = gr;
}

template<class T>
void SplayTree<T>::rotateR(SplayingNode<T>* p)
{
    p->parent->left = p->right;
    p->right = p->parent;
    continueRotation(p->parent->parent,p->right,p,p->right->left);
}

template<class T>
void SplayTree<T>::rotateL(SplayingNode<T>* p)
{
    p->parent->right = p->left;
    p->left = p->parent;
    continueRotation(p->parent->parent,p->left,p,p->left->right);
}

template<class T>
void SplayTree<T>::semisplay(SplayingNode<T>* p)
{
    while (p != root)
    {
        if (p->parent->parent == 0)    // if p's parent is the root;
            if (p->parent->left == p)                   /* Half splay Case 1: left */
                rotateR(p);
            else rotateL(p);                            /* Case 1 mirror: right */
        else if (p->parent->left == p) // if p is a left child;
            if (p->parent->parent->left == p->parent)   /* Half splay Case 2: left-left */
            {
                rotateR(p->parent);
                p = p->parent;
            }
            else                                        /* Half splay Case 3: right-left */
            {
                rotateR(p); // rotate p and its parent;
                rotateL(p); // rotate p and its new parent;
            }
        else                          // if p is a rigth child;
        if (p->parent->parent->right == p->parent)      /* Half splay Case 2 mirror: right-right */
        {
            rotateL(p->parent);
            p = p->parent;
        }
        else                                            /* Half splay Case 3 mirror: left-right */
        {
            rotateL(p); // rotate p and its parent;
            rotateR(p); // rotate p and its new parent;
        }
        if (root == 0)              // update the root;
            root = p;
    }
}


template<class T>
void SplayTree<T>::fullsplay(SplayingNode<T>* p)
{
    while (p != root)
    {
        if (p->parent->parent == 0)    // if p's parent is the root;
            if (p->parent->left == p)                       /* Full splay Case 1: left */
                rotateR(p);
            else rotateL(p);                                /* Full splay Case 1 mirror: right */
        else if (p->parent->left == p) // if p is a left child;
            if (p->parent->parent->left == p->parent)       /* Full splay Case 2: left-left */
            {
                rotateR(p->parent);
                rotateR(p);       //added by Chambers and Avelli 2016 spring
                // p = p->parent; //removed by Chambers Avelli 2016 spring
            }
            else                                            /* Full splay Case 3: right-left */
            {
                rotateR(p); // rotate p and its parent;
                rotateL(p); // rotate p and its new parent;
            }
        else                          // if p is a rigth child;
        if (p->parent->parent->right == p->parent)          /* Full splay Case 2 mirror: right-right */
        {
            rotateL(p->parent);
            rotateL(p);        //added by Chambers and Avelli 2016 spring
            // p = p->parent;  //removed by Chambers Avelli 2016 spring
        }
        else                                                /* Full splay Case 3 mirror: left-right */
        {
            rotateL(p); // rotate p and its parent;
            rotateR(p); // rotate p and its new parent;
        }
        if (root == 0)              // update the root;
            root = p;
    }
}




template<class T>                     // iterative version search in BST.
T* SplayTree<T>::search(const T& el)  //  T* is to return a pointer in C++.
{
    SplayingNode<T>* p = root;
    while (p != 0)
    {
        if (p->info == el)          // if el is in the tree, el is the T type info.
        {
            semisplay(p);           // move it upward;
            return &p->info;        //  &ptr would be the address for the memory location that ptr is held in. Essentially it is a pointer to a pointer.
        }
        else if (el < p->info)
            p = p->left;
        else  // el >= p->info
            p = p->right;
    }
    return 0;
}

template<class T>
void SplayTree<T>::insert(const T& el)
{
    SplayingNode<T> *p = root, *prev = 0, *newNode;
    while (p != 0)    // find a place for inserting a new node;
    {
        prev = p;
        if (el < p->info)
            p = p->left;
        else p = p->right;
    }
    if ((newNode = new SplayingNode<T>(el,0,0,prev)) == 0)
    {
        cerr << "No room for new nodes\n";
        exit(1);
    }
    if (root == 0)    // the tree is empty;
        root = newNode;
    else if (el < prev->info)
        prev->left  = newNode;
    else
        prev->right = newNode;
    fullsplay(newNode);    //added by Chambers and Avelli 2016 spring
}



#endif


