/**************************************************************************
 * File name: p3driver.cpp
 * -----------------------
 * Menu/Prompt-driven test driver for Graph class.
 *
 * The program demonstrates the use of the Graph class
 * for directed graph, undirected graph
 * and graph imported from file.
 *
 * This driver uses a string vertex and edges with an integer weight.
 *
 * Programmer: Jian Zhong
 * Date Written: 11/15/2020
 * Date Last Revised: 11/20/2020
**************************************************************************/
#include <iostream>
#include <string>
#include "myGraphADT.h"

using namespace std;

/* Function Prototypes */
template<typename T>
void verifyInput(T&);                                // Input option validation
bool show_main_menu();                               // Main Menu
void dg_menu();                                      // Operation menu for directed graph
void ug_menu();                                      // Operation menu for undirected graph
void perform_directed(Graph<string,int>&, bool&);    // Demo directed graph
void perform_undirected(Graph<string,int>&, bool&);  // Demo undirected graph
void perform_imported(Graph<string,int>&, bool&);    // Demo text imported graph
void checkSameVertices(string&, string&);            // Check to if the two vertices are the same


/* Main Program  */
int main()
{
    // Print greetings
    cout << "----------------------------------------------------------------\n"
         << "Welcome to CS 232 Project 3!\n"
         << "This menu driven program demonstrates the use\n"
         << "of the Graph class for directed graph, undirected graph \n"
         << "and graph imported from file.\n\n"
         << "You will be given options to choose which graph to use.\n"
         << "Inputs are one of D U I E, lowercase is also accepted.\n\n"
         << "Bug fixed: fixed an issue that causes infinite loop in \n"
         << "Dijkstra's shortest function, it happens when the function is \n"
         << "executed more than once in one run.\n"
         << "-----------------------------------------------------------------\n";

    // Repeatedly show Main Menu until user indicates to stop
    while ( show_main_menu() )
        show_main_menu();

    // Farewell Msg
    cout << "\nHave a nice day!\n";
    return 0;
} /* end of main program */


/*******************************************************************************************
 * Function Name: show_main_menu()
 *
 * Purpose: function to show main menu for user to choose a specified kind of a graph for
 *          demonstration, the menu will repeatedly prompt user for input.
 * Input Parameters:  none.
 * Output parameters: none.
 * Return Value:
 *          return ture if neither 'E' nor 'e' was entered.
 *          return false if 'E' or 'e' was entered.
 *******************************************************************************************/
bool show_main_menu()
{
    bool undone = true;  // Operation menu action signal

    // Print main menu
    cout << "\nMain Menu: \n"
         << "  (D)irected Graph\n"
         << "  (U)ndirected Graph\n"
         << "  (I)mport Graph from a text\n"
         << "  (E)xit\n"
         << "Which kind of graph would you like: ";

    string op1;   // option for main menu
    getline(cin>>ws, op1);     // eat up all whitespaces before getline read                                //⚠️ 搞了很久，不能将cin和getline混用，也可以用cin.ignore！！！！！！！！！！！！！！
    if (op1 == "D" || op1 == "d")          // Case 1: demo directed graph
    {
        Graph<string,int> dg;  // directed graph
        while (undone)
            perform_directed(dg, undone);   // show Operation menu for directed graph                      // ⚠️ ⚠️ 搞了很久这里不能用return，要不然直接终止！
    }
    else if (op1 == "U" || op1 == "u")     // Case 2: demo un-directed graph
    {
        Graph<string,int> ug;   // undirected graph
        while (undone)
            perform_undirected(ug, undone); // show Operation menu for undirected graph
    }
    else if (op1 == "I" || op1 == "i")     // Case 3: demo imported graph
    {
        Graph<string,int> ig;  // graph imported from text file
        ig.GetGraph();
        cout << "Graph file Loaded.\n";
        while (undone)
            perform_imported(ig, undone);  // show Operation menu for imported graph
    }
    else if (op1 == "E" || op1 == "e")     // Case 4: exit the program
        return false;
    else                                   // Case 5: invalid input, prompt error msg
        cout << "Invalid letter option, please enter D U I E.\n";

    return true;
}


