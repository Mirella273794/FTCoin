#include "OracleService.hpp"
#include "FTCoinQuoteDAO.hpp"
#include "OracleDemo.hpp"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const string GREEN = "\033[32m";
const string RESET = "\033[0m";

void runOracleDemo(FTCoinQuoteDAO& dao) {
    OracleService oracle(dao);
    string date;

    cout << "Enter a date (format: YYYY-MM-DD) or type 'exit' to quit:" << endl;

    while (true) {
        cout << "> ";
        getline(cin, date);

        if (date == "exit") {
            cout << "Bye!" << endl;
            break;
        }

        try {
            double quote = oracle.getOrCreateQuote(date);

            cout << "Quote for " << date << ": "
                 << GREEN
                 << "R$ " << fixed << setprecision(2) << quote
                 << RESET
                 << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}