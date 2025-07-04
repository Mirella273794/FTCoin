#ifndef RELATORIOS_SERVICE_H
#define RELATORIOS_SERVICE_H

#include <optional>
#include <cstdint>
#include <vector>
#include "Wallet.h"
#include "AbstractMovementDAO.h"
#include "OracleService.hpp"

class RelatoriosService {
private:
    const std::vector<Wallet*>& wallets;
    AbstractMovementDAO* movementDAO;
    OracleService* oracleService;

    std::string _getTodayDateString();
    void _listWallets();

public:
    RelatoriosService(const std::vector<Wallet*>& wallets, AbstractMovementDAO* movementDAO, OracleService* oracleService);

    void listWalletsById();
    void listWalletsByOwnerName();
    void displayCurrentBalance();
    void displayTransactionHistory();
    void presentProfitLoss();
};

#endif 