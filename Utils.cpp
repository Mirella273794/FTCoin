#include "Utils.h"
#include <iostream>

using namespace std;

void Utils::printMessage(const string& message) {
   cout << message <<endl;
}

string Utils::getInput(const string& prompt) {
   cout << prompt;
   string input;
   getline(cin, input);
    return input;
}

int Utils::getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            printMessage("Attention, invalid input! Please enter a number.");
        } else {
            cin.ignore();
            return value;
        }
    }
}