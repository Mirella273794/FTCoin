#ifndef FTCOIN_QUOTE_H
#define FTCOIN_QUOTE_H

#include <string>
using namespace std;

class FTCoinQuote {
private:
    string date;
    double value;

public:
    FTCoinQuote(const string& date, double value);

    string getDate() const;
    double getValue() const;

    void setDate(const string& newDate);
    void setValue(double newValue);
};

#endif // FTCOIN_QUOTE_H
