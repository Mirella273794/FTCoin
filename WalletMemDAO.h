#ifndef WALLET_MEM_DAO_H
#define WALLET_MEM_DAO_H

#include "AbstractWalletDAO.h"
#include <vector>
#include <map>

using namespace std;

class WalletMemDAO : public AbstractWalletDAO {
private:
    map<int, Wallet*> wallets;
    int lastId;
    
public:
    WalletMemDAO();
    ~WalletMemDAO();
    
    void addWallet(Wallet* wallet) override;
    vector<Wallet*> getAllWallets() override;
    Wallet* getWalletById(int walletId) override;
    void updateWallet(Wallet* wallet) override;
    void deleteWallet(int walletId) override;
    int getNextId() override;
};

#endif