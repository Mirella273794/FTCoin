/* ********************************************************************************
 * FT_Coin - WalletDBDAO.cpp
 * Lógica de acesso ao banco de dados para a entidade Wallet.
 ******************************************************************************** */

#include "WalletDBDAO.h"
#include "Wallet.h"
#include <memory>
#include <iostream>

using namespace std;

const string WalletDBDAO::SQL_addWallet = "INSERT INTO CARTEIRA (Titular, Corretora) VALUES (?, ?)";
const string WalletDBDAO::SQL_getAllWallets = "SELECT IdCarteira, Titular, Corretora FROM CARTEIRA ORDER BY IdCarteira";
const string WalletDBDAO::SQL_getWalletById = "SELECT IdCarteira, Titular, Corretora FROM CARTEIRA WHERE IdCarteira = ?";
const string WalletDBDAO::SQL_updateWallet = "UPDATE CARTEIRA SET Titular = ?, Corretora = ? WHERE IdCarteira = ?";
const string WalletDBDAO::SQL_deleteWallet = "DELETE FROM CARTEIRA WHERE IdCarteira = ?";
const string WalletDBDAO::SQL_getNextId = "SELECT AUTO_INCREMENT FROM information_schema.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = 'CARTEIRA'";

WalletDBDAO::WalletDBDAO(ServerDBConnection* connection) : dbConnection(connection) {}
WalletDBDAO::~WalletDBDAO() {}

int WalletDBDAO::getNextId() {
    int nextId = 0;
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_getNextId));
        stmnt->setString(1, "PooI_25_B05");
        unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
        if (res->next()) {
            nextId = res->getInt(1);
        }
    } catch (sql::SQLException &e) {
        cerr << "Erro ao buscar o próximo ID de Wallet: " << e.what() << endl;
    }
    return nextId;
}

void WalletDBDAO::addWallet(Wallet* wallet) {
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_addWallet));
        stmnt->setString(1, wallet->getOwner());
        stmnt->setString(2, wallet->getBroker());
        stmnt->executeUpdate();
    } catch (sql::SQLException &e) {
        cerr << "Erro ao adicionar Wallet: " << e.what() << endl;
    }
}

void WalletDBDAO::updateWallet(Wallet* wallet) {
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_updateWallet));
        stmnt->setString(1, wallet->getOwner());
        stmnt->setString(2, wallet->getBroker());
        stmnt->setInt(3, wallet->getId());
        stmnt->executeUpdate();
    } catch (sql::SQLException &e) {
        cerr << "Erro ao atualizar Wallet: " << e.what() << endl;
    }
}

void WalletDBDAO::deleteWallet(int walletId) {
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_deleteWallet));
        stmnt->setInt(1, walletId);
        stmnt->executeUpdate();
    } catch (sql::SQLException &e) {
        cerr << "Erro ao deletar Wallet: " << e.what() << endl;
    }
}

Wallet* WalletDBDAO::getWalletById(int walletId) {
    Wallet* wallet = nullptr;
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_getWalletById));
        stmnt->setInt(1, walletId);
        unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
        if (res->next()) {
            wallet = new Wallet(
                res->getInt("IdCarteira"),
                string(res->getString("Titular")),
                string(res->getString("Corretora"))
            );
        }
    } catch (sql::SQLException &e) {
        cerr << "Erro ao buscar Wallet por ID: " << e.what() << endl;
    }
    return wallet;
}

vector<Wallet*> WalletDBDAO::getAllWallets() {
    vector<Wallet*> wallets;
    try {
        unique_ptr<sql::Statement> stmnt(dbConnection->getConnection()->createStatement());
        unique_ptr<sql::ResultSet> res(stmnt->executeQuery(SQL_getAllWallets));
        while (res->next()) {
            wallets.push_back(new Wallet(
                res->getInt("IdCarteira"),
                string(res->getString("Titular")),
                string(res->getString("Corretora"))
            ));
        }
    } catch (sql::SQLException &e) {
        cerr << "Erro ao listar todas as Wallets: " << e.what() << endl;
    }
    return wallets;
}