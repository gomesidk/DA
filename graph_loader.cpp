#include "graph_loader.h"
#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

/**
 * Reads locations.csv and adds nodes to the graph.
 */
void readLocations(const string &filename, Graph<int> &graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, idStr, code, parkingStr;
        if (getline(ss, name, ',') &&
            getline(ss, idStr, ',') &&
            getline(ss, code, ',') &&
            getline(ss, parkingStr, ',')) {

            int id = std::stoi(idStr);
            bool hasParking = (parkingStr == "1");

            // Add vertex to graph (store parking info in the vertex if needed)
            graph.addVertex(id, hasParking);
        }
    }

    file.close();
}

/**
 * Reads distances.csv and adds edges to the graph.
 */
void readDistances(const std::string &filename, Graph<int> &graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header

    while (std::getline(file, line)) {
        stringstream ss(line);
        string loc1Str, loc2Str, drivingTimeStr, walkingTimeStr;
        if (std::getline(ss, loc1Str, ',') &&
            std::getline(ss, loc2Str, ',') &&
            std::getline(ss, drivingTimeStr, ',') &&
            std::getline(ss, walkingTimeStr, ',')) {

            int loc1 = stoi(loc1Str);
            int loc2 = stoi(loc2Str);
            int drivingTime = stoi(drivingTimeStr);
            int walkingTime = stoi(walkingTimeStr);

            // Add bidirectional edges for both driving and walking
            graph.addEdge(loc1, loc2, drivingTime, walkingTime); // Edge weight represents driving time
            graph.addEdge(loc2, loc1, drivingTime, walkingTime); // Since the graph is undirected
        }
    }

    file.close();
}

/**
 * Loads the graph from both CSV files.
 */
Graph<int> GraphLoader::loadGraph(const std::string &locationsFile, const std::string &distancesFile) {
    Graph<int> graph;
    readLocations(locationsFile, graph);
    readDistances(distancesFile, graph);
    return graph;
}

