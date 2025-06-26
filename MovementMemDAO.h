#ifndef MOVEMENT_MEM_DAO_H
#define MOVEMENT_MEM_DAO_H

#include "AbstractMovementDAO.h"
#include <vector>
#include <map>

class MovementMemDAO : public AbstractMovementDAO {
private:
    std::map<int, std::vector<Movement>> movements;
    int lastMovementId;
    
public:
    MovementMemDAO();
    
    void addMovement(const Movement& movement) override;
    std::vector<Movement> getMovementsByWallet(int walletId) override;
    Movement getMovementById(int movementId) override;
    void deleteMovementsByWallet(int walletId) override;
    int getNextMovementId() override;
};

#endif