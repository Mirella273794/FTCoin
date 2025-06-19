#include "Controller.h"
#include "Menu.h"
#include "Utils.h"
#include "TextFromFile.h" 
#include <iostream>

using namespace std;

void Controller::start() {
    showMainMenu();
}

void Controller::showMainMenu() {
    Menu menu({"Wallets", "Help", "Exit"}, "Main Menu");
    
    while (true) {
        int choice = menu.getChoice();
        switch (choice) {
            case 1: showWalletMenu(); break;
            case 2: showHelp(); break;
            case 3: return;
        }
    }
}

void Controller::showHelp() {
    TextFromFile helpText("help.txt");
    Utils::printMessage(helpText.getContent());
}

void Controller::showWalletMenu() {
    Menu menu({"Create", "Edit", "Delete", "List", "Return"}, "Menu Wallets");
    
    while (true) {
        int choice = menu.getChoice();
        switch (choice) {
            case 1: createWallet(); break;
            case 2: editWallet(); break;
            case 3: deleteWallet(); break;
            case 4: listWallets(); break;
            case 5: return;
        }
    }
}

void Controller::createWallet() {
    string owner = Utils::getInput("Owner name: ");
    string broker = Utils::getInput("Broker: ");

    if (owner.empty() || broker.empty()) {
        Utils::printMessage("Attention, all fields must be filled in.");
        return;
    }

    int id = wallets.size() + 1;
    wallets.push_back(new Wallet(id, owner, broker));

    Utils::printMessage("Wallet created with ID: " + to_string(id));
}

void Controller::editWallet() {
    if (wallets.empty()) {
        Utils::printMessage("No wallet registered for Edit.");
        return;
    }

    listWallets();
    int id = Utils::getIntInput("Wallet ID for Edit: ");
    
    for (auto& wallet : wallets) {
        if (wallet->getId() == id) {
            string newOwner = Utils::getInput("New owner [" + wallet->getOwner() + "]: ");
            string newBroker = Utils::getInput("New broker [" + wallet->getBroker() + "]: ");
            
            if (newOwner.empty() || newBroker.empty()) {
                Utils::printMessage("Attention, all fields must be filled in.");
                return;
            }
            
            wallet->setOwner(newOwner);
            wallet->setBroker(newBroker);
            
            Utils::printMessage("Wallet updated successfully!");
            return;
        }
    }
    Utils::printMessage("Wallet not found!");
}

void Controller::deleteWallet() {
    if (wallets.empty()) {
        Utils::printMessage("No wallet registered for Delete.");
        return;
    }

    listWallets();
    int id = Utils::getIntInput("Wallet ID for Delete: ");
    
    for (auto it = wallets.begin(); it != wallets.end(); ++it) {
        if ((*it)->getId() == id) {

            string confirm = Utils::getInput("Are you sure you want to Delete? (Y/N): ");
            if (toupper(confirm[0]) != 'S') {
                Utils::printMessage("Operation cancelled.");
                return;
            }

            delete *it;
            wallets.erase(it);
            Utils::printMessage("Wallet deleted");
            return;
        }
    }
    Utils::printMessage("Wallet not found");
}

void Controller::listWallets() {
    if (wallets.empty()) {
        Utils::printMessage("No wallet registered.");
        return;
    }
    
    for (const auto& wallet : wallets) {
        Utils::printMessage(
            "ID: " + to_string(wallet->getId()) +
            " | Owner: " + wallet->getOwner() +
            " | Broker: " + wallet->getBroker()
        );
    }
}

Controller::~Controller() {
    for (auto wallet : wallets) {
        delete wallet;
    }
}