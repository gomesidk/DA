#include "graph_loader.h"
#include <iostream>
using namespace std;

int main() {
    string locationsFile = "data/locations.csv";
    string distancesFile = "data/distances.csv";

    Graph<int> graph = GraphLoader::loadGraph(locationsFile, distancesFile);

    std::cout << "Graph loaded successfully with " << graph.getNumVertex() << " locations." << std::endl;
    return 0;
}
