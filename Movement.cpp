#include "Movement.h"

Movement::Movement(int walletId, int movementId, const Date& date, char type, double amount)
    : walletId(walletId), movementId(movementId), date(date), type(type), amount(amount) {}

int Movement::getWalletId() const { return walletId; }
int Movement::getMovementId() const { return movementId; }
Date Movement::getDate() const { return date; }
char Movement::getType() const { return type; }
double Movement::getAmount() const { return amount; }

void Movement::setDate(const Date& date) { this->date = date; }
void Movement::setType(char type) { this->type = type; }
void Movement::setAmount(double amount) { this->amount = amount; }

bool Movement::isValid() const {
    return (type == 'C' || type == 'V') && amount >= 0 && walletId > 0 && movementId > 0;
}