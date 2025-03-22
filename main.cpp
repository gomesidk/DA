#include "graph_loader.h"
#include <iostream>
using namespace std;

int main() {
    string locationsFile = "C:/Users/joaog/Documents/GitHub/DA/data/Locations.csv";
    string distancesFile = "C:/Users/joaog/Documents/GitHub/DA/data/Distances.csv";

    Graph<int> graph = GraphLoader::loadGraph(locationsFile, distancesFile);

    std::cout << "Graph loaded successfully with " << graph.getNumVertex() << " locations." << std::endl;
    return 0;
}
