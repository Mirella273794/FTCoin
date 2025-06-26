/* ********************************************************************************
 * FT_Coin - WalletDBDAO.h
 * Descrição: Declaração da implementação do DAO de Wallet para MariaDB.
 * (Versão atualizada para corresponder à interface AbstractWalletDAO)
 ******************************************************************************** */

#ifndef WALLETDBDAO_H_
#define WALLETDBDAO_H_

#include "AbstractWalletDAO.h" // Inclui o "contrato" que a classe deve seguir
#include "ServerDBConnection.h"  // Inclui a classe de conexão com o BD
#include "Wallet.h"              // Inclui a definição do objeto Wallet

#include <string>
#include <vector>

using namespace std;

class WalletDBDAO final : public AbstractWalletDAO {
private:
    ServerDBConnection* dbConnection;

    // Declaração das strings SQL que serão definidas no .cpp
    // Uma para cada método que precisa de uma query.
    static const string SQL_addWallet;
    static const string SQL_getAllWallets;
    static const string SQL_getWalletById;
    static const string SQL_updateWallet;
    static const string SQL_deleteWallet;
    static const string SQL_getNextId;

public:
    // Construtor que recebe a conexão com o banco de dados
    WalletDBDAO(ServerDBConnection* connection);
    
    // Destrutor virtual padrão
    virtual ~WalletDBDAO();

    // ---------------------------------------------------------------------------
    // Implementação dos métodos da interface AbstractWalletDAO.
    // A palavra-chave 'override' garante que a assinatura do método aqui
    // corresponde exatamente à da classe base.
    // ---------------------------------------------------------------------------
    virtual void addWallet(Wallet* wallet) override;
    virtual vector<Wallet*> getAllWallets() override;
    virtual Wallet* getWalletById(int walletId) override;
    virtual void updateWallet(Wallet* wallet) override;
    virtual void deleteWallet(int walletId) override;
    virtual int getNextId() override;
};

#endif /* WALLETDBDAO_H_ */