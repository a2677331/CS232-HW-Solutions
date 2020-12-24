/**********************************************************************
 * File name: myGraphADT.t
 * -----------------------
 * This file implements all templated functions of the Graph class.
 *
 * Programmer: Jian Zhong
 * Date Written: 11/15/2020
 * Date Last Revised: 11/20/2020
 **********************************************************************/

#ifndef MYGRAPHADT_T
#define MYGRAPHADT_T

/*******************************************************************************************
 * Destructor: Graph
 * ------------------
 * Purpose: To Initialize an empty graph object.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
Graph<V,W>::Graph()
{
    minTree = nullptr;
}


/*******************************************************************************************
 * Destructor: Graph
 * ------------------
 * Purpose: To avoid memory leak.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>                         //⚠️！！！！！！！！！！！！！！！！！！！！！！！！！！
Graph<V,W>::~Graph()
{
    if (minTree != nullptr) delete minTree;
    G.clear();          // Removes all vertices in graph vector.
    G.shrink_to_fit();  // Frees the memory which is not used by the vector
}



/*******************************************************************************************
 * Function Name: vertexCount
 * ------------------
 * Purpose: get the total number of vertices in the graph.
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value:
 *          int: non-negative integer indicates the size, 0 is empty.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::vertexCount() const
{
    return G.size();
}


/*******************************************************************************************
* Function Name: inputFile
*
* Purpose: To open a file from specified file path,
*          if fails to open, user can specify another file path.
*
* Input Parameters:
*          inFile: input file stream.
*          filePath: file path name.
*
* Output parameters:
*          inFile: now points to opened file.
*
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::inputFile(ifstream& inFile)
{
    string filePath;                // file path
    cout << "Please enter file path: ";
    getline(cin, filePath);
    while (true)                    // user have unlimited chances to enter.
    {
        inFile.open(filePath);
        if (!inFile.fail()) break;  // if open fail, user can try again.
        cout << "Can't locate the file, please re-enter file path: ";
        getline(cin, filePath);
    }
}


/*******************************************************************************************
* Function Name: isVertex
*
* Purpose: To test whether v is a vertex in the graph.
*
* Input Parameters:
*          v: vertex name
 *         G: graph object
*
* Output parameters: none.
* Return Value:
*          int type: 1 indicates v is vertex in graph.
*                    -1 indicates no such vertex in graph.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::isVertex(V &v) const
{
    for (int i = 0; i < G.size(); i++)  // for each vertex in given graph vector
        if (G[i].name == v) return i;   // if name matches, return index of it.
    return -1;                          // indicate no such vertex in graph
}


/*******************************************************************************************
* Function Name: isUniEdge
*
* Purpose: To tests whether a directed edge <v1,v2> is in graph.
*
* Input Parameters:
*          v1: starting vertex name
*          v2: ending vertex name
*
* Output parameters: none.
* Return Value:
*          int type: non-negative integer: the index of vector has that edge,
*                    -1 indicates no such edge in graph.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::isUniEdge(V &v1, V &v2) const
{
    int i = 0;                              // index of v1 in main graph vector
    for (vertexT v: G)                      // for each vertex in main graph vector
    {
        if (v.name == v1)                   // look for v1 in graph
        {
            for (edgeT e: v.edgeList)       // for each edge inside that vertex
                if (e.name == v2) return i; // index of vector has that edge
        }
        i++;
    }
    return -1;                              // indicate no such edge in graph
}


/*******************************************************************************************
* Function Name: isBiDirEdge
*
* Purpose: Tests whether an undirected edge (v1,v2) is in graph.
*
* Input Parameters:
*          v1: starting/ending vertex name
*          v2: starting/ending vertex name
*
* Output parameters: none.
* Return Value:
*          int type: non-negative integer: the index of vector has that undirected edge,
*                    -1 indicates no such undirected edge in graph.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::isBiDirEdge(V &v1, V &v2) const
{
    if (isUniEdge(v1, v2) != -1)     // check if <v1,v2> edge exists
        return isUniEdge(v2, v1);    // check if <v2,v1> edge exists
    return -1;                       // indicate no such edge in graph
}


/*******************************************************************************************
* Function Name: AddVertex
*
* Purpose: Adds vertex with name v to the graph if v is not already in
*          graph, and returns the index where the vertex is stored.
*
* Input Parameters:
*          v: vertex name to be added
*
* Output parameters: none.
* Return Value:
*          int type: non-negative integer: the index where the vertex is stored,
*                    -1 indicates v was not added.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::AddVertex(V& v)
{
    if (isVertex(v) == -1)      // only add if v doesn't exist in graph
    {
        vertexT newV(v);        // construct a new vertex object with v
        G.push_back(newV);      // add it into main graph vector
//        std::sort(G.begin(), G.end());  // ⚠️ 添加了sort vertices。
        return G.size() - 1;    // the index where the vertex is stored
    }

    return -1;                  // indicate v was not added
}


/*******************************************************************************************
* Function Name: DeleteVertex
*
* Purpose: Deletes vertex with name v from the graph if v is in the graph.
*          If there are any edges incident on the vertex, these edges are deleted also.
*
* Input Parameters:
*          v: vertex name to be added
*
* Output parameters: none.
* Return Value:
*          non-negative integer: the index where the vertex is stored,
*          -1 indicates no delete action was perform.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::DeleteVertex(V &v)
{
    int posToDel = isVertex(v);         // get v's position to delete
    int isDeleted = -1;                    // delete indicator

    // only delete if v is in the graph
    if (posToDel != -1)
    {
        isDeleted = 1;                     // update delete indicator
        G.erase(G.begin() + posToDel);     // First: delete v

        for (vertexT & ver: G)             // Second: delete all edges related with v
            for (edgeT & e: ver.edgeList)
                if (e.name == v)           // if edge name matches v
                {
                    ver.edgeList.remove(e);// delete the edge
                    break;                 // one v edge at most at every vertex
                }
    }
    // return delete indicator
    return isDeleted;
}


/*******************************************************************************************
* Function Name: DeleteUniEdge
*
* Purpose: Deletes the directed edge <v1,v2> (any weight) from the graph if it's in graph.
*          The vertices are not deleted from the graph, only the edge.
*
* Input Parameters:
*          v1: starting vertex name
*          v2: ending vertex name
*
* Output parameters: none.
* Return Value:
*          int: 1 successfully deleted,
*               -1 failed to delete the directional edge.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::DeleteUniEdge(V &v1, V &v2)
{
    int posToDel = isUniEdge(v1, v2);  // index of vertex holds v1->v2 edge

    if (posToDel != -1)  // delete if the edge is in graph
        for (edgeT & e: G[posToDel].edgeList)
            if (e.name == v2)
            {            // remove the edge with v2 name.
                G[posToDel].edgeList.remove(e);
                return 1;
            }

    return -1;           // else indicate no edge was deleted
}


/*******************************************************************************************
* Function Name: AddUniEdge
*
* Purpose: Adds the directed edge <v1,v2,wt> to the graph; adds the vertices
*          to the graph if the vertices are not already part of the graph.
*
* Input Parameters:
*          v1: starting vertex name
*          v2: ending vertex name
*          wt: weight of the directed edge <v1,v2,wt>
*
* Output parameters: none.
* Return Value:
*          int: 1 successfully added the edge,
*               -1 indicate no edge was added.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::AddUniEdge(V &v1, V &v2, W &wt)
{
    // Only add if the edge is not in graph:
    if (isUniEdge(v1, v2) == -1)
    {
        // Add v1 and v2 vertices into graph.
        AddVertex(v1);
        AddVertex(v2);

        // Add new edge <v1,v2,wt> into graph.
        edgeT newEdge(v2, wt);
        int v1Index = isVertex(v1);             // get v1 index
        G[v1Index].edgeList.push_back(newEdge);    // add
        G[v1Index].edgeList.sort();                // sort in ascending order
        return 1;     // indicate the edge was added
    }

    // Else the v1->v2 edge exists:
    return -1;
}


/*******************************************************************************************
* Function Name: AddBiDirEdge
*
* Purpose: Adds the bi-directional edge (v1,v2,wt) to the graph; Adds the
*          vertices to the graph if the vertices are not already part of the graph.
*
* Input Parameters:
*          v1: starting vertex name
*          v2: ending vertex name
*          wt: weight of the directed edge <v1,v2,wt>
*
* Output parameters: none.
*
* Return Value:
*          int:  1 successfully added (v1,v2).
*               -1 <v1,v2> already exists, <v2,v1> added.
 *              -2 <v1,v2> added, <v2,v1> already exists.
 *              -3 <v1,v2> and <v2,v1> already exists.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::AddBiDirEdge(V &v1, V &v2, W &wt)
{
    // Add edges: v1->v2 and v2->v1:
    int addE1 = AddUniEdge(v1, v2, wt);
    int addE2 = AddUniEdge(v2, v1, wt);

    // Check if edge was added successfully:
    if (addE1 == 1 && addE2 == 1)          //  (v1,v2) successfully added.
        return 1;
    else if (addE1 == -1 && addE2 == 1)    //  <v1,v2> already exists, <v2,v1> added.
        return -1;
    else if (addE1 == 1 && addE2 == -1)    //  <v1,v2> added, <v2,v1> already exists.
        return -2;
    else                                   //  (v1,v2) already exists.
        return -3;
}


/*******************************************************************************************
* Function Name: DeleteBiDirEdge
*
* Purpose: Deletes the bi-directional edge (v1,v2) (any weight)
*          from the graph if it is in the graph.
*          The vertices are not deleted from the graph, only the edge.
*
* Input Parameters:
*          v1: starting vertex name
*          v2: ending vertex name
*
* Output parameters: none.
*
* Return Value:
*          int:  1 successfully deleted (v1,v2).
*               -1 <v1,v2> doesn't exist, <v2,v1> deleted.
 *              -2 <v1,v2> deleted, <v2,v1> already doesn't exist.
 *              -3 (v1,v2) do not exist.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::DeleteBiDirEdge(V &v1, V &v2)
{
    // Delete edges: v1->v2 and v2->v1
    int delE1 = DeleteUniEdge(v1, v2);
    int delE2 = DeleteUniEdge(v2, v1);

    // Check if edges were deleted successfully:
    if (delE1 == 1 && delE2 == 1)          //  (v1,v2) successfully deleted.
        return 1;
    else if (delE1 == -1 && delE2 == 1)    //  <v1,v2> doesn't exist, <v2,v1> deleted.
        return -1;
    else if (delE1 == 1 && delE2 == -1)    //  <v1,v2> deleted, <v2,v1> doesn't exist.
        return -2;
    else                                   //  (v1,v2) does not exists.
        return -3;
}


/*******************************************************************************************
* Function Name: SimplePrintGraph
*
* Purpose: Prints the list of vertices in the graph, and for each vertex
*          prints the list of edges in proper parenthesized notation,
*          namely (v1,v2,wt) or <v1,v2,wt>.
*
* Input Parameters: none.
* Output parameters: none.
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::SimplePrintGraph() const
{
    if (G.empty())              // prompt user if empty graph.
    {
        cout << "The graph is empty.";
        return;
    }

    for (vertexT v: G)         // print list of vertices in adjacent list form.
    {
        cout << "\nAdjacency list of vertex \"" << v.name << "\": ";
        for (edgeT e: v.edgeList)
            cout << " -> <"<< v.name << "," << e.name << "," << e.weight << ">";
    }
    cout << "\nThe graph contains " << vertexCount() << " vertices.";
}


/*******************************************************************************************
* Function Name: GetGraph
*
* Purpose: Retrieves a graph from a special format file and
*          sets up the adjacency list for the graph.
*
* Input Parameters: none.
* Output parameters: none.
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::GetGraph()
{
    ifstream inFile;                 // input file stream
    inputFile(inFile);               // prompt user for text graph file
    V starting, ending;              // starting vertex and ending vertex
    W weight;                        // weight between two vertices
    char endMark = char{};           // to detect '#' character

    // Setup the graph ADT from data in given graph file:
    while (inFile >> starting)           // for each line, first read starting vertex.
    {
        while (true)                     // then repeatedly load ending vertex and weight
        {
            // Case 1: If the starting vertex has no edge at all:
            inFile >> ws;                // eat up any leading white spaces
            if (inFile.peek() == '#')    // check if end mark exists
            {
                inFile.get(endMark);     // discard the end mark
                break;                   // stop loading
            }

            inFile >> ending >> weight;  // Load ending vertex and its weight:
            AddUniEdge(starting, ending, weight); // add directed edge

            // Case 2: If reach the '#' symbol at line end:
            inFile >> ws;                // eat up any leading white spaces
            if (inFile.peek() == '#')    // check if end mark exists
            {
                inFile.get(endMark);     // discard the end mark
                break;                   // stop loading
            }
        }
    }
}


/*******************************************************************************************
* Function Name: printPath
*
* Purpose: Print path from a given vertex in the graph.
*          Vertex's predecessor is evaluated until no predecessor
*          is found(one's predecessor is itself).
*
* Input Parameters:
*          vertexT*: pointer to vector type of the graph.
*
* Output parameters: none.
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::printPath(vertexT* vertex)
{
    // Setup path stack
    stack<V> path;
    while (true)
    {
        path.push(vertex->name);                         // add name into path
        int preIndex = isVertex(vertex->predecessor);    // get predecessor's index
        if (G[preIndex].name == vertex->name) break;     // exit loop when no predecessor
        vertex = &G[preIndex];                           // point to predecessor's vertex
    }

    // Print path from path stack
    cout << "Shortest path: ";
    while (!path.empty())
    {
        cout << path.top();
        if (path.size() != 1) cout << " -> ";
        path.pop();
    }
}


/*******************************************************************************************
* Function Name: minimumOf
*
* Purpose: Get the vertex with minimum current
*          distance and remove it from vec collection.
*
* Input Parameters:
*          vector<vertexT*>: a vector of pointers to vertex type
*
* Output parameters:
*          vec: a modified vector with one less element than before.
* Return Value:
*          vertex<V,W>*: pointer to vertex with minimum current distance.
 *******************************************************************************************/