/*******************************************************************************************
 * Function Name: dg_menu
 *
 * Purpose: function to print directed graph operation menu.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void dg_menu()
{
    cout << "\n<--0) Back to Main Menu\n"
        << "   1) Print graph state\n"
        << "   2) Add a vertex\n"
        << "   3) Delete a vertex\n"
        << "   4) Add a directional edge\n"
        << "   5) Delete a directional edge\n"
        << "   6) Test if a directional edge exists\n"
        << "   7) Test if a vertex exists\n"
        << "   8) BFS\n"
        << "   9) Recursive DFS\n"
        << "  10) Find Dijkstra's shortest path\n"
        << "  11) Find Ford's shortest path (New)\n"
        << "  12) Iterative DFS (New)\n"
        << "Which option: ";
}

/*******************************************************************************************
 * Function Name: verifyInput
 *
 * Purpose: function to verify input, user is given unlimited
 *          chances to enter a legal input.
 *
 * Input Parameters:
 *          input: input of char type.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
template<typename T>
void verifyInput(T& input)
{
    while (!cin || (cin.peek() != '\n'))
    {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Invalid input, try again: ";
        cin >> input;
    }
}

/*******************************************************************************************
 * Function Name: checkSameVertices
 *
 * Purpose: function to check if the two vertices are the same name.
 *
 * Input Parameters:
 *          v1: vertex name of v1
 *          v2: vertex name of v2
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void checkSameVertices(string& v1, string& v2)
{
    while (true)
    {
        cout << "Starting vertex: ";
        cin >> v1;
        verifyInput(v1);
        cout << "Ending vertex: ";
        cin >> v2;
        verifyInput(v2);
        if (v1 != v2) break;
        cout << "The two vertices are the same, try again.\n";
    }
}


/*******************************************************************************************
 * Function Name: perform_directed
 *
 * Purpose: function to perform demonstration of directed graph.
 *
 * Input Parameters:
 *          dg: directed graph object.
 *          undone: indicate if user wants to show the directed menu.
 *
 * Output parameters:
 *          dg: the graph may be modified by user from the
 *              operations of the directed menu.
 *          undone: return true/false depending if user wants to continue the menu.
 *
 * Return Value: none.
 *******************************************************************************************/
void perform_directed(Graph<string,int>& dg, bool& undone)
{
    string v1, v2;        // vertex name
    int weight, op2;      // edge weight and menu option number

    dg_menu();            // show directed graph menu
    cin >> op2;           // read in menu option number
    verifyInput(op2);  // check if input is valid
    switch (op2)
    {
        case 0:           // go back to main menu
            undone = false;
            break;
        case 1:           // add a vertex
            dg.SimplePrintGraph();
            cout << endl;
            break;
        case 2:           // add a vertex
            cout << "Vertex name: ";
            cin >> v1;
            verifyInput(v1);
            if (dg.AddVertex(v1) == -1)
                cout << "Can't add: " << v1 << " already exists.\n";
            else
                cout << "Added.\n";
            break;
        case 3:          // delete a vertex
            cout << "Vertex name: ";
            cin >> v1;
            verifyInput(v1);
            if (dg.DeleteVertex(v1) == -1)
                cout << "Can't delete: " << v1 << " is NOT in the graph.\n";
            else
                cout << "Deleted.\n";
            break;
        case 4:          // add a directed edge
            checkSameVertices(v1, v2);
            cout << "Edge weight: ";
            cin >> weight;
            verifyInput(weight);
            if (dg.AddUniEdge(v1, v2, weight) == -1)
                cout << "Can't add: Edge <" << v1 << "," << v2 << "> already exists.\n";
            else
                cout << "Added.\n";
            break;
        case 5:         // delete a directed edge
            checkSameVertices(v1, v2);
            if (dg.DeleteUniEdge(v1, v2) == -1)
                cout << "Can't delete: Edge <" << v1 << ","
                     << v2 << "> is NOT in the graph.\n";
            else
                cout << "Deleted.\n";
            break;
        case 6:         // Test if a directed edge exists
            checkSameVertices(v1, v2);
            if (dg.isUniEdge(v1, v2) == -1)
                cout << "Edge <" << v1 << "," << v2 << "> is NOT in the graph.\n";
            else
                cout << "Edge <" << v1 << "," << v2 << "> is in the graph.\n";
            break;
        case 7:         // Test if a vertex exists
            cout << "Vertex name: ";
            cin >> v1;
            verifyInput(v1);
            if (dg.isVertex(v1) == -1)
                cout << "Vertex "<< v1 << " is NOT in the graph.\n";
            else
                cout << "Vertex "<< v1 << " is in the graph.\n";
            break;
        case 8:         // BFS
            cout << "BFS from vertex: ";
            cin >> v1;
            verifyInput(v1);
            dg.BFTraversal(v1);
            cout << endl;
            break;
        case 9:         // Recursive version of DFS
            cout << "Recursive DFS from vertex: ";
            cin >> v1;
            verifyInput(v1);
            dg.DepthFirstTraversal(v1);
            cout << endl;
            break;
        case 10:        // Find shortest path by Dijkstra's algorithm
        {
            checkSameVertices(v1, v2);
            double dist = dg.ShortestDistance(v1, v2);
            if (dist == -1)           // check to see if v1 exists
                cout << "Can't find: Vertex " << v1 << " is NOT in the graph.\n";
            else if (dist == -2)      // check to see if v2 exists
                cout << "Can't find: Vertex " << v2 << " is NOT in the graph.\n";
            else if (dist == -3)      // check to see if path exists
                cout << "No path from " << v1 << " to " << v2 << ".\n";
            else                      // print path
                cout << "\nShortest distance from " << v1
                     << " to " << v2 << " is: " << dist << endl;
            break;
        }
        case 11:        // Find shortest path by Ford's algorithm (new)
        {
            cout << "Starting vertex: ";
            cin >> v1;
            verifyInput(v1);
            cout << "----------------------- Ford Trace Information -----------------------\n";
            dg.FordShortestPaths(v1);
            break;
        }
        case 12:        // Perform iterative version of DFS (new)
        {
            cout << "Iterative DFS from vertex: ";
            cin >> v1;
            verifyInput(v1);
            dg.DFTraversal(v1);
            cout << endl;
            break;
        }
        default:
            cout << "Invalid option number: please enter 1 ~ 12.\n";
            break;
    }
}

