#ifndef WALLETDBDAO_H_
#define WALLETDBDAO_H_

#include "AbstractWalletDAO.h" 
#include "ServerDBConnection.h"  
#include "Wallet.h"             

#include <string>
#include <vector>

using namespace std;

class WalletDBDAO final : public AbstractWalletDAO {
private:
    ServerDBConnection* dbConnection;

    // Declaração das strings SQL que serão definidas no .cpp
    // Uma para cada método que precisa de um query
    static const string SQL_addWallet;
    static const string SQL_getAllWallets;
    static const string SQL_getWalletById;
    static const string SQL_updateWallet;
    static const string SQL_deleteWallet;
    static const string SQL_getNextId;

public:
    WalletDBDAO(ServerDBConnection* connection);
    
    virtual ~WalletDBDAO();

    virtual void addWallet(Wallet* wallet) override;
    virtual vector<Wallet*> getAllWallets() override;
    virtual Wallet* getWalletById(int walletId) override;
    virtual void updateWallet(Wallet* wallet) override;
    virtual void deleteWallet(int walletId) override;
    virtual int getNextId() override;
};

#endif /* WALLETDBDAO_H_ */