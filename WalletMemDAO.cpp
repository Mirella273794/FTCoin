#include "WalletMemDAO.h"
#include <algorithm>

WalletMemDAO::WalletMemDAO() : lastId(0) {}

WalletMemDAO::~WalletMemDAO() {
    for (auto& pair : wallets) {
        delete pair.second;
    }
}

void WalletMemDAO::addWallet(Wallet* wallet) {
    wallets[wallet->getId()] = wallet;
    if (wallet->getId() > lastId) {
        lastId = wallet->getId();
    }
}

std::vector<Wallet*> WalletMemDAO::getAllWallets() {
    std::vector<Wallet*> result;
    for (const auto& pair : wallets) {
        result.push_back(pair.second);
    }
    return result;
}

Wallet* WalletMemDAO::getWalletById(int walletId) {
    auto it = wallets.find(walletId);
    if (it != wallets.end()) {
        return it->second;
    }
    return nullptr;
}

void WalletMemDAO::updateWallet(Wallet* wallet) {
    if (wallets.find(wallet->getId()) != wallets.end()) {
        *wallets[wallet->getId()] = *wallet;
    }
}

void WalletMemDAO::deleteWallet(int walletId) {
    auto it = wallets.find(walletId);
    if (it != wallets.end()) {
        delete it->second;
        wallets.erase(it);
    }
}

int WalletMemDAO::getNextId() {
    return ++lastId;
}