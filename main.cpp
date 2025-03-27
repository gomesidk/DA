#include <iostream>
#include "graph_loader.h"
#include "menu.h"

using namespace std;

int main() {
    string locationsFile = "../data/locations.csv";
    string distancesFile = "../data/distances.csv";

    Graph<string> graph = GraphLoader::loadGraph(locationsFile, distancesFile);

    std::cout << "Graph loaded successfully with " << graph.getNumVertex() << " locations." << std::endl;

    main_menu();
    return 0;
}
