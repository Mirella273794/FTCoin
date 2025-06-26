#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include "Wallet.h"
#include "Menu.h"

#include "AbstractWalletDAO.h" 
#include "AbstractMovementDAO.h"
#include "WalletDBDAO.h"
#include "MovementDBDAO.h"
#include "WalletMemDAO.h"
#include "MovementMemDAO.h"
#include "FTCoinQuoteDAO.hpp"

#include "ServerDBConnection.h" 
#include "FTCoinMemoryDB.h"  
#include "OracleService.hpp"
#include "RelatoriosService.hpp" 

class Menu; 
class TextFromFile;

enum class DataBaseSelector { MEMORY, MARIADB };

class Controller {
private:
    AbstractWalletDAO* walletDAO = nullptr;
    AbstractMovementDAO* movementDAO = nullptr;
    OracleService* oracleService = nullptr; 
    FTCoinQuoteDAO* quoteDAO = nullptr; 
    RelatoriosService* reportsService = nullptr;

    ServerDBConnection* dbConnection = nullptr;
    DataBaseSelector dbSelector; 
    
    void showHelpMenu();    
    void showProgramGuide();  
    void showAbout();  
    
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

    void runOracle();

    void showReportsMenu();

public:
    Controller(DataBaseSelector dataBaseSelector);
    ~Controller();
    void start();
};

#endif