template<typename V, typename W>
vertex<V,W>* Graph<V,W>::minimumOf(vector<vertexT*>& vec)
{
    vertexT* min = vec[0];  // minimum item in vec
    int indexToDel = 0;     // index to delete

    // Find the minimum item in vec
    for (int i = 0; i < vec.size(); i++)
        if (min->currDist > vec[i]->currDist)
        {
            min = vec[i];   // update minimum
            indexToDel = i; // update index of minimum
        }

    vec.erase(vec.begin() + indexToDel); // deleted the minimum item in vec
    return min;                          // return the deleted item
}


/*******************************************************************************************
* Function Name: ShortestDistance
*
* Purpose: Returns the shortest distance from vertex 1 to vertex 2 using
*          Dijkstra algorithm and print user the path too.
*
* Input Parameters:
*          v1: starting vertex
*          v2: ending vertex
*
* Output parameters: none.
* Return Value:
*          non-negative double: the shortest total distance from v1 to v2.
*          -1: when v1 does not exists.
 *         -2: when v2 does not exists.
 *         -3: there is no path between v1 and v2.
 *******************************************************************************************/
template<typename V, typename W>
double Graph<V,W>::ShortestDistance(V &v1, V &v2)
{
    resetAllFlags();                     //  Bug fixed: causing infinite loop when execute more than once in one run.
    int v1Pos = isVertex(v1);         // check v1 index
    if (v1Pos == -1) return -1;          // return -1 when no such vertex in graph
    int v2Pos = isVertex(v2);         // vector v2 index
    if (v2Pos == -1) return -2;          // return -2 when no such vertex in graph

    // Initialize current distance of all vertices
    for (vertexT & v: G)
        v.currDist = INF;                // Distance from all vertices is infinity
    vertexT* vertex = &G[v1Pos];         // v1 vertex in graph vector
    vertex->currDist = 0;                // Distance from v1 vertex is 0

    // Initialize toBeChecked:
    vector<vertexT*> toBeChecked;        // vector of pointers to all vertices
    for (int i = 0; i < (int)G.size(); i++)
        toBeChecked.push_back( &G[i] );  // add all vertices

    // Dijkstra begins:
    while (!toBeChecked.empty())
    {
        vertex = minimumOf(toBeChecked);     // obtain and remove the vertex with minimum currDist

        for (edgeT & e: vertex->edgeList)                  // for each neighbor of vertex
        {
            vertexT* neighbor = &G[ isVertex(e.name) ]; // neighbor vertex in graph vector
            double newDist = vertex->currDist + e.weight;  // possible newDist candidate
            if (newDist < neighbor->currDist)              // if newDist is shorter
            {
                neighbor->currDist = newDist;              // update neighbor's currDist
                neighbor->predecessor = vertex->name;      // update neighbor's predecessor
            }
        }
    }

    // Print path and return total distance:
    vertexT* ver2 = &G[v2Pos]; // v2 vertex
    if (ver2->predecessor == ver2->name) return -3; // return -3 if path does not exist.

    // else, found a path between v1 and v2!
    printPath(ver2);           // print path
    return ver2->currDist;     // output total distance
}


