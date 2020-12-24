/**********************************************************************
 * File name: myGraphADT.t
 * -----------------------
 * This file implements all templated functions of the Graph class.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/25/2020
 * Date Last Revised: 10/29/2020
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
Graph<V,W>::Graph() = default;


/*******************************************************************************************
 * Destructor: Graph
 * ------------------
 * Purpose: To avoid memory leak.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
Graph<V,W>::~Graph()
{
    // usually the STL vector will handle memory leak itself, but I'm adding it
    // just to ensure memory is freed when out of scope.
    G.clear();          // Removes all elements in vector
    G.shrink_to_fit();  // Frees the memory which is not used by the vector
}


/*******************************************************************************************
 * Function Name: clear
 * ------------------
 * Purpose: Removes all vertices in main graph vector.
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::clear()
{
    G.clear();  // Removes all vertices in graph vector.
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
*
* Output parameters: none.
* Return Value:
*          int type: -1 indicates v is vertex in graph.
*                    1 indicates no such vertex in graph.
 *******************************************************************************************/
template<typename V, typename W>
int Graph<V,W>::isVertex(V &v) const
{
    int i = 0;                          // index of v in main graph vector
    for (vertexT ver: G)                // for each vertex in main graph vector
    {
        if (ver.name == v) return i;    // return index if a vertex name matches v
        i++;
    }
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
    return -1;                              // indicate no such edge in graph
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
    if (isVertex(v) == -1)   // only add if v doesn't exist in graph
    {
        vertexT newV(v);        // construct a new vertex object with v
        G.push_back(newV);      // add it into main graph vector
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

        for (vertexT & ver: G)             // Second: delete all edges related with v         // ⚠️ 注意搞了很久， 一定要用reference才能更改原vector的元素。
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
        int v1Index = isVertex(v1);          // get v1 index
        G[v1Index].edgeList.push_back(newEdge); // add
        G[v1Index].edgeList.sort();             // sort in ascending order                       // ⚠️ 要加 algorithm吗，还有差点忘记sort每个vertex的edge list了，by 11/05/2020
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
    inputFile(inFile);            // prompt user for text graph file
    V starting, ending;              // starting vertex and ending vertex
    W weight;                        // weight between two vertices
    char endMark = char{};           // to detect '#' character

    // Setup the graph ADT from data in given graph file:
    while (inFile >> starting)          // for each line, first read starting vertex.
    {
        while (true)                    // then repeatedly load ending vertex and weight
        {
            // Case 1: If the starting vertex has no edge at all:
            inFile >> ws;               // eat up any leading white spaces
            if (inFile.peek() == '#')   // check if end mark exists
            {
                inFile.get(endMark); // discard the end mark
                break;                  // stop loading
            }

            inFile >> ending >> weight;  // Load ending vertex and its weight:
            AddUniEdge(starting, ending, weight); // add directed edge

            // Case 2: If reach the '#' symbol at line end:
            inFile >> ws;                // eat up any leading white spaces
            if (inFile.peek() == '#')    // check if end mark exists
            {
                inFile.get(endMark);  // discard the end mark
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
        int preIndex = isVertex(vertex->predecessor); // get predecessor's index
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
    vertexT* min = vec[0];  // minimum item in vec      // ⚠️ 为什么在删除后还能用？？因为vector的assignment是deep copy.
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
    int v1Pos = isVertex(v1);            // check v1 index
    if (v1Pos == -1) return -1;             // return -1 when no such vertex in graph
    int v2Pos = isVertex(v2);            // vector v2 index
    if (v2Pos == -1) return -2;             // return -2 when no such vertex in graph

    // Initialize current distance of all vertices
    for (vertexT & v: G)
        v.currDist = MAX_DIST;               // Distance from all vertices is infinity
    vertexT* vertex = &G[v1Pos];             // v1 vertex in graph vector
    vertex->currDist = 0;                    // Distance from v1 vertex is 0

    // Initialize toBeChecked:
    vector<vertexT*> toBeChecked;            // vector of pointers to all vertices
    for (int i = 0; i < G.size(); i++)
        toBeChecked.push_back( &G[i] );      // add all vertices

    // Dijkstra begins:
    while (!toBeChecked.empty())
    {
        vertex = minimumOf(toBeChecked);  // obtain and remove the vertex with minimum currDist

        for (edgeT & e: vertex->edgeList)                   // for each neighbor of vertex
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
    if (ver2->predecessor == ver2->name) return -3; // return -3 if no available path

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
*             All vertices' visited flag are set to unvisited(0).
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::resetVisitFlag()
{
    for (vertexT & ver : G)    // ⚠️ 注意：只有设为&(reference)才能改变vector里面的值，要不然每个ver都是vector的copy，不改变原值！
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
    vertexT* ver = &G[vPos];            // pointer to initial vertex
    Q.push(ver);                        // enqueue starting vertex

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
* Function Name: DFTraversal
*
* Purpose: Performs a recursive Depth First Traversal of the graph starting at
*          specified vertex (parameter) and also prints trace information.
*
* Input Parameters:
*            v: the vertex's name that DFT first starts.
* Output parameters:
*           All traversed vertices' visited flag are set to visited(1).
* Return Value: none.
 *******************************************************************************************/
template<typename V, typename W>
void Graph<V,W>::DFTraversal(V &v)
{
    // Check to see if v exists in graph
    int vPos = isVertex(v); // get index of v in graph vector
    if (vPos == -1)            // don't traverse when no such vertex in graph
    {
        cout << "Vertex: " << v << " is NOT in the graph";
        return;
    }

    resetVisitFlag();          // clear all visited flags
    recDFT(&G[vPos]);       // start DF traversal
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

#endif