#include "graph_loader.h"
#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;

/**
 * Reads locations.csv and adds nodes to the graph.
 */
void readLocations(const string &filename, Graph<string> &graph) {
    ifstream file(filename);


    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        cerr << "Current working directory: " << std::filesystem::current_path() << endl;
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

            bool hasParking = (parkingStr == "1");
            int id = stoi(idStr);
            // Add vertex to graph (store parking info in the vertex if needed)
            graph.addVertex(code, hasParking, id);
        }
    }

    file.close();
}

/**
 * Reads distances.csv and adds edges to the graph.
 */
void readDistances(const std::string &filename, Graph<string> &graph) {
    int num_of_edges = 0;
    int driving_time;
    int walking_time;
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header

    while (std::getline(file, line)) {
        stringstream ss(line);
        string loc1, loc2, drivingTimeStr, walkingTimeStr;
        if (std::getline(ss, loc1, ',') &&
            std::getline(ss, loc2, ',') &&
            std::getline(ss, drivingTimeStr, ',') &&
            std::getline(ss, walkingTimeStr, ',')) {

            if (drivingTimeStr == "X") {
                driving_time = -1;
            }
            else {
                driving_time = stoi(drivingTimeStr);
                walking_time = stoi(walkingTimeStr);
            }

            // Add bidirectional edges for both driving and walking
            num_of_edges++;
            graph.addEdge(loc1, loc2, driving_time, walking_time); // Edge weight represents driving time
            graph.addEdge(loc2, loc1, driving_time, walking_time);// Since the graph is undirected
        }
    }
    cout << "number of edges: " << num_of_edges << endl;
    file.close();
}

/**
 * Loads the graph from both CSV files.
 */
Graph<string> GraphLoader::loadGraph(const std::string &locationsFile, const std::string &distancesFile) {
    Graph<string> graph;
    readLocations(locationsFile, graph);
    readDistances(distancesFile, graph);
    return graph;
}

