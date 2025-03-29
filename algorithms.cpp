#include "graph.h"
#include "algorithms.h"
#include "MutablePriorityQueue.h"
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

std::vector<std::string> dijkstra(Graph<std::string>* g, const std::string& origin, const std::string& destination) {
    auto vertices = g->getVertexSet();
    std::unordered_map<std::string, std::string> pred;
    std::unordered_set<std::string> S; // Set of nodes whose shortest path is known

    // Initialize distances, predecessors, and add all vertices to the priority queue
    for (auto v : vertices) {
        v->setDist(std::numeric_limits<double>::infinity());  // distances as infinity
        v->setVisited(false); // Mark as unvisited
        pred[v->getInfo()] = ""; // Initialize all predecessors as empty string
    }



    g->findVertex(origin)->setDist(0); // Distance to the origin is 0
    pred[origin] = ""; // The origin has no predecessor



    // Mutable priority queue
    MutablePriorityQueue<Vertex<std::string>> pq;
    for (auto v : vertices) {
        pq.insert(v); // Add all vertices to the priority queue
    }

    // Start Dijkstra's algorithm
    while (!pq.empty()) {
        Vertex<std::string>* u = pq.extractMin(); // Extract vertex with the smallest distance

        // Add to the set of nodes whose shortest path is known
        S.insert(u->getInfo());


        // Relaxation of edges
        for (auto e : u->getAdj()) {
            std::string v = e->getDest()->getInfo();
            int driveTime = e->getDriveTime();

            if (driveTime < 0) continue; // Ignore roads that are not passable by car

            double alt = u->getDist() + driveTime;
            if (alt < e->getDest()->getDist()) {
                // Update distance and predecessor
                e->getDest()->setDist(alt);
                pred[v] = u->getInfo();


                // Update the priority queue
                pq.decreaseKey(e->getDest());
            }
        }
    }

    // Reconstruct the path
    std::vector<std::string> path;
    std::string current = destination;

    // If the distance to the destination is still infinity, return an empty path
    if (g->findVertex(current)->getDist() == std::numeric_limits<double>::infinity()) {
        cout << "No path found!" << endl;
        return {}; // No path found
    }

    // Rebuild the path from the destination to the origin
    while (current != origin) {
        path.push_back(current);
        current = pred[current];
    }
    path.push_back(origin); // Add the origin to the path
    std::reverse(path.begin(), path.end()); // Reverse to get the path from origin to destination

    // Debugging: Print the final path
    cout << "Shortest path: ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << endl;

    return path;
}
