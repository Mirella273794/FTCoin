#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Date.h"
#include <string>

class Movement {
private:
    int walletId;
    int movementId;
    Date date;
    char type;
    double amount;

public:
    Movement(int walletId, int movementId, const Date& date, char type, double amount);

    int getWalletId() const;
    int getMovementId() const;
    Date getDate() const;
    char getType() const;
    double getAmount() const;

    void setDate(const Date& date);
    void setType(char type);
    void setAmount(double amount);

    bool isValid() const;
};

#endif