#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

#include "graph.h"
#include <string>

class GraphLoader {
public:
    static Graph<int> loadGraph(const std::string &locationsFile, const std::string &distancesFile);
};

#endif // GRAPH_LOADER_H
