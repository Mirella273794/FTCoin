#include "MovementMemDAO.h"

MovementMemDAO::MovementMemDAO() : lastMovementId(0) {}

void MovementMemDAO::addMovement(const Movement& movement) {
    movements[movement.getWalletId()].push_back(movement);
    if (movement.getMovementId() > lastMovementId) {
        lastMovementId = movement.getMovementId();
    }
}

std::vector<Movement> MovementMemDAO::getMovementsByWallet(int walletId) {
    if (movements.find(walletId) != movements.end()) {
        return movements[walletId];
    }
    return {};
}

Movement MovementMemDAO::getMovementById(int movementId) {
    for (auto& pair : movements) {
        for (auto& movement : pair.second) {
            if (movement.getMovementId() == movementId) {
                return movement;
            }
        }
    }
    return Movement(0, 0, Date(), ' ', 0);
}

void MovementMemDAO::deleteMovementsByWallet(int walletId) {
    movements.erase(walletId);
}

int MovementMemDAO::getNextMovementId() {
    return ++lastMovementId;
}