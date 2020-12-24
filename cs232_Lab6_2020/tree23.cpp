// File tree23.cpp  
// Revised -
// Two-Three-Tree Program
// Demonstrates the building of a 2-3-Tree using the important
//           functions:  add, privSearch, and split.
// Includes: Recursive printing depth-first traversal.
//           Recursive depth-first traversal with function parameter.
//           Precedes function pointer passed as parameter to the
//              traversal procedures.
//
#include <cstdio>
#include <iostream>



// The node structure class for the 2-3-Tree
template <class BD>
class TTNode
{
  public:
    BD firstInfo, secondInfo;  		// The data fields
    TTNode<BD> *firstChild, *secondChild, *thirdChild; // Child ptr fields
    TTNode<BD> *parent;                 // Pointer to parent node

};

//  The 2-3-Tree class
template <class BD>
class TTTree
{
  protected:
    TTNode<BD> *root;
    bool (*precedes)(const BD &x, const BD &y);

  private:		// Internal auxiliary functions
    void split (TTNode<BD> *&t, TTNode<BD> *tree,
	       TTNode<BD> *branch, const BD *data, bool addBranch);
    TTNode<BD> *makeTreeNode();
    bool leafNode(TTNode<BD> *t);
    void destroy(TTNode<BD> *ptr);
    bool privSearch(TTNode<BD> *rt, const BD &target,
		       BD &item, TTNode<BD> *&where);
    void RecInOrderPrint(TTNode<BD> *ptr);
    void RecInOrderTrFtn(TTNode<BD> *ptr, void (*processData)(const BD &p));

  public:
    TTTree();      // Constructor
    TTTree(bool (*precedes)(const BD &x, const BD &y)); // Constructor
    ~TTTree();         // Destructor
    bool isroot(const TTNode<BD> *ptr);
    bool search(const BD &target, BD &item);
    bool add(const BD &item);
    void split(TTNode<BD> *&t, TTNode<BD> *tree,
	       TTNode<BD> *branch, const BD &data,
	       bool addBranch);
    void InOrderPrint();  // In Order Traversal
    void InOrderTrFtn(void (*processData)(const BD &p));
}  ;

template <class BD>     // Constructor
TTTree<BD>::TTTree()
{
  root = NULL;
}

template <class BD>     // Constructor
TTTree<BD>::TTTree(bool (*precedes)(const BD &x, const BD &y))
{
  root = NULL;
  this->precedes = precedes;
}

template <class BD>     // Destructor
TTTree<BD>::~TTTree()
{
  destroy(root);
}

template <class BD>      // Helper function for destructor
void TTTree<BD>::destroy(TTNode<BD> *ptr)
{
  if (ptr == NULL)
    return;
  else
  {
    destroy(ptr->firstChild);
    destroy(ptr->secondChild);
    destroy(ptr->thirdChild);
    delete(ptr);
  }
}

template <class BD>     // Test whether ptr is the root of entire tree
bool TTTree<BD>::isroot(const TTNode<BD> *ptr)
{
  return (bool)(ptr == root);
}

template <class BD>    // Function to add item to 2-3-Tree
bool TTTree<BD>::add(const BD &item)
{
  BD info;
  bool found;
  TTNode<BD> *leaf;

  found = privSearch(root, item, info, leaf);  // Find leaf node for key

  if (leaf == NULL)
  {  // ADD:  CASE 1
    root = makeTreeNode();     // Make initial root
    root->firstInfo = item;
    return(true);
  }
  if (found)
  {  // ADD:  CASE 2
     return(false);            // Item already in tree
  }
  // Add item if it will fit in leaf. Otherwise call split to split leaf
  if ((int)(leaf->secondInfo) != NULL)
    // ADD:  CASE 3
    // Then there are two items
    split(root,leaf,leaf,item,false);
  else
	 if (precedes(leaf->firstInfo, item))
		// ADD:  CASE 4
		leaf->secondInfo = item;
	 else
	 { // ADD:  CASE 5
		leaf->secondInfo = leaf->firstInfo;
		leaf->firstInfo = item;
	 }
  return(true);
}    // end of add function