/*******************************************************************************************
* Function Name: resetVisitFlag
*
* Purpose: Reset all vertices' visited flag back to unvisited.
*
* Input Parameters: none.
* Output parameters:
*             All vertices' visited flags are set to unvisited(0).
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::resetVisitFlag()
{
    for (vertexT & ver : G)
        if (ver.visited == 1)
            ver.visited = 0;
}


/*******************************************************************************************
* Function Name: BFTraversal
*
* Purpose: Performs Breadth First Traversal with trace information printed.
*
* Input Parameters:
*            v: the vertex's name that BFT first starts.
* Output parameters:
*           All traversed vertices' visited flag are set to visited(1).
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::BFTraversal(V &v)
{
    // Check to see if v exists in graph
    int vPos = isVertex(v);          // vector index
    if (vPos == -1)                     // prompt user when no such vertex in graph
    {
        cout << "Vertex: " << v << " is NOT in the graph";
        return;
    }
    // Prepare for BFT:
    resetVisitFlag();                    // reset visit flags
    queue<vertexT* > Q;                  // queue of vertex pointers
    vertexT* ver = &G[vPos];             // pointer to initial vertex
    Q.push(ver);                         // enqueue starting vertex

    // Begin BFT:
    while (!Q.empty())
    {
        // Select a vertex from queue:
        ver = Q.front();                 // select a vertex pointer
        Q.pop();                         // dequeue it from queue

        // Visit it if it's not visited yet:
        if (ver->visited == 0)
        {
            cout << " -> " << ver->name; // visit v
            ver->visited = 1;            // set visited flag
        }

        // Enqueue all neighbors of current vertex:
        for (edgeT e: ver->edgeList)
        {
            int nPos = isVertex(e.name); // neighbor index in graph vector
            if (G[nPos].visited == 0)       // if it's the unvisited neighbor
                Q.push(&G[nPos]);           // enqueue the neighbor
        }
    }
}


/*******************************************************************************************
* Function Name: DepthFirstTraversal
*
* Purpose: A recursive Depth First Traversal of the graph starting at
*          specified vertex (parameter) and also prints trace information.
*
* Input Parameters:
*            v: the vertex's name that DFT first starts.
* Output parameters:
*           All traversed vertices' visited flag are set to visited(1).
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::DepthFirstTraversal(V &v)
{
    // Check to see if v exists in graph
    int vPos = isVertex(v);    // get index of v in graph vector
    if (vPos == -1)            // don't traverse when no such vertex in graph
    {
        cout << "Vertex: " << v << " is NOT in the graph";
        return;
    }

    resetVisitFlag();             // clear all visited flags
    recDFT(&G[vPos]);          // start DF traversal
}


/*******************************************************************************************
* Function Name: recDFT
*
* Purpose: Recursive utility function that helps perform the Depth First Traversal.
*
* Input Parameters:
*            v: the vertex's name that DFT first starts.
* Output parameters:
*           All traversed vertices' visited flag are set to visited(1).
* Return Value: none.
 *******************************************************************************************/