/*******************************************************************************************
 * Function Name: ug_menu
 *
 * Purpose: function to print undirected graph operation menu.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void ug_menu()
{
    cout << "\n<--0) Back to Main Menu\n"
         << "   1) Print graph state\n"
         << "   2) Add a vertex\n"
         << "   3) Delete a vertex\n"
         << "   4) Add a bidirectional edge\n"
         << "   5) Delete a bidirectional edge\n"
         << "   6) Test if a bidirectional edge exists\n"
         << "   7) Test if a vertex exists\n"
         << "   8) BFS\n"
         << "   9) Recursive DFS\n"
         << "  10) Find Dijkstra's shortest path\n"
         << "  11) Find Ford's shortest path (New)\n"
         << "  12) Find MST (New)\n"
         << "  13) Iterative DFS (New)\n"
         << "Which option: ";
}


/*******************************************************************************************
 * Function Name: perform_undirected
 *
 * Purpose: function to perform demonstration of undirected graph.
 *
 * Input Parameters:
 *          ug: undirected graph object.
 *          undone: indicate if user wants to show the undirected menu.
 *
 * Output parameters:
 *          ug: the graph may be modified by user from the
 *              operations of the undirected menu.
 *          undone: return true/false depending if user wants to continue the menu.
 *
 * Return Value: none.
 *******************************************************************************************/
