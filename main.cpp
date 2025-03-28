#include <iostream>
#include "graph_loader.h"
#include "menu.h"

using namespace std;

int main() {
    string locationsFile = "../data/Locations.csv";
    string distancesFile = "../data/Distances.csv";

    Graph<string> graph = GraphLoader::loadGraph(locationsFile, distancesFile);

    std::cout << "Graph loaded successfully with " << graph.getNumVertex() << " locations." << std::endl;

    main_menu(graph);
    return 0;
}
