/**********************************************************************
 * File name: myGraphADT.h
 * -----------------------
 * This file defines the Graph class, which implements the Graph ADT.
 *
 * The Graph class uses an adjacency list to store vector vertices,
 * each vertices contains linked edge list.
 *
 * The graph class is template based so that the user may decide
 * what types of object should be used as vertices and edge weight.
 *
 * This file defines the
 *      Graph class:  implements the Graph ADT.
 *      vertex type:  supplied type for a vertex in a graph.
 *      edgeRep type: supplied type for an edge in a graph.
 *
 * Programmer: Jian Zhong
 * Date Written: 11/15/2020
 * Date Last Revised: 11/20/2020
 **********************************************************************/

#ifndef MYGRAPHADT_H
#define MYGRAPHADT_H

#include <list>     // list<edge> edgeList;
#include <vector>   // vector<vertexT> G;   vector<vertexT* > toBeChecked;
#include <iostream> // cin, cout, getline
#include <fstream>  // inFile
#include <queue>    // queue<vertexT* > Q;
#include <stack>    // path
#include <cfloat>   // DBL_MAX
#include <string>   // filePath
#include <iomanip>  // setw()
#include <deque>    // deque<vertexT* > toBeChecked
using namespace std;


/* Forward references to these two types so */
/* that the compiler can recognize them. */
template <typename V, typename W>
struct edgeRep;
template <typename V, typename W>
struct vertex;

// This value represents the infinity value in the Graph ADT.
const double INF = 9999.0;

/*
 * Type: Graph
 * ------------
 * This type represents a graph implemented
 * by adjacent list representation.
 * V is the vertex class; W is edge weight class.
 */
template <typename V, typename W>
class Graph
{
protected:
    typedef vertex<V, W> vertexT;  // for convenience
    typedef edgeRep<V, W> edgeT;   // for convenience

    vector<vertexT> G;             // Main graph vector for adjacency list representation
    Graph<V,W>* minTree;           // Pointer to Minimum spanning tree

    /* Print path from a given vertex in the graph */
    void printPath(vertexT* vertex);

    /* Get the vertex with minimum current
     * distance and remove it from vec collection */
    vertexT* minimumOf(vector<vertexT*>& vec);

    /* To open a file from specified file path */
    void inputFile(ifstream& inFile);

    /* Reset all vertices' visited flags back to unvisited */
    void resetVisitFlag();

    /* Recursive utility that does the actual work for DepthFirstTraversal */
    void recDFT(vertexT* v);

    /* Get total distance from v to its neighbor w in mst( ) */
    W distOf(const int& v, const int& w, const vector<vertexT>& g);

    /* Get total distance from the dist array in mst( ) */
    W sumOf(const vector<W>& dist);

    /* Print trace info for mst( ) */
    void printMst(const vector<bool>& comp, const vector<W>& dist,
                  const vector<V>& neigh, int& count);

    /* Print DeQ trace information */
    void printDeQ(const deque<vertexT*>& DeQ) const;

    /* Reset all flags of each vertex in graph back to default */
    void resetAllFlags();

public:
    /* Constructor */
    Graph();

    /* Destructor */
    ~Graph();

    /* Return the current number of vertices in the graph */
    int vertexCount() const;

    /* Test whether v is a vertex in the graph */
    int isVertex(V& v) const;

    /* Tests whether a directed edge <v1,v2> is in the graph */
    int isUniEdge(V& v1, V& v2) const;

    /* Deletes the directed edge <v1,v2> from the graph */
    int DeleteUniEdge(V& v1, V& v2);

    /* Adds the directed edge <v1,v2,wt> to the graph */
    int AddUniEdge(V& v1, V& v2, W& wt);

    /* Adds vertex with name v to the graph */
    int AddVertex(V& v);

    /* Deletes vertex v from the graph */
    int DeleteVertex(V& v);

    /* Tests whether an undirected edge (v1,v2) is in the graph */
    int isBiDirEdge(V& v1, V& v2) const;

    /* Adds the bi-directional edge (v1,v2,wt) to the graph */
    int AddBiDirEdge(V& v1, V& v2, W& wt);

    /* Deletes the bi-directional edge (v1,v2) to the graph */
    int DeleteBiDirEdge(V& v1, V& v2);

    /* Prints the adjacent list of the graph in parenthesized notation */
    void SimplePrintGraph() const;

    /* Setup the graph from a special format file */
    void GetGraph();

    /* Find shortest path with path and distance printed */
    double ShortestDistance(V& v1, V& v2);

    /* Performs BFT with information printed */
    void BFTraversal(V& v);

    /* A recursive version of DFS traversal from a given vertex */
    void DepthFirstTraversal(V& v);

    /* An iterative version of DFS traversal from a given vertex */
    void DFTraversal(V& v);

    /* Determine the minimum spanning tree using Prim's algorithm */
    void mst();

    /* Determines the shortest paths to all other vertices from the specified vertex */
    void FordShortestPaths(V &v);

}; /* end of Graph class */


/*
 * Type: edgeRep
 * -------------
 * This type is the supplied type for an edge in a graph.
 */
template <typename V, typename W>
struct edgeRep
{
    typedef edgeRep<V, W> edge;     // for convenience
    edgeRep(V n, W w)               // edgeRep Constructor
    {
        name = n;
        weight = w;
    }

    V name;                         // Endpoint's Vertex name
    W weight;                       // Edge weight

    // Overload operators for edgeList removals and sorts.
    bool operator == (const edge& e) const { return name == e.name; }
    bool operator != (const edge& e) const { return name != e.name; }
    bool operator < (const edge& rhs) const { return name < rhs.name; }
    bool operator > (const edge& rhs) const { return name > rhs.name; }
};  /* end of edgeRep class */


/*
 * Type: Vertex
 * ------------
 * This type is the supplied type for a vertex in a graph.
 */
template <typename V, typename W>
struct vertex    // Array cell structure for graph
{
    typedef edgeRep<V, W> edge;     // for convenience
    explicit vertex(V n)            // vertex Constructor
    {
        name = n;                   // vertex name
        predecessor = n;            // used by finding shortest path
        currDist = INF;             // used by finding shortest path   //  ⚠️ 由0改为max dist
        visited = 0;                // visited flag for traversal
    }

    V name;                         // Vertex name
    int visited;                    // Used during traversal, Breadth-First or Depth-First
    V predecessor;                  // predecessor of the vertex for path-finding
    double currDist;                // distance of vertex for path-finding
    list<edge> edgeList;            // Pointer to edge list

    // Overload operators
    bool operator == (const vertex& v) const { return name == v.name; }
    bool operator != (const vertex& v) const { return name != v.name; }
    bool operator < (const vertex& rhs) const { return name < rhs.name; }
    bool operator > (const vertex& rhs) const { return name > rhs.name; }
};  /* end of vertex class */

#include "myGraphADT.t"

#endif //MYGRAPHADT_H
