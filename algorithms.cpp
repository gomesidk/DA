// route_planner.cpp
#include "route_planner.h"
#include "graph.h"
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <string>
using namespace std;

std::vector<std::string> dijkstraDriving(Graph<std::string>* g, const std::string& origin, const std::string& destination) {
    auto vertices = g->getVertexSet();
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> prev;

    // Inicializar distâncias
    for (auto v : vertices) {
        dist[v->getInfo()] = std::numeric_limits<double>::infinity();
        v->setDist(std::numeric_limits<double>::infinity());
        v->setPath(nullptr);
        v->setVisited(false);
    }

    auto cmp = [&](const std::string& left, const std::string& right) {
        return dist[left] > dist[right];
    };

    std::priority_queue<std::string, std::vector<std::string>, decltype(cmp)> pq(cmp);

    dist[origin] = 0;
    pq.push(origin);

    while (!pq.empty()) {
        std::string u = pq.top();
        pq.pop();

        auto uVertex = g->findVertex(u);
        if (!uVertex || uVertex->isVisited()) continue;
        uVertex->setVisited(true);

        for (auto e : uVertex->getAdj()) {
            std::string v = e->getDest()->getInfo();
            int driveTime = e->getDriveTime();

            if (driveTime < 0) continue; // Ignorar ruas não transitáveis de carro

            double alt = dist[u] + driveTime;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push(v);
            }
        }
    }

    // Reconstroi o caminho
    std::vector<std::string> path;
    std::string current = destination;
    if (dist[current] == std::numeric_limits<double>::infinity()) {
        return {}; // Sem caminho
    }

    while (current != origin) {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(origin);
    std::reverse(path.begin(), path.end());
    return path;
}