template <typename V, typename W>
void Graph<V,W>::recDFT(vertexT* v)
{
    cout << " -> " << v->name;           // visit v
    v->visited = 1;                      // set visited flag

    for (edgeT e: v->edgeList)           // for all neighbors of current vertex
    {
        int vPos = isVertex(e.name);  // neighbor's index of ver in graph vector
        if (G[vPos].visited == 0)        // if neighbor is unvisited
            recDFT(&G[vPos]);         // recur to visit next neighbor
    }
}


/*******************************************************************************************
* Function Name: resetAllFlags()
*
* Purpose: Reset all flags of each vertex in graph back to default,
*           used in ShortestDistance( ) and FordShortestPaths( ).
*
* Input Parameters: none.
* Output parameters:
*          All vertices' visited flags are set to unvisited(0).
* Return Value: none.
 *******************************************************************************************/
template <typename V, typename W>
void Graph<V,W>::resetAllFlags()
{
    for (vertexT& v : G)
    {
        v.visited = 0;
        v.currDist = INF;
        v.predecessor = v.name;
    }
}


/*******************************************************************************************
* Function Name: DFTraversal()
*
* Purpose: An iterative version of DFS traversal from a given vertex.
*
* Input Parameters:
*          v: the vertex's name that DFT first starts from.
* Output parameters: none.
* Return Value: none.
 *******************************************************************************************/
