#include "graph.h"
#include "algorithms.h"
#include "MutablePriorityQueue.h"
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

std::vector<std::string> dijkstra(Graph<std::string>* g, const std::string& origin, const std::string& destination) {
    auto vertices = g->getVertexSet();
    std::unordered_map<std::string, std::string> pred;
    std::unordered_set<std::string> S; // Set of nodes whose shortest path is known

    // Inicializa distâncias, predecessores e adiciona todos os vértices à fila de prioridade
    for (auto v : vertices) {
        v->setDist(std::numeric_limits<double>::infinity());  // distâncias como infinito
        v->setVisited(false); // Inicializa como não visitado
        pred[v->getInfo()] = ""; // Inicializa todos os predecessores como ""
    }

    g->findVertex(origin)->setDist(0); // Distância da origem é 0
    pred[origin] = ""; // Não tem predecessor para a origem

    // Fila de prioridade mutável
    MutablePriorityQueue<Vertex<std::string>> pq;
    for (auto v : vertices) {
        pq.insert(v); // Adiciona todos os vértices à fila de prioridade
    }

    while (!pq.empty()) {
        Vertex<std::string>* u = pq.extractMin(); // Extrai o vértice com a menor distância

        S.insert(u->getInfo()); // Adiciona u ao conjunto S (vértices com caminho conhecido)

        // Relaxamento das arestas
        for (auto e : u->getAdj()) {
            std::string v = e->getDest()->getInfo();
            int driveTime = e->getDriveTime();

            if (driveTime < 0) continue; // Ignora ruas não transitáveis de carro

            double alt = u->getDist() + driveTime;
            if (alt < e->getDest()->getDist()) {
                e->getDest()->setDist(alt); // Atualiza a distância de v
                pred[v] = u->getInfo(); // Atualiza o predecessor de v
                pq.decreaseKey(e->getDest()); // Atualiza a posição de v na fila de prioridade
            }
        }
    }
    // Reconstrução do caminho
    std::vector<std::string> path;
    std::string current = destination;

    // Se a distância para o destino for infinita, significa que não existe caminho
    if (g->findVertex(current)->getDist() == std::numeric_limits<double>::infinity()) {
        return {}; // Não existe caminho
    }

    // Reconstruir o caminho a partir dos predecessores
    while (current != origin) {
        path.push_back(current);
        current = pred[current];
    }
    path.push_back(origin); // Adiciona a origem ao caminho
    std::reverse(path.begin(), path.end()); // Reverte o caminho para a ordem correta
    cout << path.size() << endl;
    return path;
}
