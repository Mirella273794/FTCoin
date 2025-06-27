#include "Controller.h"
#include "Utils.h"
#include "MovementMemDAO.h"
#include "WalletMemDAO.h"
#include "Menu.h"
#include "TextFromFile.h" 
#include "Sysinfo.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime> 

using namespace std;

Controller::Controller(DataBaseSelector dataBaseSelector) : dbSelector(dataBaseSelector) {
    if (dataBaseSelector == DataBaseSelector::MARIADB) {
        dbConnection = new ServerDBConnection();
        walletDAO = new WalletDBDAO(dbConnection);
        movementDAO = new MovementDBDAO(dbConnection);
        quoteDAO = new FTCoinQuoteDAO("143.106.243.64", "3306", "PooI_25_B05", "blwltAO53Y", "PooI_25_B05");
        oracleService = new OracleService(*quoteDAO);

    } else {
        walletDAO = new WalletMemDAO(); 
        movementDAO = new MovementMemDAO();
        oracleService = nullptr;
    }
}

void Controller::start() {
    showMainMenu();
}

void Controller::showMainMenu() {
    Menu menu({"Wallets",  "Movements", "Oracle", "Reports", "Help", "Exit"}, "Main Menu");
    
    while (true) {
        int choice = menu.getChoice();
        switch (choice) {
            case 1: showWalletMenu(); break;
            case 2: showMovementMenu(); break;
            case 3: runOracle(); break;
            case 4: showReportsMenu(); break;
            case 5: showHelpMenu(); break;
            case 6: return;
        }
    }
}

void Controller::showHelpMenu() {
    Menu helpMenu({"Program Guide", "About", "Return"}, "Help Menu");

    while (true) {
        int choice = helpMenu.getChoice();
        switch (choice) {
            case 1: showProgramGuide(); break;
            case 2: showAbout(); break;
            case 3: return; 
        }
    }
}

void Controller::showProgramGuide() {
    TextFromFile helpText("help.txt");
    Utils::printMessage(helpText.getFileContent());
}

void Controller::showAbout() {
    time_t now = time(0);
    char* dt = ctime(&now);

    cout << "\n--- About FTCoin Wallet System ---" << endl;
    cout << "Version: " << SysInfo::getVersion() << endl;
    cout << "Authors: " << SysInfo::getAuthor() << endl;
    cout << "Copyright (c) 2025" << endl;
    cout << "Date: " << dt;
    cout << "--------------------------------" << endl;
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
        Utils::printError("Attention, all fields must be filled in.");
        return;
    }

    int id = walletDAO->getNextId();
    Wallet* wallet = new Wallet(id, owner, broker);
    walletDAO->addWallet(wallet);

    Utils::printSuccess("Wallet created successfully!\n");
    Utils::printMessage("Wallet created with ID: " + to_string(id));
}

void Controller::editWallet() {
    auto wallets = walletDAO->getAllWallets();
    if (wallets.empty()) {
        Utils::printError("No wallet registered for Edit.");
        return;
    }

    listWallets();
    int id = Utils::getIntInput("Wallet ID for Edit: ");
    
    Wallet* wallet = walletDAO->getWalletById(id);
    if (wallet) {
        string newOwner = Utils::getInput("New owner [" + wallet->getOwner() + "]: ");
        string newBroker = Utils::getInput("New broker [" + wallet->getBroker() + "]: ");
            
        if (newOwner.empty() || newBroker.empty()) {
            Utils::printError("Attention, all fields must be filled in.");
            return;
        }
            
        wallet->setOwner(newOwner);
        wallet->setBroker(newBroker);
        walletDAO->updateWallet(wallet);
        
        Utils::printSuccess("Wallet updated successfully!");
    } else {
        Utils::printError("Wallet not found!");
    }
}

void Controller::deleteWallet() {
    auto wallets = walletDAO->getAllWallets();
    if (wallets.empty()) {
        Utils::printError("No wallet registered for Delete.");
        return;
    }

    listWallets();
    int id = Utils::getIntInput("Wallet ID for Delete: ");
    
        string confirm = Utils::getInput("Are you sure you want to Delete? (Y/N): ");
        if (toupper(confirm[0]) != 'Y') {
            Utils::printError("Operation cancelled.");
            return;
        }

    if (walletDAO->getWalletById(id)) {
        movementDAO->deleteMovementsByWallet(id);
        walletDAO->deleteWallet(id);

        Utils::printSuccess("Wallet deleted successfully!");
    } else {
        Utils::printError("Wallet not found!");
    }
}

