#ifndef FTCOINQUOTEDAO_H
#define FTCOINQUOTEDAO_H

#include <string>
#include <stdexcept>
#include <mariadb/conncpp.hpp>
using namespace std;

class FTCoinQuoteDAO {
public:
    FTCoinQuoteDAO(const string& host, const string& port, 
                   const string& user, const string& password, 
                   const string& database);
    ~FTCoinQuoteDAO();

    bool checkExistence(const string& date);
    void saveQuote(const string& date, double quote);
    double getQuoteByDate(const string& date);
    optional<double> getPreviousQuote(const string& date);
    optional<double> getNextQuote(const string& date);

private:
    sql::Driver* driver;
    unique_ptr<sql::Connection> conn;
};

#endif // FTCOINQUOTEDAO_H