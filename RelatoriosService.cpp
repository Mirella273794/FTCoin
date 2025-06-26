#include "RelatoriosService.hpp"
#include "Utils.h" 
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>

// Construtor
RelatoriosService::RelatoriosService(const std::vector<Wallet*>& wallets, AbstractMovementDAO* movementDAO, OracleService* oracleService)
    : wallets(wallets), movementDAO(movementDAO), oracleService(oracleService) {}

std::string RelatoriosService::_getTodayDateString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&now_time));
    return std::string(buffer);
}


// 1. Listar carteiras por ID
void RelatoriosService::listarCarteirasPorId() {
    std::cout << "\n--- Wallets Sorted by ID ---" << std::endl;
    auto sortedWallets = this->wallets;

    std::sort(sortedWallets.begin(), sortedWallets.end(), [](const Wallet* a, const Wallet* b) {
        return a->getId() < b->getId();
    });

    for (const auto& wallet : sortedWallets) {
        std::cout << "ID: " << wallet->getId() 
                  << " | Owner: " << wallet->getOwner() 
                  << " | Broker: " << wallet->getBroker() << std::endl;
    }
    std::cout << "----------------------------------" << std::endl;
}

// 2. Listar carteiras por Nome do Titular
void RelatoriosService::listarCarteirasPorNome() {
    std::cout << "\n--- Wallets Sorted by Owner Name ---" << std::endl;
    auto sortedWallets = this->wallets;

    std::sort(sortedWallets.begin(), sortedWallets.end(), [](const Wallet* a, const Wallet* b) {
        return a->getOwner() < b->getOwner();
    });

    for (const auto& wallet : sortedWallets) {
        std::cout << "Owner: " << wallet->getOwner() 
                  << " | ID: " << wallet->getId() 
                  << " | Broker: " << wallet->getBroker() << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
}

// 3. Exibir saldo atual de uma carteira
void RelatoriosService::exibirSaldoAtual() {
    int idCarteira = Utils::getIntInput("\nEnter wallet ID to display balance: ");
    auto movimentacoes = movementDAO->getMovementsByWallet(idCarteira);
    double saldo = 0.0;
    for (const auto& mov : movimentacoes) {
        if (mov.getType() == 'C') saldo += mov.getAmount();
        else if (mov.getType() == 'V') saldo -= mov.getAmount();
    }
    
    std::cout << std::fixed << std::setprecision(8);
    std::cout << ">>> Current balance for wallet " << idCarteira << ": " << saldo << " " << Wallet(0, "", "").getCoin() << std::endl;
}

// 4. Historico de movimentações
void RelatoriosService::exibirHistoricoMovimentacao() {
    int idCarteira = Utils::getIntInput("\nEnter wallet ID to display history: ");
    auto movimentacoes = movementDAO->getMovementsByWallet(idCarteira);
    if (movimentacoes.empty()) {
        Utils::printMessage("No movements found for wallet ID " + std::to_string(idCarteira));
        return;
    }
    
    std::cout << "\n--- History for Wallet " << idCarteira << " ---" << std::endl;
    std::cout << std::fixed << std::setprecision(8);
    for (const auto& mov : movimentacoes) {
        std::cout << "Date: " << mov.getDate().getIsoFormat()
                  << " | Type: " << mov.getType()
                  << " | Amount: " << mov.getAmount() << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

// 5. Ganho/Perda
void RelatoriosService::apresentarGanhoPerda() {
    std::cout << "\n--- Profit/Loss Report ---" << std::endl;
    if (this->oracleService == nullptr) {
        Utils::printMessage("Oracle Service not available to calculate profit/loss.");
        return;
    }

    std::string today = _getTodayDateString();
    double cotacaoAtual = oracleService->getOrCreateQuote(today);

    std::cout << std::fixed << std::setprecision(2);

    for (const auto& carteira : this->wallets) {
        auto movimentacoes = movementDAO->getMovementsByWallet(carteira->getId());
        double totalInvestido = 0.0, totalVendido = 0.0, saldoMoedas = 0.0;

        for (const auto& mov : movimentacoes) {
            std::string dataMovimento = mov.getDate().getIsoFormat();
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

        std::cout << "\nWallet ID: " << carteira->getId() << " (" << carteira->getOwner() << ")" << std::endl;
        std::cout << "  - RESULT: ";
        if (lucroPrejuizo >= 0) {
            std::cout << "[PROFIT] of R$ " << lucroPrejuizo << std::endl;
        } else {
            std::cout << "[LOSS] of R$ " << -lucroPrejuizo << std::endl;
        }
    }
    std::cout << "------------------------------------" << std::endl;
}