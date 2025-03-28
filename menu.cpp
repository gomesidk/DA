#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "menu.h"
#include "route_planner.h"

using namespace std;


void main_menu() {
    ifstream infile("input.txt");
    string mode;
    RouteOptions options;
    cout << "Which mode do you want? Interactive or Batch Mode? (Enter 'I' for Interactive, 'B' for Batch): ";
    cin >> mode;

    if (mode == "I" || mode == "i") {
        cout << "You have chosen Interactive Mode." << endl;
        // Implement interactive mode logic here
        menu(options);
    }
    else if (mode == "B" || mode == "b") {
        cout << "You have chosen Batch Mode." << endl;
        if (!infile) {
            cout << "Error: Could not open input.txt." << endl;
        }
        if (batch_mode(options)) {
            cout << "batch mode successful" << endl;
        }
        else {
            cout << "batch mode failed" << endl;
        }
    }
    else {
        cout << "Invalid choice. Please restart the program and enter 'I' or 'B'." << endl;
    }

}

void menu(RouteOptions &options) {
        int choice;
        int node;
        int source_node2;
        int destination_node2;
        cout << "We are now going to load you data" << endl;
        cout << "Choose the mode of your route: \n 1.Driving \n 2.Driving-Walking" << endl;
        cin >> choice;
        if (choice == 1) {
            options.mode = "Driving";
        }
        else if (choice == 2) {
            options.mode = "Driving-Walking";
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
            cout << "Choose the mode of your route: \n 1.Driving \n 2.Driving-Walking" << endl;
            cin >> choice;
            if (choice == 1) {
                options.mode = "Driving";
            }
            else if (choice == 2) {
                options.mode = "Driving-Walking";
            }
        }
        cout << "Choose the source node of your route" << endl;
        cin >> options.sourceNode;
        cout  << "Choose the destination node of your route" << endl;
        cin >> options.destinationNode;
        cout << "Would you like to avoid any nodes? Press 1 if yes, press 2 if no." << endl;
        cin >> choice;
        if (choice == 1) {
            while (true) {
                cout << "Enter the nodes you would like to avoid" << endl;
                cin >> node;
                options.avoidedNodes.push_back(node);
                cout << "Is there any node you would like to avoid? Press 1 for yes, press 2 for no." << endl;
                cin >> choice;
                if (choice == 2) {
                    break;
                }
                if (choice != 1 && choice != 2) {
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Is there any node you would like to avoid? Press 1 for yes, press 2 for no." << endl;
                    cin >> choice;
                    if (choice == 2) {
                        break;
                    }
                }
            }
        }
        cout << "Is there any segments you would like to avoid?" << endl;
        cin >> choice;
        if (choice == 1) {
            while (true) {
                cout << "Enter the source node of the segment you would like to avoid" << endl;
                cin >> source_node2;
                cout << "Enter the destination node of the segment you would like to avoid" << endl;
                cin >> destination_node2;
                options.avoidedSegments.push_back(make_pair(source_node2, destination_node2));
                cout << "Would you like to enter anymore segments you would like to avoid? Press 1 for yes. Press 2 for no." << endl;
                cin >> choice;
                if (choice == 2) {
                    break;
                }
                if (choice != 1 && choice != 2) {
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Would you like to enter anymore segments you would like to avoid? Press 1 for yes. Press 2 for no." << endl;
                    cin >> choice;
                    if (choice == 2) {
                        break;
                    }
                }
            }
        }
        cout << "Is there any node you would like to include? Press 1 for yes. Press 2 for no." << endl;
        cin >> choice;
        if (choice == 1) {
            cout << "Enter the node you would like to include." << endl;
            cin >> options.includedNode;
        }
        if (choice != 2 && choice != 1) {
            cout << "Invalid choice. Please try again." << endl;
            cout << "Is there any node you would like to include? Press 1 for yes. Press 2 for no." << endl;
            cin >> choice;
            if (choice == 1) {
                cout << "Enter the node you would like to include." << endl;
                cin >> options.includedNode;
            }
        }
    dijkstraDriving(g, options.includedNode, options.destinationNode);

}

bool batch_mode(RouteOptions &options) {
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Error: Could not open input.txt." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, ':') && std::getline(iss, value)) {

            if (key == "Mode") {
                options.mode = value;
            }
            else if (key == "Source") {
                options.sourceNode = std::stoi(value);
            }
            else if (key == "Destination") {
                options.destinationNode = std::stoi(value);
            }
            else if (key == "AvoidNodes") {
                std::istringstream nodeStream(value);
                std::string node;
                while (std::getline(nodeStream, node, ',')) {
                    options.avoidedNodes.push_back(std::stoi(node));
                }
            }
            else if (key == "AvoidSegments") {
                std::istringstream segmentStream(value);
                std::string segment;
                while (std::getline(segmentStream, segment, ')')) {
                    if (segment.empty()) continue;
                    segment.erase(0, 1);  // Remove leading '('
                    std::replace(segment.begin(), segment.end(), ',', ' ');
                    std::istringstream segStream(segment);
                    int from, to;
                    if (segStream >> from >> to) {
                        options.avoidedSegments.push_back({from, to});
                    }
                }
            }
            else if (key == "IncludeNode") {
                options.includedNode = std::stoi(value);
            }
        }
    }

    infile.close();
    return true;
}

