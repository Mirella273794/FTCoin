#include "Utils.h"
#include <iostream>
#include <limits>

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
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            value = stoi(input); // Tenta converter a string para inteiro
            return value;
        } catch (const std::invalid_argument& e) {
            printMessage("Attention, invalid input! Please enter a number.");
        } catch (const std::out_of_range& e) {
            printMessage("Attention, number out of range!");
        }
    }
}

double Utils::getDoubleInput(const string& prompt) {
    double value;
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        for (char &ch : input) {
            if (ch == ',') {
                ch = '.';
            }
        }

        try {
            value = stod(input);
            return value;
        } catch (const std::invalid_argument& e) {
            printMessage("Invalid input! Please enter a number (e.g., 2000.00 or 100).");
        } catch (const std::out_of_range& e) {
            printMessage("Attention, number out of range!");
        }
    }
}