template <typename V, typename W>
void Graph<V,W>::DFTraversal(V& v)
{
    // Setup and verify pre-conditions:
    resetVisitFlag();           // Reset visited flag
    int vPos = isVertex(v);
    if (vPos == -1)             // don't traverse when no such vertex in graph
    {
        cout << "Vertex: " << v << " is NOT in the graph";
        return;
    }

    // Traversal begins:
    stack<vertexT*> Stack;      // stack for DFS
    vertexT* vertex = &G[vPos]; // get source vertex
    Stack.push(vertex);         // push it onto stack
    while (!Stack.empty())
    {
        vertex = Stack.top();
        Stack.pop();

        if (vertex->visited == 0)                               // ⚠️ 可能有多个node指向同一个邻居，所以要加这个排除掉重复出现的neighbor，只要visit一次就可以了！
        {
            cout << " -> " << vertex->name;   // print
            vertex->visited = 1;              // set visited  // ⚠️ 记得要取出以后才可以设置为visited，要不然第一个就不会输出了。
        }

        for (edgeT edge : vertex->edgeList)
        {
            vertexT* neighbor = &G[ isVertex(edge.name) ];
            if (neighbor->visited == 0)
                Stack.push(neighbor);         // push unvisited neighbor
        }
    }
}


/*******************************************************************************************
* Function Name: mst()
*
* Purpose: Determine the minimum spanning tree using Prim's algorithm.
*          1: this method also prints trace information when finding MST.
*          2: NOTE: Prim's algorithm can be used only in undirected graph, used in
*                   directed graph may lead to incorrect results.
*          3: after MST is found, weight and adjacency list of the MST would be printed.
*
* Input Parameters: none.
* Output parameters: none.
* Return Value: none.
 *******************************************************************************************/
