#include "Controller.h"
#include "Utils.h"
#include "MovementMemDAO.h"
#include "Menu.h"
#include "TextFromFile.h" 
#include <iostream>

using namespace std;

Controller::Controller(DataBaseSelector dataBaseSelector) {
    movementDAO = new MovementMemDAO();
}

void Controller::start() {
    showMainMenu();
}

void Controller::showMainMenu() {
    Menu menu({"Wallets",  "Movements", "Help", "Exit"}, "Main Menu");
    
    while (true) {
        int choice = menu.getChoice();
        switch (choice) {
            case 1: showWalletMenu(); break;
            case 2: showMovementMenu(); break;
            case 3: showHelp(); break;
            case 4: return;
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
            if (toupper(confirm[0]) != 'Y') {
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

void Controller::showMovementMenu() {
    vector<string> menuItems = { "Register Purchase", "Register Sale", "List Movements", "Return" };
    Menu movementMenu(menuItems, "Movements Menu");
    
    int choice;
    while ((choice = movementMenu.getChoice()) != 4) {
        switch (choice) {
            case 1: registerPurchase(); break;
            case 2: registerSale(); break;
            case 3: listMovements(); break;
        }
    }
}

void Controller::registerPurchase() {
    if (wallets.empty()) {
        Utils::printMessage("No wallets registered. Please create a wallet first.");
        return;
    }
    
    listWallets();
    int walletId = Utils::getIntInput("Wallet ID: ");
    
    Date date;
    cout << "Date (DD.MM.YYYY): ";
    cin >> date;
    cin.ignore();
    
    double amount = Utils::getDoubleInput("Amount to purchase: ");
    
    if (amount <= 0) {
        Utils::printMessage("Amount must be positive!");
        return;
    }
    
    int movementId = movementDAO->getNextMovementId();
    Movement movement(walletId, movementId, date, 'C', amount);
    movementDAO->addMovement(movement);
    
    Utils::printMessage("Purchase registered successfully with ID: " + to_string(movementId));
}

void Controller::registerSale() {
    if (wallets.empty()) {
        Utils::printMessage("No wallets registered. Please create a wallet first.");
        return;
    }
    
    listWallets();
    int walletId = Utils::getIntInput("Wallet ID: ");
    double balance = calculateBalance(walletId);
    
    if (balance <= 0) {
        Utils::printMessage("Insufficient balance for sale!");
        return;
    }
    
    Date date;
    cout << "Date (DD.MM.YYYY): ";
    cin >> date;
    cin.ignore();
    
    double amount = Utils::getDoubleInput("Amount to sell (max " + to_string(balance) + "): ");
    
    if (amount <= 0 || amount > balance) {
        Utils::printMessage("Invalid amount!");
        return;
    }
    
    int movementId = movementDAO->getNextMovementId();
    Movement movement(walletId, movementId, date, 'V', amount);
    movementDAO->addMovement(movement);
    
    Utils::printMessage("Sale registered successfully with ID: " + to_string(movementId));
}

void Controller::listMovements() {
    if (wallets.empty()) {
        Utils::printMessage("No wallets registered.");
        return;
    }
    
    listWallets();
    int walletId = Utils::getIntInput("Wallet ID to list movements: ");
    
    auto movements = movementDAO->getMovementsByWallet(walletId);
    if (movements.empty()) {
        Utils::printMessage("No movements found for this wallet.");
        return;
    }
    
    Utils::printMessage("=== Movements for Wallet ID: " + to_string(walletId) + " ===");
    for (const auto& movement : movements) {
        string typeStr = (movement.getType() == 'C') ? "Purchase" : "Sale";
        Utils::printMessage(
            "ID: " + to_string(movement.getMovementId()) +
            " | Date: " + movement.getDate().toString() +
            " | Type: " + typeStr +
            " | Amount: " + to_string(movement.getAmount())
        );
    }
    
    double balance = calculateBalance(walletId);
    Utils::printMessage("Current balance: " + to_string(balance));
}

double Controller::calculateBalance(int walletId) {
    auto movements = movementDAO->getMovementsByWallet(walletId);
    double balance = 0.0;
    
    for (const auto& movement : movements) {
        if (movement.getType() == 'C') {
            balance += movement.getAmount();
        } else {
            balance -= movement.getAmount();
        }
    }
    
    return balance;
}

Controller::~Controller() {
    for (auto wallet : wallets) {
        delete wallet;
    }
    delete movementDAO;
}
