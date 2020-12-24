/**************************************************************************
 * File name: lab8Driver.cpp
 * -------------------------
 * This file contains driver code for 234_tree.h file.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/30/2020
 * Date Last Revised: 10/31/2020
**************************************************************************/

#include <iostream>
#include "234_tree.h"
using namespace std;

int myCompare(const int& x, const int& y) {      // comparison function
    return x - y;
}

void processNode(int& item) {                   // how to output the node
    cout << " " << item << "  ";
}

/* Main function */
int main()
{
    const int dataSize = 13;                                        // # of item
    int data[dataSize] = {60,50,70,40,80,30,90,20,100,10,66,44,33}; // item to be added
    TwoThreeFourTree<int> my234Tree(myCompare);                     // construct a 234 tree

    for (int i : data)
    {
        cout << "\nAdding: \"" << i << "\": \n";  // prompt msg for adding action
        my234Tree.add(i);                         // add data
        my234Tree.drawGraph(processNode);         // draw graph by level.
    }

    return 0;
} /* end of Main */

/************************  Answer  ********************************
 * In add( ):
 * Line 355 is the Case A: inserting into a 4-node root.
 * Line 363 is the Case B: parent of the 4-node is a 2-node.
 * Line 365 is the Case C: parent of the 4-node is a 3-node.
 *
 * In splitChildOf2( ):
 * Line 479 is the Case B1: the 4-node is its parent's 1st child.
 * Line 493 is the Case B2: the 4-node is its parent's 4th child.
 *
 * Line 517 is the Case C1: the 4-node is its parent's 1st child.
 * Line 533 is the Case C2: the 4-node is its parent's 2nd child.
 * Line 547 is the Case C3: the 4-node is its parent's 4th child.
 ******************************************************************/

/************************ Console Output  *************************
Adding: "60":
 60

Adding: "50":
 50   60

Adding: "70":
 50   60   70

Adding: "40":
     60
 40   50     70

Adding: "80":
     60
 40   50     70   80

Adding: "30":
       60
 30   40   50     70   80

Adding: "90":
       60
 30   40   50     70   80   90

Adding: "20":
     40     60
 20   30     50     70   80   90

Adding: "100":
     40     60     80
 20   30     50     70     90   100

Adding: "10":
           60
       40         80
 10   20   30     50     70     90   100

Adding: "66":
           60
       40           80
 10   20   30     50     66   70     90   100

Adding: "44":
             60
       40             80
 10   20   30     44   50     66   70     90   100

Adding: "33":
               60
   20       40             80
 10     30   33     44   50     66   70     90   100
******************************************************************/