template <typename V, typename W>
void Graph<V,W>::mst()
{
    // Setup MST:
    if (minTree != nullptr) delete minTree;    // avoid memory leak
    minTree = new Graph<V,W>;                  // allocate new space for the MST
    int g_size = G.size();                     // get the number of vertices in graph
    int count = 0;                             // count MST iteration
    vector<bool> component(g_size, false);  // setup mst vertices, default is false
    vector<W> distance(g_size, INF);           // setup distances, default is infinity
    vector<V> neighbor(g_size, G[0].name);     // setup neighbors, the 1st vertex is always the source

    // In distance[]: initialize distances from source to neighbors:
    for (edgeT e: G[0].edgeList)
    {
        int index = isVertex(e.name);       // get the neighbor index
        if (index != -1)                       // if neighbor exists
            distance[index] = e.weight;        // update distance from vertex to neighbors
    }
    component[0] = true;                       // put source in mst
    cout << "\n-------------------- MST Trace Starting From \"" << G[0].name << "\" --------------------\n";
    printMst(component, distance, neighbor, count);  // print trace info

    // Now begin Prim's algorithm:
    for (int i = 1; i < g_size; i++)
    {
        int v;                     // add a vertex to mst on each pass
        W min = INF;               // largest value of type
        for (int w = 0; w < g_size; w++)
            if (!component[w])     // only vertices not in mst
                if (distance[w] < min)
                {
                    v = w;         // assign vertex at pos of w to v.
                    min = distance[w];
                }

        if (min < INF)             // edge was found from vertex in mst to vertex or not
        {
            component[v] = true;   // put min dist neighbor in mst
            cout << endl << endl;
            printMst(component, distance, neighbor, count);                // print trace info
            minTree->AddBiDirEdge( G[v].name, neighbor[v], distance[v] );  // add edge v->u
            cout << "\n\n    Add Edge (" << G[v].name << "," << neighbor[v] << "," << distance[v] << ")";

            for (int w = 0; w < g_size; w++)
                if (!component[w])                    // only vertices not in mst
                {
                    W actualDist = distOf(v, w, G);   // get actual distance from v to w in graph
                    if (actualDist < distance[w])     // if actual distance < the distance so far in mst
                    {
                        distance[w] = actualDist;     // use actual distance
                        neighbor[w] = G[v].name;      // v is neighbor of w
                        cout << endl << endl;
                        printMst(component, distance, neighbor, count);  // print trace info
                    }
                }
        } // end if (min < INF)
        else
            break;
    } // end for i

    // Print weight and who connects to whom:
    cout << "\n\n    Total Weight of MST: " << sumOf(distance);
    cout << "\n\n----------------------- MST Connections -----------------------";
    minTree->SimplePrintGraph();
    cout << endl;
}