void perform_undirected(Graph<string,int>& ug, bool& undone)
{
    string v1, v2;        // vertex name
    int weight, op2;      // edge weight and menu option number

    ug_menu();            // show undirected graph menu
    cin >> op2;           // read in menu option number
    verifyInput(op2);  // check if input is valid
    switch (op2)          // maps user input op2 to 10 different operations.
    {
        case 0:           // go back to main menu
            undone = false;
            break;
        case 1:           // print graph state
            ug.SimplePrintGraph();
            cout << endl;
            break;
        case 2:           // add a vertex
            cout << "Vertex name: ";
            cin >> v1;
            verifyInput(v1);
            if (ug.AddVertex(v1) == -1)
                cout << "Can't add: " << v1 << " already exists.\n";
            else
                cout << "Added.\n";
            break;
        case 3:           // delete a vertex
            cout << "Vertex name: ";
            cin >> v1;
            verifyInput(v1);
            if (ug.DeleteVertex(v1) == -1)
                cout << "Can't delete: " << v1 << " is NOT in the graph.\n";
            else
                cout << "Deleted.\n";
            break;
        case 4:          // add an undirected edge
        {
            checkSameVertices(v1, v2);
            cout << "Edge weight: ";
            cin >> weight;
            verifyInput(weight);
            int addBiEdge = ug.AddBiDirEdge(v1, v2, weight);
            if (addBiEdge == -3)        // (v1,v2) already exists.
                cout << "Can't add: Edge (" << v1 << "," << v2 << ") already exists.\n";
            else if (addBiEdge == -2)   //  <v1,v2> added, <v2,v1> already exists.
                cout << "Edge <" << v1 << "," << v2 << "> added, "
                     << "Edge <" << v2 << "," << v1 << "> already exists.\n";
            else if (addBiEdge == -1)   //  <v1,v2> already exists, <v2,v1> added.
                cout << "Edge <" << v2 << "," << v1 << "> added, "
                     << "Edge <" << v1 << "," << v2 << "> already exists.\n";
            else                        //  (v1,v2) successfully added.
                cout << "Added.\n";
            break;
        }
        case 5:         // delete an undirected edge
        {
            checkSameVertices(v1, v2);
            int delBiEdge = ug.DeleteBiDirEdge(v1, v2);
            if (delBiEdge == -3)        //  (v1,v2) does not exists.
                cout << "Can't delete: Edge (" << v1 << "," << v2 << ") is NOT in the graph.\n";
            else if (delBiEdge == -2)   //  <v1,v2> deleted, <v2,v1> doesn't exist.
                cout << "Edge <" << v1 << "," << v2 << "> deleted, "
                     << "Edge <" << v2 << "," << v1 << "> is NOT in the graph.\n";
            else if (delBiEdge == -1)   //  <v1,v2> doesn't exist, <v2,v1> deleted.
                cout << "Edge <" << v2 << "," << v1 << "> deleted, "
                     << "Edge <" << v1 << "," << v2 << "> is NOT in the graph.\n";
            else                        //  (v1,v2) successfully deleted.
                cout << "Deleted.\n";
            break;
        }
        case 6:         // test if an undirected edge exists
            checkSameVertices(v1, v2);
            if (ug.isBiDirEdge(v1, v2) == -1)
                cout << "Edge (" << v1 << "," << v2 << ") is NOT in the graph.\n";
            else
                cout << "Edge (" << v1 << "," << v2 << ") is in the graph.\n";
            break;
        case 7:         // Test if a vertex exists
            cout << "Vertex name: ";
            cin >> v1;
            verifyInput(v1);
            if (ug.isVertex(v1) == -1)
                cout << "Vertex "<< v1 << " is NOT in the graph.\n";
            else
                cout << "Vertex "<< v1 << " is in the graph.\n";
            break;
        case 8:         // BFS
            cout << "BFS from vertex: ";
            cin >> v1;
            verifyInput(v1);
            ug.BFTraversal(v1);
            cout << endl;
            break;
        case 9:         // Recursive DFS
            cout << "Recursive DFS from vertex: ";
            cin >> v1;
            verifyInput(v1);
            ug.DepthFirstTraversal(v1);
            cout << endl;
            break;
        case 10:        // Find shortest path
        {
            checkSameVertices(v1, v2);
            double dist = ug.ShortestDistance(v1, v2);
            if (dist == -1)           // check to see if v1 exists
                cout << "Can't find: Vertex " << v1 << " is NOT in the graph.\n";
            else if (dist == -2)      // check to see if v2 exists
                cout << "Can't find: Vertex " << v2 << " is NOT in the graph.\n";
            else if (dist == -3)      // check to see if path exists
                cout << "No path from " << v1 << " to " << v2 << ".\n";
            else                      // print path
                cout << "\nShortest distance from " << v1
                     << " to " << v2 << " is: " << dist << endl;
            break;
        }
        case 11:        // Find shortest path by Ford(new)
        {
            cout << "Starting vertex: ";
            cin >> v1;
            verifyInput(v1);
            cout << "\n----------------------- Ford Trace Information -----------------------\n";
            ug.FordShortestPaths(v1);
            break;
        }
        case 12:        // Find minimum spanning tree(new)
        {
            ug.mst();
            break;
        }
        case 13:       // Perform iterative version of DFS (new)
        {
            cout << "Iterative DFS from vertex: ";
            cin >> v1;
            verifyInput(v1);
            ug.DFTraversal(v1);
            cout << endl;
            break;
        }
        default:
            cout << "Invalid option number: please enter 1 ~ 13.\n";
            break;
    }
}


/*******************************************************************************************
 * Function Name: perform_imported
 *
 * Purpose: function to perform demonstration of imported graph,
 *          the graph can be defined by either directed or undirected depending
 *          by user input.
 *
 * Input Parameters:
 *          ig: imported graph object.
 *          undone: indicate if user wants to show the imported menu.
 *
 * Output parameters:
 *          ig: the graph may be modified by user from the
 *              operations of the imported menu.
 *          undone: return true/false depending if user wants to continue the menu.
 *
 * Return Value: none.
 *******************************************************************************************/
void perform_imported(Graph<string,int>& ig, bool& undone)
{
    cout << "\n<--0) Back to Menu Menu\n"   // show menu
         << "   1) Directed\n"
         << "   2) Undirected\n"
         << "Which option: ";

    int input;                 // user input option
    cin >> input;
    verifyInput(input);     // verify input
    switch (input)             // maps input to menu options
    {
        case 0:
            undone = false;
            break;
        case 1:                // perform directed graph for the imported graph
            while (undone)
                perform_directed(ig, undone);
            break;
        case 2:
            while (undone)    // perform undirected graph for the imported graph
                perform_undirected(ig, undone);
            break;
        default:
            cout << "Invalid option number: please enter 0, 1, 2.\n";
            break;
    }
}
