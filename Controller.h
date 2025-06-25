#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include "Wallet.h"
#include "AbstractMovementDAO.h"
#include "Menu.h"

class Menu; 
class TextFromFile;

enum class DataBaseSelector { MEMORY, MARIADB };

class Controller {
private:
    std::vector<Wallet*> wallets;
    AbstractMovementDAO* movementDAO;
    
    void showMainMenu();
    void showWalletMenu();
    void showHelp();
    void createWallet();
    void editWallet();
    void deleteWallet();
    void listWallets();
    
    void showMovementMenu();
    void registerPurchase();
    void registerSale();
    void listMovements();
    double calculateBalance(int walletId);

public:
    Controller(DataBaseSelector dataBaseSelector = DataBaseSelector::MEMORY);
    ~Controller();
    void start();
};

#endif
