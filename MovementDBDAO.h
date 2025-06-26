/* ********************************************************************************
 * FT_Coin - MovementDBDAO.h
 * Descrição: Declaração da implementação do DAO de Movement para MariaDB.
 ******************************************************************************** */

#ifndef MOVEMENTDBDAO_H_
#define MOVEMENTDBDAO_H_

#include "AbstractMovementDAO.h" // A interface que estamos implementando
#include "ServerDBConnection.h"
#include "Movement.h"

#include <string>
#include <vector>

using namespace std;

class MovementDBDAO final : public AbstractMovementDAO {
private:
    ServerDBConnection* dbConnection;

    // Declaração das strings SQL
    static const string SQL_addMovement;
    static const string SQL_getMovementsByWallet;
    static const string SQL_getMovementById;
    static const string SQL_deleteMovementsByWallet;
    static const string SQL_getNextId;

public:
    MovementDBDAO(ServerDBConnection* connection);
    virtual ~MovementDBDAO();

    // Implementação dos métodos da interface
    virtual void addMovement(const Movement& movement) override;
    virtual vector<Movement> getMovementsByWallet(int walletId) override;
    virtual Movement getMovementById(int movementId) override;
    virtual void deleteMovementsByWallet(int walletId) override;
    virtual int getNextMovementId() override;
};

#endif /* MOVEMENTDBDAO_H_ */