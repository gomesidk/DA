#ifndef MENU_H  // Prevent multiple inclusions
#define MENU_H
#include <string>
using namespace std;
// Function declaration for the main menu
void main_menu();

struct RouteOptions {
    string mode;
    int sourceNode;
    int destinationNode;
    vector<int> avoidedNodes;
    vector<pair<int, int>> avoidedSegments;
    int includedNode;
};

void menu(RouteOptions &options);

#endif // MENU_H