#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "Wallet.h"

class Menu; 
class TextFromFile;

class Controller {
private:
    std::vector<Wallet*> wallets;
    
    void showMainMenu();
    void showWalletMenu();
    void showHelp();
    void createWallet();
    void editWallet();
    void deleteWallet();
    void listWallets();
    
public:
    void start();
    ~Controller();
};

#endif