template <class BD>   // Split a node that already holds two data items
void TTTree<BD>::split(TTNode<BD> *&t,    // Pointer to root of TTTree
				 TTNode<BD> *tree,  // Pointer to node to be split
				 TTNode<BD> *branch,// Pointer to node to be added
				 const BD &data,    // Data item forcing the split
				 bool addBranch) // Indicates if branch must be
					  // added to the splitting node
{
  TTNode<BD> *parent, *sibling;
  BD key, middle;

  if (tree == t)
  { // Node referenced by tree is root, so make new parent (root) node

	 parent = makeTreeNode();
	 tree->parent = parent;
	 parent->firstChild = tree;
	 t = parent;
  }
  else
	 parent = tree->parent;

  // Make sibling node with empty flags and NULL children
  sibling = makeTreeNode();
  sibling->parent = parent;

  // Determine which of the three key values is the middle one in terms
  // of value and assign it to middle. Put/leave the smallest one in the
  // cuttent node (tree), put the largest one into the new node (sibling).
  if (precedes(data, tree->firstInfo))
  {
	 middle = tree->firstInfo;
	 tree->firstInfo = data;
	 sibling->firstInfo = tree->secondInfo;
	 tree->secondInfo = (BD) NULL;
  }
  else
	 if (precedes(data, tree->secondInfo))
	 {
		middle = data;
		sibling->firstInfo = tree->secondInfo;
		tree->secondInfo = (BD) NULL;
	 }
	 else
	 {
		sibling->firstInfo = data;
		middle = tree->secondInfo;
		tree->secondInfo = (BD) NULL;
	 }
  // If this is an interior node, four children must be taken care of (the
  // fourth is branch). Put/leave the two smallest (according to precedes
  // relation) children (subtrees) as the first two children of the old
  // node (tree), and put the two largest as the first two children of the
  // new node (sibling). In addition, update the parent pointers of the
  // children to point to the appropriate parent nodes.

  if (addBranch)
  {
	 key = branch->firstInfo;
	 if (precedes(key, tree->firstChild->firstInfo))
	 {   // ADD BRANCH: CASE 1
		sibling->secondChild = tree->thirdChild;
		sibling->firstChild = tree->secondChild;
		tree->thirdChild = NULL;
		tree->secondChild = tree->firstChild;
		tree->firstChild = branch;
		sibling->secondChild->parent = sibling;
		sibling->firstChild->parent = sibling;
		tree->firstChild->parent = tree;
	 }
	 else
		if (precedes(key, tree->secondChild->firstInfo))
		{   // ADD BRANCH: CASE 2
	sibling->secondChild = tree->thirdChild;
	sibling->firstChild = tree->secondChild;
	tree->thirdChild = NULL;
	tree->secondChild = branch;
	sibling->secondChild->parent = sibling;
	sibling->firstChild->parent = sibling;
	tree->secondChild->parent = tree;
      }
      else
	if (precedes(key, tree->thirdChild->firstInfo))
	{   // ADD BRANCH: CASE 3
	  sibling->secondChild = tree->thirdChild;
	  sibling->firstChild = branch;
	  tree->thirdChild = NULL;
	  sibling->secondChild->parent = sibling;
	  sibling->firstChild->parent = sibling;
	}
	else
	{   // ADD BRANCH: CASE 4
	  sibling->secondChild = branch;
	  sibling->firstChild = tree->thirdChild;
	  tree->thirdChild = NULL;
	  sibling->secondChild->parent = sibling;
	  sibling->firstChild->parent = sibling;
	}
  } // end if (addBranch)

  // Now "promote" middle up to the tree's parent node and determine whether
  // that node must be split.  If middle will fit, arrange the parent node
  // accordingly and return. If not, then make a recursive call to split with
  // the parent node as tree, the sibling node as branch, and middle as data.

  if ((int) (parent->firstInfo) == NULL)  // Then firstInfo is empty flag
  {   // ACTION AT PARENT: CASE A
    parent->firstInfo = middle;
    parent->firstChild = tree;
    parent->secondChild = sibling;
    return;
  }
  if ((int) (parent->secondInfo) != NULL)
  {   // ACTION AT PARENT: CASE B
    split(t, parent, sibling, middle, true);
    return;
  }
  if (precedes(parent->firstInfo, middle))
  {   // ACTION AT PARENT: CASE C
    parent->secondInfo = middle;
    parent->thirdChild = sibling;
    return;
  }
  // ACTION AT PARENT: CASE D
  parent->secondInfo = parent->firstInfo;
  parent->firstInfo = middle;
  parent->thirdChild = parent->secondChild;
  parent->secondChild = sibling;
} // end of split function


template <class BD>   // Make a new empty 2-3-Tree node
TTNode<BD> *TTTree<BD>::makeTreeNode()
{
  TTNode<BD> *p;

  p = new TTNode<BD>;
  p->parent = NULL;
  p->firstChild = NULL;
  p->secondChild = NULL;
  p->thirdChild = NULL;
  p->firstInfo = (BD) NULL;
  p->secondInfo = (BD) NULL;
  return(p);
}

template <class BD>   // Test whether a node is a leaf node
bool TTTree<BD>::leafNode(TTNode<BD> *t)
{
  if ((t->firstChild == NULL) && (t->secondChild == NULL) &&
      (t->thirdChild == NULL))
    return (true);
  else
    return (false);
}