void Controller::listWallets() {
    auto wallets = walletDAO->getAllWallets();
    if (wallets.empty()) {
        Utils::printError("No wallet registered.");
        return;
    }
    
    for (const auto& wallet : wallets) {
        Utils::printMessage(
            "ID: " + to_string(wallet->getId()) +
            " | Owner: " + wallet->getOwner() +
            " | Broker: " + wallet->getBroker() +
            " | Coin: " + wallet->getCoin()
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
    auto wallets = walletDAO->getAllWallets();
    if (wallets.empty()) {
        Utils::printError("No wallets registered. Please create a wallet first.");
        return;
    }
    
    listWallets();
    int walletId = Utils::getIntInput("Wallet ID: ");

    if (!walletDAO->getWalletById(walletId)) {
    Utils::printError("Invalid wallet ID!");
    return; 
    }
    
    string dateStr = Utils::getInput("Enter the date (format: YYYY-MM-DD): ");
    Date date(dateStr);
    
    double amount = Utils::getDoubleInput("Amount to purchase: ");
    
    if (amount <= 0) {
        Utils::printError("Amount must be positive!");
        return;
    }
    
    int movementId = movementDAO->getNextMovementId();
    Movement movement(walletId, movementId, date, 'C', amount);
    movementDAO->addMovement(movement);
    
    Utils::printSuccess("Purchase registered successfully");
    Utils::printMessage("Purchase registered with ID: " + to_string(movementId));
}

void Controller::registerSale() {
    auto wallets = walletDAO->getAllWallets();
    if (wallets.empty()) {
        Utils::printError("No wallets registered. Please create a wallet first.");
        return;
    }
    
    listWallets();
    int walletId = Utils::getIntInput("Wallet ID: ");

    if (!walletDAO->getWalletById(walletId)) {
        Utils::printError("Invalid wallet ID!");
        return;
    }

    double balance = calculateBalance(walletId);

    if (balance <= 0) {
        Utils::printError("Insufficient balance for sale!");
        return;
    }

    stringstream stream;
    stream << fixed << setprecision(2) << balance;
    string formattedBalance = stream.str();
    
    string dateStr = Utils::getInput("Enter the date (format: YYYY-MM-DD): ");
    Date date(dateStr);
    
    double amount = Utils::getDoubleInput("Amount to sell (max " + formattedBalance + "): ");    
    if (amount <= 0 || amount > balance) {
        Utils::printError("Invalid amount!");
        return;
    }
    
    int movementId = movementDAO->getNextMovementId();
    Movement movement(walletId, movementId, date, 'V', amount);
    movementDAO->addMovement(movement);
    
    Utils::printSuccess("Sale registered successfully\n");
    Utils::printMessage("Sale registered with ID: " + to_string(movementId));
}

void Controller::listMovements() {
    auto wallets = walletDAO->getAllWallets();
    if (wallets.empty()) {
        Utils::printError("No wallets registered.");
        return;
    }
    
    listWallets();
    int walletId = Utils::getIntInput("Wallet ID to list movements: ");
    
    auto movements = movementDAO->getMovementsByWallet(walletId);
    if (movements.empty()) {
        Utils::printError("No movements found for this wallet.");
        return;
    }
    
    Utils::printMessage("=== Movements for Wallet ID: " + to_string(walletId) + " ===");
    for (const auto& movement : movements) {
        string typeStr = (movement.getType() == 'C') ? "Purchase" : "Sale";
        cout << "ID: " << movement.getMovementId()
                  << " | Date: " << movement.getDate().getIsoFormat()
                  << " | Type: " << typeStr
                  << " | Amount: " << fixed << setprecision(2) << movement.getAmount() << endl;
    }
    
    double balance = calculateBalance(walletId);
    const std::string CYAN = "\033[36m";
    const std::string RESET = "\033[0m";
    cout << "Current balance: " << CYAN << fixed << setprecision(2) << balance << RESET << endl;
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

void Controller::runOracle() {
    if (dbSelector != DataBaseSelector::MARIADB) {
        Utils::printError("Oracle is only available in MariaDB (database) mode.");
        return;
    }

    const string GREEN = "\033[32m";
    const string RESET = "\033[0m";
    string date;

    cout << "\n=== FTCoin Quote Oracle ===" << endl;
    cout << "Enter a date (format: YYYY-MM-DD) or type 'exit' to return:" << endl;

    while (true) {
        cout << "> ";
        getline(cin, date);

        if (date == "exit") {
            break;
        }

        try {
            double quote = oracleService->getOrCreateQuote(date);

            cout << "Quote for " << date << ": "
                 << GREEN
                 << "R$ " << fixed << setprecision(2) << quote
                 << RESET
                 << endl;
        } catch (const exception& e) {
            Utils::printError(e.what());
        }
    }
}

void Controller::showReportsMenu() {
    vector<string> menuItems = {
        "List wallets by ID",
        "List wallets by owner name",
        "Display wallet balance",
        "Display wallet transaction history",
        "Display profit/loss report",
        "Return"
    };
    Menu reportsMenu(menuItems, "Reports Menu");

    auto wallets = walletDAO->getAllWallets();
    if (wallets.empty()) {
        Utils::printError("No wallets registered to generate reports.");
        return;
    }

    RelatoriosService reportsService(wallets, movementDAO, oracleService);

    while (true) {
        int choice = reportsMenu.getChoice();
        switch (choice) {
            case 1: reportsService.listWalletsById(); break;
            case 2: reportsService.listWalletsByOwnerName(); break;
            case 3: reportsService.displayCurrentBalance(); break;
            case 4: reportsService.displayTransactionHistory(); break;
            case 5: reportsService.presentProfitLoss(); break;
            case 6: return;
        }
    }
}

Controller::~Controller() {
    delete walletDAO;
    delete movementDAO;
    if (dbConnection) {
        delete dbConnection;
    }
     if (quoteDAO) {
        delete quoteDAO;
    }
    if (oracleService) {
        delete oracleService;
    }
    if (reportsService) {
        delete reportsService;
    }
}
