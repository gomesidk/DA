#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void load_data();
void find_fastest_route();
void find_alternative_route();
void plan_restricted_route();
void plan_eco_route();
void process_batch_mode();
void main_menu();

int main() {
    ifstream infile("input.txt");
    string mode;

    cout << "Which mode do you want? Interactive or Batch Mode? (Enter 'I' for Interactive, 'B' for Batch): ";
    cin >> mode;

    if (mode == "I" || mode == "i") {
        cout << "You have chosen Interactive Mode." << endl;
        // Implement interactive mode logic here
        main_menu();
    }
    else if (mode == "B" || mode == "b") {
        cout << "You have chosen Batch Mode." << endl;
        if (!infile) {
            cout << "Error: Could not open input.txt." << endl;
            return 1;
        }
        // Implement batch processing logic here
    }
    else {
        cout << "Invalid choice. Please restart the program and enter 'I' or 'B'." << endl;
    }

    return 0;
}

void main_menu() {
    while (true) {
        int choice;
        string mode;
        cout << "We are now going to load you data" << endl;
        cout << "Choose the mode of your route: \n 1.Driving \n 2.Driving-Walking" << endl;
        cin >> choice;
        if (choice == 1) {
            mode = "Driving";
        }
        else if (choice == 2) {
            mode = "Driving-Walking";
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        cout << "Choose the source node of your route" << endl;
    }
}