template <class BD> // Search for target in 2-3-Tree and return item found
bool TTTree<BD>::search(const BD &target, BD &item)
{
  TTNode<BD> *where;

  // Just pass the root pointer to the recursive workhorse function
  return(privSearch(root, target, item, where));
}

template <class BD>
bool TTTree<BD>::privSearch(TTNode<BD> *rt,  // pointer to root of TTTree
			const BD &target,  // what we are searching for
			BD &item,      // item returned matching target
			TTNode<BD> *&where) // node ptr where target is found
{
  bool found, atLeastOneItem, twoItems;

  if (rt == NULL)   // target will not be found in the empty tree
  {
    where = NULL;
    return(false);
  }
  found = false;
  // NULL is used as an empty flag in informational field.
  // Type casting allows comparision of BD variable to NULL.
  if (((int) (rt->firstInfo)) != NULL)
    atLeastOneItem = true;
  else
    atLeastOneItem = false;
  if (((int) (rt->secondInfo)) != NULL)
    twoItems = true;
  else
    twoItems = false;

  if (atLeastOneItem)
    if (rt->firstInfo == target)   // Check first key
    {
      found = true;
      item = rt->firstInfo;
    }
    else
      if (twoItems)
	if (rt->secondInfo == target)  // Check second key
	{
	  found = true;
	  item = rt->secondInfo;
	}
  // If target was found at rt or rt references a leafnode, return where as rt
  if (found || leafNode (rt))
  {
    where = rt;
    return(found);
  }
  // If reach this point, there must be at least one item in the node, so
  // make recursive call(s) to search appropriate subtree(s)
  if (precedes(target, rt->firstInfo))
    return(privSearch(rt->firstChild, target, item, where));
  if (!twoItems)
    return(privSearch(rt->secondChild, target, item, where));
  if (precedes(target, rt->secondInfo))
    return(privSearch(rt->secondChild, target, item, where));
  else
    return(privSearch(rt->thirdChild, target, item, where));
}

template <class BD>
void TTTree<BD>::RecInOrderTrFtn(TTNode<BD> *ptr,
			      void (*processData)(const BD &p))
{
  if (ptr == NULL)
    return;
  else
  { RecInOrderTrFtn(ptr->firstChild, processData);
    processData(ptr->firstInfo);
    RecInOrderTrFtn(ptr->secondChild, processData);
    processData(ptr->secondInfo);
    RecInOrderTrFtn(ptr->thirdChild, processData);
  }
}

template <class BD>
void TTTree<BD>::InOrderTrFtn(void (*processData)(const BD &p))
{
  RecInOrderTrFtn(root, processData);
  return;
}

template <class BD>
void TTTree<BD>::RecInOrderPrint(TTNode<BD> *ptr)
{
  if (ptr == NULL)
    return;
  else
  { cout << "(";
    RecInOrderPrint(ptr->firstChild);
    cout << " " << ptr->firstInfo << " ";
    RecInOrderPrint(ptr->secondChild);
    cout << " " << ptr->secondInfo << " ";
    RecInOrderPrint(ptr->thirdChild);
    cout << ")";
  }
}

template <class BD>
void TTTree<BD>::InOrderPrint()
{
  RecInOrderPrint(root);
  cout << endl;
  return;
}

// integer comparison function
bool int_less (const int &x, const int &y)
{ return ((bool) (x < y));
}

// integer print function
void int_print (const int &x)
{  cout << x << " ";
   return;
}

bool char_less (const char &x, const char &y)
{ return ((bool) (x < y));
}

void char_print (const char &x)
{  cout << x << " ";
   return;
}

//*********************** Main Program Function ******************

int main()
{
  TTTree<int> T1(int_less);

  const int numbInts = 18;
  const int ArySize = 30;
  int Numb[ArySize] = {190,30,100,150,180,120,200,130,50,
						40,60,80,70,210,220,160,20,140};
  cout << endl
    << "Two-Three-Tree Program" << endl
    << "This program uses a recursive in-order traversal to display" << endl
    << "a trace of the building of the Two-Tree-Tree (2-3-Tree) as" << endl
    << "additions are made to the tree."  << endl
    << "Parentheses are used to enclose each node." << endl
    << "Since each subtree of a node is nested within its displayed" << endl
    << "parent node, the parentheses actually enclose each tree and" << endl
    << "subtree." << endl
    << "Integer data is used in this demo, and each empty info field" << endl
    << "is shown as a 0." << endl << endl;

  for( int i=0; i<numbInts; i++)
  {   cout << "Adding: " << Numb[i] << endl;
      T1.add(Numb[i]);
      T1.InOrderPrint();
      cout << "Hit the Enter key to continue..." << endl;
      // hold window open here
  }

  cout << "Recursive in-order traversal passing print function:" << endl;
  T1.InOrderTrFtn(int_print);

  cout << endl << endl << "End of program" << endl << endl;
  
  
 return 0; 
 
}














