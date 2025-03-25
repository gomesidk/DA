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
    if (infile.good()) {
        cout << "Batch mode detected. Processing input.txt..." << endl;
        //process_batch_mode();
    } else {
        main_menu();
    }
    return 0;
}

void main_menu() {
    while (true) {
        cout << "\n==== Route Planning Tool ====" << endl;
        cout << "1. Load Data" << endl;
        cout << "2. Find Fastest Route" << endl;
        cout << "3. Find Alternative Route" << endl;
        cout << "4. Plan a Restricted Route" << endl;
        cout << "5. Plan an Environmentally Friendly Route" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                //load_data();
            break;
            case 2:
                //find_fastest_route();
            break;
            case 3:
                //find_alternative_route();
            break;
            case 4:
                //plan_restricted_route();
            break;
            case 5:
                //plan_eco_route();
            break;
            case 6:
                cout << "Exiting..." << endl;
            return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
