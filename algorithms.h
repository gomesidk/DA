// route_planner.h
#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include "graph.h"
#include <string>
#include <vector>

// Função para calcular o caminho mais rápido em modo Driving
std::vector<std::string> dijkstra(Graph<std::string>* g, const std::string& origin, const std::string& destination);

#endif // ROUTE_PLANNER_H

