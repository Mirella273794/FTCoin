#ifndef ABSTRACT_MOVEMENT_DAO_H
#define ABSTRACT_MOVEMENT_DAO_H

#include <vector>
#include "Movement.h"

class AbstractMovementDAO {
public:
    virtual ~AbstractMovementDAO() {}
    
    virtual void addMovement(const Movement& movement) = 0;
    virtual std::vector<Movement> getMovementsByWallet(int walletId) = 0;
    virtual Movement getMovementById(int movementId) = 0;
    virtual void deleteMovementsByWallet(int walletId) = 0;
    virtual int getNextMovementId() = 0;
};

#endif