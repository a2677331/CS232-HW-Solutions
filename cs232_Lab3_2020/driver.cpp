/**************************************************************************
* File name: driver.cpp
* This file contains codes for testing the AVL rotations
*     by displaying the depth and breadth first traversals.
* Programmer: Jian Zhong
* Date Written: 09/21/2020
* Date Last Revised: 09/22/2020
* *************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "AvlTree.h"

int preceed (const char& c1, const char& c2)
{
    return  c1 - c2;
}


bool preceed2 (const int &x, const int &y)
{
    return x <= y;
}


void dump(char & value)
{
    cout << value;
}

void dump2( int & value)
{
    cout << value << "  ";
}


int main()
{
    cout << " \nAVL Tree: "  << endl;

    AvlTree<int> t7( preceed2 );
    t7.add( 60 );
    t7.add( 80 );
    t7.add( 30 );
    t7.add( 90 );
    t7.add( 70 );
    t7.add( 100 );
    t7.add( 40 );
    t7.add( 20 );
    t7.add( 50 );
    t7.add( 10 );

    cout << " t7 printing depth first traversal: \n ";
    t7.depthFirstTraversal( dump2);

    cout << endl << endl;

    cout << " t7 printing breadth first traversal: \n ";
    t7.breadthFirstTraversal( dump2);

    cout << "\n\nHave a good day!\n";

    return (0);
}

/************ Console Output *****************
*
*  AVL Tree:
*  t7 printing depth first traversal
*  80  40  20  10  30  60  50  70  90  100
*
*  t7 printing breadth first traversal
*  80  40  90  20  60  100  10  30  50  70
*
*  Have a good day!
*
**********************************************/
