#ifndef FTCOINMEMORYDB_H_
#define FTCOINMEMORYDB_H_

#include <vector>
#include "Wallet.h"
#include "Movement.h"
// Futuramente: #include "FTCoinQuote.h"

using namespace std;

class FTCoinMemoryDB {
public:
    // "Tabelas" em memória que guardam os ponteiros para os objetos
    vector<Wallet*> walletsDB;
    vector<Movement*> movementsDB;
    // vector<FTCoinQuote*> quotesDB;

    // O destrutor será responsável por limpar toda a memória
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