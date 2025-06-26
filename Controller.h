// Arquivo: Controller.h (VERSÃO CORRIGIDA E LIMPA)
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include "Wallet.h"
#include "AbstractMovementDAO.h"
#include "Menu.h"
#include "OracleService.hpp" // Dependência do OracleService continua
#include "RelatoriosService.hpp" 

class Menu; 
class TextFromFile;

enum class DataBaseSelector { MEMORY, MARIADB };

class Controller {
private:
    std::vector<Wallet*> wallets;
    AbstractMovementDAO* movementDAO;
    OracleService* oracleService; // O OracleService continua aqui

    void showMainMenu();
    void showWalletMenu();
    void showReportsMenu();
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