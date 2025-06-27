#ifndef FTCOINMEMORYDB_H_
#define FTCOINMEMORYDB_H_

#include <vector>
#include "Wallet.h"
#include "Movement.h"

using namespace std;

class FTCoinMemoryDB {
public:

vector<Wallet*> walletsDB;
    vector<Movement*> movementsDB;

    ~FTCoinMemoryDB() {
        for (Wallet* w : walletsDB) {
            delete w;
        }
        walletsDB.clear();

        for (Movement* m : movementsDB) {
            delete m;
        }
        movementsDB.clear();
    }
};

#endif /* FTCOINMEMORYDB_H_ */