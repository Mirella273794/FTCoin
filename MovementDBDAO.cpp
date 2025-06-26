/* ********************************************************************************
 * FT_Coin - MovementDBDAO.cpp
 * Lógica de acesso ao banco de dados para a entidade Movement.
 ******************************************************************************** */

#include "MovementDBDAO.h"
#include <memory>
#include <iostream>

using namespace std;

const string MovementDBDAO::SQL_addMovement = "INSERT INTO MOVIMENTACAO (IdMovimento, IdCarteira, Data, TipoOperacao, Quantidade) VALUES (?, ?, ?, ?, ?)";
const string MovementDBDAO::SQL_getMovementsByWallet = "SELECT IdMovimento, IdCarteira, Data, TipoOperacao, Quantidade FROM MOVIMENTACAO WHERE IdCarteira = ? ORDER BY Data";
const string MovementDBDAO::SQL_getMovementById = "SELECT IdMovimento, IdCarteira, Data, TipoOperacao, Quantidade FROM MOVIMENTACAO WHERE IdMovimento = ?";
const string MovementDBDAO::SQL_deleteMovementsByWallet = "DELETE FROM MOVIMENTACAO WHERE IdCarteira = ?";
const string MovementDBDAO::SQL_getNextId = "SELECT AUTO_INCREMENT FROM information_schema.TABLES WHERE TABLE_SCHEMA = ? AND TABLE_NAME = 'MOVIMENTACAO'";

MovementDBDAO::MovementDBDAO(ServerDBConnection* connection) : dbConnection(connection) {}
MovementDBDAO::~MovementDBDAO() {}

void MovementDBDAO::addMovement(const Movement& movement) {
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_addMovement));
        stmnt->setInt(1, movement.getMovementId());
        stmnt->setInt(2, movement.getWalletId());
        stmnt->setString(3, movement.getDate().getIsoFormat());
        stmnt->setString(4, string(1, movement.getType()));
        stmnt->setDouble(5, movement.getAmount());
        stmnt->executeUpdate();
    } catch (sql::SQLException &e) {
        cerr << "Erro ao adicionar Movement: " << e.what() << endl;
    }
}

vector<Movement> MovementDBDAO::getMovementsByWallet(int walletId) {
    vector<Movement> movements;
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_getMovementsByWallet));
        stmnt->setInt(1, walletId);
        unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
        while (res->next()) {
            movements.push_back(Movement(
                res->getInt("IdMovimento"),
                res->getInt("IdCarteira"),
                Date(string(res->getString("Data"))),
                res->getString("TipoOperacao")[0],
                res->getDouble("Quantidade")
            ));
        }
    } catch (sql::SQLException &e) {
        cerr << "Erro ao buscar Movements por Wallet ID: " << e.what() << endl;
    }
    return movements;
}

Movement MovementDBDAO::getMovementById(int movementId) {
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_getMovementById));
        stmnt->setInt(1, movementId);
        unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
        if (res->next()) {
            return Movement(
                res->getInt("IdMovimento"),
                res->getInt("IdCarteira"),
                Date(string(res->getString("Data"))),
                res->getString("TipoOperacao")[0],
                res->getDouble("Quantidade")
            );
        }
    } catch (sql::SQLException &e) {
        cerr << "Erro ao buscar Movement por ID: " << e.what() << endl;
    }
    return Movement(0, 0, Date(), ' ', 0.0);
}

void MovementDBDAO::deleteMovementsByWallet(int walletId) {
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_deleteMovementsByWallet));
        stmnt->setInt(1, walletId);
        stmnt->executeUpdate();
    } catch (sql::SQLException &e) {
        cerr << "Erro ao deletar Movements por Wallet ID: " << e.what() << endl;
    }
}

int MovementDBDAO::getNextMovementId() {
    int nextId = 0;
    try {
        unique_ptr<sql::PreparedStatement> stmnt(dbConnection->getConnection()->prepareStatement(SQL_getNextId));
        stmnt->setString(1, "PooI_25_B05");
        unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
        if (res->next()) {
            nextId = res->getInt(1);
        }
    } catch (sql::SQLException &e) {
        cerr << "Erro ao buscar o próximo ID de Movement: " << e.what() << endl;
    }
    return nextId;
}