/*******************************************************************************************
* Function Name: FordShortestPaths()
*
* Purpose: Determines the shortest paths to all other vertices from the specified vertex,
*           1: the function prints trace information: the DeQ after each iteration.
*           2: the function also prints the minimum distance along with nodes in the path.
*           3: this method can be applied to graphs with negative weights with no negative cycle.
*
* Input Parameters:
*           v: the vertex's name.
* Output parameters: none.
* Return Value: none.
 *******************************************************************************************/
template <typename V, typename W>
void Graph<V,W>::FordShortestPaths(V &v)                            // ⚠️ 注意了：在一般找最短路径的算法里，只要有negative cycle在图里，那就一定找不到，因为可以无限绕这个cycle来获得负无穷weight。
{
    // CASE 1: don't find if no such vertex exists:
    int vIndex = isVertex(v);   // get v index in main graph vector
    if (vIndex == -1)
    {
        cout << "Vertex: " << v << " is NOT in the graph\n";
        return;                    // DONE if no such vertex exists
    }

    // CASE 2: find paths by Ford's algorithm:
    resetAllFlags();               // first reset all flags                // ⚠️ 想了很久，进行影响到vertex里的flag的操作时，每次要记得reset，要不第二次工作时就会乱。
    for (vertexT& vertex: G)       // set all dists to infinity
        vertex.currDist = INF;
    vertexT* currVer = &G[vIndex]; // obtain starting vertex from index
    currVer->currDist = 0;         // starting vertex to itself is zero
    deque<vertexT*> DeQ;           // collection stores vertices to be checked
    DeQ.push_back(currVer);        // add starting vertex
    cout  << "Adding: " << currVer->name << "\n";        // Print trace info
    printDeQ(DeQ);

    // Begin Ford Algorithm:
    while (!DeQ.empty())
    {
        currVer = DeQ.front(); // get a vertex from deque
        DeQ.pop_front();       // remove it from deque
        cout << "\nRemoving: " << currVer->name << "\n"; // Print trace info
        printDeQ(DeQ);

        // Examine each neighbor of currVer:
        for (edgeT& edge : currVer->edgeList)
        {
            vertexT* neighbor = &G[ isVertex(edge.name) ];          // get a neighbor of v
            if (neighbor->currDist > currVer->currDist + edge.weight)  // if its dist is longer
            {
                neighbor->currDist = currVer->currDist + edge.weight;  // update currDist
                neighbor->predecessor = currVer->name;                 // update predecessor

                // Add neighbor if isn't in DeQ
                if ( find(DeQ.begin(), DeQ.end(), neighbor) == DeQ.end() )
                {
                    DeQ.push_back(neighbor);
                    cout << "\nAdding: " << neighbor->name << "\n";
                    printDeQ(DeQ);            // print DeQ info
                }
            }
        }  // end for loop
    } // end while loop

    // Print ford shortest path and minimum distance:
    for (int i = 0; i < G.size(); i++)
    {
        cout  << "Minimum distance from " << v << " to "
              << G[i].name <<  ":  " << G[i].currDist << endl;
        printPath(&G[i]);
        cout << endl << endl;
    }
} // end


