#ifndef ORACLE_SERVICE_H
#define ORACLE_SERVICE_H

#include "FTCoinQuoteDAO.hpp"
#include <string>
#include <optional>
using namespace std;

class OracleService {
private:
    FTCoinQuoteDAO& dao;

    double generateRandomQuote();

    double generateSmartQuote(const string& date);

public:
    OracleService(FTCoinQuoteDAO& dao);
    double getOrCreateQuote(const string& date);
};

#endif