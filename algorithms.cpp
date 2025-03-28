#include "graph.h"
#include "algorithms.h"
#include "MutablePriorityQueue.h"
#include <unordered_map>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

std::vector<std::string> dijkstra(Graph<std::string>* g, const std::string& origin, const std::string& destination) {
    auto vertices = g->getVertexSet();
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> pred;
    std::unordered_map<std::string, Vertex<std::string>*> vertexMap;

    // Inicializa distâncias e predecessores
    for (auto v : vertices) {
        dist[v->getInfo()] = std::numeric_limits<double>::infinity(); // distância infinita para todos
        v->setDist(std::numeric_limits<double>::infinity());
        v->setPath(nullptr);
        v->setVisited(false);
        vertexMap[v->getInfo()] = v; // Mapeia o ID da localização para o vértice
    }

    dist[origin] = 0; // Distância para a origem é 0
    pred[origin] = ""; // Não tem predecessor para a origem

    // Fila de prioridade mutável
    MutablePriorityQueue<Vertex<std::string>> pq;
    pq.insert(vertexMap[origin]);

    while (!pq.empty()) {
        Vertex<std::string>* u = pq.extractMin();

        // Relaxamento das arestas
        for (auto e : u->getAdj()) {
            std::string v = e->getDest()->getInfo();
            int driveTime = e->getDriveTime();

            if (driveTime < 0) continue; // Ignora ruas não transitáveis de carro

            double alt = dist[u->getInfo()] + driveTime;
            if (alt < dist[v]) {
                dist[v] = alt;
                pred[v] = u->getInfo();
                pq.decreaseKey(vertexMap[v]); // Atualiza a posição de v na fila de prioridade
            }
        }
    }

    // Reconstrução do caminho
    std::vector<std::string> path;
    std::string current = destination;

    if (dist[current] == std::numeric_limits<double>::infinity()) {
        return {}; // Não existe caminho
    }

    // Reconstruir o caminho a partir dos predecessores
    while (current != origin) {
        path.push_back(current);
        current = pred[current];
    }
    path.push_back(origin);
    std::reverse(path.begin(), path.end());
    cout << path.size() << endl;
    return path;
}
