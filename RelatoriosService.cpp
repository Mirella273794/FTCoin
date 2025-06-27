#include "RelatoriosService.hpp"
#include "Utils.h" 
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

void RelatoriosService::_listWallets() {
    cout << "\n--- Available Wallets ---" << endl;
    if (wallets.empty()) {
        cout << "No wallets registered." << endl;
        return;
    }
    for (const auto& wallet : wallets) {
        cout << "ID: " << wallet->getId()
                  << " | Owner: " << wallet->getOwner()
                  << " | Broker: " << wallet->getBroker() << endl;
    }
    cout << "-------------------------" << endl;
}

RelatoriosService::RelatoriosService(const vector<Wallet*>& wallets, AbstractMovementDAO* movementDAO, OracleService* oracleService)
    : wallets(wallets), movementDAO(movementDAO), oracleService(oracleService) {}

string RelatoriosService::_getTodayDateString() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&now_time));
    return string(buffer);
}


void RelatoriosService::listWalletsById() {
    cout << "\n--- Wallets Sorted by ID ---" << endl;
    auto sortedWallets = this->wallets;

    sort(sortedWallets.begin(), sortedWallets.end(), [](const Wallet* a, const Wallet* b) {
        return a->getId() < b->getId();
    });

    for (const auto& wallet : sortedWallets) {
        cout << "ID: " << wallet->getId() 
                  << " | Owner: " << wallet->getOwner() 
                  << " | Broker: " << wallet->getBroker() << endl;
    }
    cout << "----------------------------------" << endl;
}

void RelatoriosService::listWalletsByOwnerName() {
    cout << "\n--- Wallets Sorted by Owner Name ---" << endl;
    auto sortedWallets = this->wallets;

    sort(sortedWallets.begin(), sortedWallets.end(), [](const Wallet* a, const Wallet* b) {
        return a->getOwner() < b->getOwner();
    });

    for (const auto& wallet : sortedWallets) {
        cout << "Owner: " << wallet->getOwner() 
                  << " | ID: " << wallet->getId() 
                  << " | Broker: " << wallet->getBroker() << endl;
    }
    cout << "------------------------------------------" << endl;
}

void RelatoriosService::displayCurrentBalance() {
    _listWallets();
    int idCarteira = Utils::getIntInput("\nEnter wallet ID to display balance: ");
    auto movimentacoes = movementDAO->getMovementsByWallet(idCarteira);
    double saldo = 0.0;
    for (const auto& mov : movimentacoes) {
        if (mov.getType() == 'C') saldo += mov.getAmount();
        else if (mov.getType() == 'V') saldo -= mov.getAmount();
    }
    
    cout << fixed << setprecision(2);
    cout << ">>> Current balance for wallet " << idCarteira << ": " << saldo << " " << Wallet(0, "", "").getCoin() << endl;
}

void RelatoriosService::displayTransactionHistory() {
    _listWallets();
    int idCarteira = Utils::getIntInput("\nEnter wallet ID to display history: ");
    auto movimentacoes = movementDAO->getMovementsByWallet(idCarteira);
    if (movimentacoes.empty()) {
        Utils::printMessage("No movements found for wallet ID " + to_string(idCarteira));
        return;
    }
    
    cout << "\n--- History for Wallet " << idCarteira << " ---" << endl;
    cout << fixed << setprecision(2);
    for (const auto& mov : movimentacoes) {
        cout << "Date: " << mov.getDate().getIsoFormat()
            << " | Type: " << mov.getType()
            << " | Amount: " << mov.getAmount() << endl;
    }
    cout << "--------------------------------" << endl;
}

void RelatoriosService::presentProfitLoss() {
    cout << "\n--- Profit/Loss Report ---" << endl;
    if (this->oracleService == nullptr) {
        Utils::printMessage("Oracle Service not available to calculate profit/loss.");
        return;
    }

    string today = _getTodayDateString();
    double cotacaoAtual = oracleService->getOrCreateQuote(today);

    cout << fixed << setprecision(2);

    for (const auto& carteira : this->wallets) {
        auto movimentacoes = movementDAO->getMovementsByWallet(carteira->getId());
        double totalInvestido = 0.0, totalVendido = 0.0, saldoMoedas = 0.0;

        for (const auto& mov : movimentacoes) {
            string dataMovimento = mov.getDate().getIsoFormat();
            double cotacaoDoDia = oracleService->getOrCreateQuote(dataMovimento);

            if (mov.getType() == 'C') {
                totalInvestido += mov.getAmount() * cotacaoDoDia;
                saldoMoedas += mov.getAmount();
            } else if (mov.getType() == 'V') {
                totalVendido += mov.getAmount() * cotacaoDoDia;
                saldoMoedas -= mov.getAmount();
            }
        }

        double valorAtualEmCarteira = saldoMoedas * cotacaoAtual;
        double lucroPrejuizo = (totalVendido + valorAtualEmCarteira) - totalInvestido;

        cout << "\nWallet ID: " << carteira->getId() << " (" << carteira->getOwner() << ")" << endl;
        cout << "  - RESULT: ";
        if (lucroPrejuizo >= 0) {
            cout << "[PROFIT] of R$ " << lucroPrejuizo << endl;
        } else {
            cout << "[LOSS] of R$ " << -lucroPrejuizo << endl;
        }
    }
    cout << "------------------------------------" << endl;
}