/*******************************************************************************************
* Function Name: printDeQ()
*
* Purpose: To print DeQ trace information, used in FordShortestPaths( ).
*
* Input Parameters:
*           DeQ: STL deque collection that stores vertices.
* Output parameters: none.
* Return Value: none.
 *******************************************************************************************/
template <typename V, typename W>
void Graph<V,W>::printDeQ(const deque<vertexT*>& DeQ) const
{
    cout << "       DeQ: ";
    for (vertexT* item : DeQ)
        cout << item->name << "  ";
    cout << endl;
}


/*******************************************************************************************
* Function Name: distOf()
*
* Purpose: To get total distance from v to its neighbor w in mst( ).
*
* Input Parameters:
*           g: graph main vector
*           v: integer representing the index of vertex in graph.
*           w: integer representing the index of vertex in graph.
* Output parameters: none.
* Return Value:
*           W: edge's weight type.
 *******************************************************************************************/
template <typename V, typename W>
W Graph<V,W>::distOf(const int& v, const int& w, const vector<vertexT>& g)
{
    W actualDist;
    for (edgeT e : g[v].edgeList)
        if (e.name == g[w].name)
            return actualDist = e.weight;
    return INF;  // return infinity if no neighbor from v to w.
}


/*******************************************************************************************
* Function Name: sumOf()
*
* Purpose: To get total distance from v to its neighbor w in mst( ).
*
* Input Parameters:
*           dist: a vector of edge weight/distance.
* Output parameters: none.
* Return Value:
*           W: sum of weights in the dist vector.
 *******************************************************************************************/
template <typename V, typename W>
W Graph<V,W>::sumOf(const vector<W>& dist)
{
    W sum = 0;
    for (int i = 0; i < dist.size(); i++)
        if (dist[i] != INF)
            sum += dist[i];
    return sum;
}


/*******************************************************************************************
* Function Name: printMst()
*
* Purpose: To print trace info for mst( ).
*
* Input Parameters:
*           comp: a vector of boolean value indicating if a vertex is in mst.
*           dist: a vector of edge weight/distance.
*           neigh: a vector of neighbors and adjacent vertices.
*           count: count iterations info.
* Output parameters: none.
* Return Value:
 *******************************************************************************************/
template <typename V, typename W>
void Graph<V,W>::printMst(const vector<bool>& comp, const vector<W>& dist,
                          const vector<V>& neigh, int& count)
{
    int width = 8;  // width between cols
    count++;        // count trace number

    // print column label in the first row:
    cout << "MST Iteration trace " << count << ":  (9999 means Infinity)";
    cout << left << setw(width) << "\n         ";
    for (vertexT v : G)
        cout << right << setw(width) << v.name << "  ";

    // then print 3 rows of arrays:
    cout << left << setw(width) << "\nComp:    ";
    for (bool item : comp)
        cout << right << setw(width) << item << "  ";
    cout << left << setw(width) << "\nDist:    ";
    for (W item : dist)
        cout << right << setw(width) << item << "  ";
    cout << left << setw(width) << "\nNeighbor:";
    for (V item : neigh)
        cout << right << setw(width) << item << "  ";
}


#endif