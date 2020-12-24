/**************************************************************************
 * File name: lab7Driver.cpp
 * -------------------------
 * This file contains codes for interface of generic splaying tree.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/21/2020
 * Date Last Revised: 10/23/2020
**************************************************************************/

#include <iostream>
#include "splay.h"
using namespace std;

int main()
{
    SplayTree<int> myTree;  // an user-defined splay tree
    const int size1 = 10;   // array 1 size
    int arr1[size1] = {60, 80, 30, 90, 70, 100, 40, 20, 50, 10}; // an array of items to be added
    const int size2 = 3;    // array 2 size
    int arr2[size2] = {30, 100, 60}; // an array of items to be searched

    // Add 60 80 30 90 70 100 40 20 50 10 and display after each insertion:
    cout << "------------------ Adding Section ----------------------" << endl;
    for (int item : arr1)
    {
        cout << "Adding: " << item << endl;
        myTree.insert(item); // Inserting a node
        cout << "Displaying the tree by level: " << endl;
        myTree.drawGraph();       // Display tree by level
    }

    // Search for 30, 100, 60 and display after each search:
    cout << "------------------ Searching Section --------------------" << endl;
    for (int item : arr2)
    {
        cout << "Searching: " << item << endl;
        myTree.search(item); // Searching for a node
        cout << "Displaying the tree by level: " << endl;
        myTree.drawGraph();       // Display tree by level
    }

    return 0;
}

/************************  Answer  ********************************
 * In semisplay( ):
 * Line 107 from unmodified splay.h is a case 1 left rotation.
 * Line 109 from unmodified splay.h is a case 1 right rotation.
 * Line 111 from unmodified splay.h is a case 2 left of left rotation.
 * Line 116 from unmodified splay.h is a case 3 left of right rotation.
 * Line 122 from unmodified splay.h is a case 2 right of right rotation.
 * Line 127 from unmodified splay.h is a case 3 right of left rotation.
 *
 *
 * In fullsplay( ):
 * Line 149 from unmodified splay.h is a case 1 left rotation.
 * Line 151 from unmodified splay.h is a case 1 right rotation.
 * Line 153 from unmodified splay.h is a case 2 left of left rotation.
 * Line 159 from unmodified splay.h is a case 3 left of right rotation.
 * Line 165 from unmodified splay.h is a case 2 right of right rotation.
 * Line 171 from unmodified splay.h is a case 3 right of left rotation.
 */


/************************  Console Output  ************************

 ------------------ Adding Section ----------------------
Adding: 60
Displaying the tree by level:
60

Adding: 80
Displaying the tree by level:
 80
/
60

Adding: 30
Displaying the tree by level:
30
 \
 60
  \
  80

Adding: 90
Displaying the tree by level:
   90
  /
30
 \
  80
 /
 60

Adding: 70
Displaying the tree by level:
  70
 / \
30   90
 \ /
 60 80

Adding: 100
Displaying the tree by level:
     100
    /
    90
   /
  70
 / \
30  80
 \
 60

Adding: 40
Displaying the tree by level:
 40
/ \
30     100
     /
   70
  / \
  60  90
    /
    80

Adding: 20
Displaying the tree by level:
20
 \
 30
  \
  40
   \
       100
      /
    70
   / \
   60  90
     /
     80

Adding: 50
Displaying the tree by level:
   50
  / \
 30      100
/ \    /
20 40 60
     \
     70
      \
       90
      /
      80

Adding: 10
Displaying the tree by level:
10
 \
    50
   / \
 20       100
  \     /
  30  60
   \  \
   40  70
       \
        90
       /
       80

------------------ Searching Section --------------------
Searching: 30
Displaying the tree by level:
  30
 / \
10   50
 \ / \
 20 40     100
        /
     60
      \
      70
       \
        90
       /
       80

Searching: 100
Displaying the tree by level:
    50
   / \
  30      100
 / \    /
10  40 60
 \    \
 20    70
       \
        90
       /
       80

Searching: 60
Displaying the tree by level:
     60
    / \
    50    100
   /    /
  30   70
 / \   \
10  40    90
 \     /
 20     80

*************************************************************/
