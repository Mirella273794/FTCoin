#ifndef ABSTRACT_WALLET_DAO_H
#define ABSTRACT_WALLET_DAO_H

#include <vector>
#include "Wallet.h"

using namespace std;

class AbstractWalletDAO {
public:
    virtual ~AbstractWalletDAO() {}
    
    virtual void addWallet(Wallet* wallet) = 0;
    virtual vector<Wallet*> getAllWallets() = 0;
    virtual Wallet* getWalletById(int walletId) = 0;
    virtual void updateWallet(Wallet* wallet) = 0;
    virtual void deleteWallet(int walletId) = 0;
    virtual int getNextId() = 0;
};

#endif