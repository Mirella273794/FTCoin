#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(const vector<string>& items, 
           const string& title, 
           const string& message)
    : items(items), title(title), message(message) {}

int Menu::getChoice() const {
    int choice;
    do {
        cout << "\n=== " << title << " ===\n";
        for (size_t i = 0; i < items.size(); i++) {
            cout << i+1 << ". " << items[i] << "\n";
        }
        cout << message;
        cin >> choice;
        cin.ignore();
    } while (choice < 1 || choice > items.size());
    return choice;
}