#include "Controller.h"
#include <iostream>

using namespace std;

int main() {
    char choice;
    DataBaseSelector dbSelector;

    cout << "Welcome to FTCoin!!!" << endl;
    cout << "Choose the persistence mode:" << endl;
    cout << "  [M] for In-Memory"  << endl;
    cout << "  [D] for Database (MariaDB)" << endl;
    cout << "> ";
    cin >> choice;

    if (toupper(choice) == 'D') {
        dbSelector = DataBaseSelector::MARIADB;
    } else {
        dbSelector = DataBaseSelector::MEMORY;
    }

    Controller controller(dbSelector);
    controller.start(); 

    return 0;
}