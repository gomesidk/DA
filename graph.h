#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>


template <class T>
class Edge;

/************************* Vertex  **************************/

template <class T>
class Vertex {
public:
    Vertex(T in, bool parking);
    bool operator<(Vertex<T> & vertex) const; // required by MutablePriorityQueue

    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;
    bool hasParking() const;             //check if location has parking

    void setInfo(T info);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setParking(bool parking);       //needed because of parking

    int getLow() const;
    void setLow(int value);
    int getNum() const;
    void setNum(int value);

    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge<T> *path);
    Edge<T> * addEdge(Vertex<T> *dest, int walk_time, int drive_time);
    bool removeEdge(T in);
    void removeOutgoingEdges();

protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges
    bool parking; // indicates if the location has parking

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    int low = -1, num = -1; // used by SCC Tarjan
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming; // incoming edges

    int queueIndex = 0;        // required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge<T> *edge);
};

/********************** Edge  ****************************/

template <class T>
class Edge {
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, int walk_time, int drive_time);

    Vertex<T> * getDest() const;
    int getWalkTime() const;
    int getDriveTime() const;
    bool isSelected() const;
    Vertex<T> * getOrig() const;
    Edge<T> *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge<T> *reverse);
    void setFlow(double flow);
protected:
    Vertex<T> * dest; // destination vertex
    int walk_time; // walking time
    int drive_time; // driving time

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;

    double flow; // for flow-related problems
};



/********************** Graph  ****************************/

template <class T>
class Graph {
public:
    ~Graph();
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in, bool parking);
    bool removeVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, int walk_time, int drive_time);
    bool removeEdge(const T &source, const T &dest);
    bool addBidirectionalEdge(const T &sourc, const T &dest, int walk_time, int drive_time);

    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

protected:
    std::vector<Vertex<T> *> vertexSet;

    double ** distMatrix = nullptr;
    int **pathMatrix = nullptr;

    int findVertexIdx(const T &in) const;
};

inline void deleteMatrix(int **m, int n);
inline void deleteMatrix(double **m, int n);

/********************** Vertex Declarations  ****************************/

template <class T>
Vertex<T>::Vertex(T in, bool parking): info(in), parking(parking) {}


template <class T>
T Vertex<T>::getInfo() const {
    return info;  // Simply return the info of the vertex
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
bool Vertex<T>::isVisited() const{
    return visited;
}

template <class T>
bool Vertex<T>::isProcessing() const{
    return processing;
}

template <class T>
unsigned int Vertex<T>::getIndegree() const{
    return indegree;
}

template <class T>
double Vertex<T>::getDist() const{
    return dist;
}

template <class T>
Edge<T> *Vertex<T>::getPath() const{
    return path;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return incoming;
}

template <class T>
bool Vertex<T>::hasParking() const{
    return parking;
}

template <class T>
int Vertex<T>::getLow() const{
    return low;
}

template <class T>
int Vertex<T>::getNum() const{
    return num;
}


template <class T>
Edge<T>* Vertex<T>::addEdge(Vertex<T> *dest, int walk_time, int drive_time) {
    // Create a new edge from the current vertex (this) to the destination vertex (dest)
    Edge<T>* edge = new Edge<T>(this, dest, walk_time, drive_time);

    // Add this edge to the adjacency list of the current vertex (outgoing edges)
    adj.push_back(edge);

    // Also add this edge to the incoming edges list of the destination vertex (for reverse reference)
    dest->incoming.push_back(edge);

    // Return the created edge
    return edge;
}


/********************** Edge Declarations ****************************/

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, int walk_time, int drive_time)
    : orig(orig), dest(dest), walk_time(walk_time), drive_time(drive_time) {}



template <class T>
Vertex <T> *Edge<T>::getDest() const {
    return dest;
}

template <class T>
int Edge<T>::getWalkTime() const {
    return walk_time;
}

template <class T>
int Edge<T>::getDriveTime() const {
    return drive_time;
}

template <class T>
bool Edge<T>::isSelected() const {
    return selected;
}

template <class T>
Vertex<T> *Edge<T>::getOrig() const {
    return orig;
}


template <class T>
Vertex <T> *Edge<T>::getDest() const {
    return dest;
}

template <class T>
int Edge<T>::getWalkTime() const {
    return walk_time;
}

template <class T>
int Edge<T>::getDriveTime() const {
    return drive_time;
}

template <class T>
bool Edge<T>::isSelected() const {
    return selected;
}

template <class T>
Edge<T> *Edge<T>::getReverse() const {
    return reverse;
}


template <class T>
Vertex <T> *Edge<T>::getDest() const {
    return dest;
}

template <class T>
int Edge<T>::getWalkTime() const {
    return walk_time;
}

template <class T>
int Edge<T>::getDriveTime() const {
    return drive_time;
}

template <class T>
bool Edge<T>::isSelected() const {
    return selected;
}

template <class T>
double Edge<T>::getFlow() const {
    return flow;
}


/********************** Graph Declarations ****************************/

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}


template <class T>
bool Graph<T>::addVertex(const T &in, bool parking) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in, parking));
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, int walk_time, int drive_time) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, walk_time, drive_time);
    return true;
}



template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, int walk_time, int drive_time) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, walk_time, drive_time);
    auto e2 = v2->addEdge(v1, walk_time, drive_time);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}


template <class T>
Graph<T>::~Graph() {
    for (auto v : vertexSet)
        delete v;
}


#endif /* DA_TP_CLASSES_GRAPH */
//
// Created by joaog on 22/03/2025.
//
