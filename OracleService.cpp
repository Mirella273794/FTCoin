#include "OracleService.hpp"
#include <random>
#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

OracleService::OracleService(FTCoinQuoteDAO& dao) : dao(dao) {}

double OracleService::generateRandomQuote() {
    static mt19937 rng(random_device{}());
    uniform_real_distribution<double> dist(2.0, 6.0);
    return dist(rng);
}

double OracleService::generateSmartQuote(const string& date) {
    auto prevQuote = dao.getPreviousQuote(date);
    auto nextQuote = dao.getNextQuote(date);

    if (prevQuote || nextQuote) {
        double baseValue = 0.0;
        int count = 0;

        if (prevQuote) { baseValue += *prevQuote; count++; }
        if (nextQuote) { baseValue += *nextQuote; count++; }

        baseValue /= count;

        static mt19937 rng(random_device{}());
        uniform_real_distribution<double> noiseDist(-0.05, 0.05);
        double noise = noiseDist(rng);
        
        return baseValue * (1.0 + noise);
    }
    return generateRandomQuote();
}

double OracleService::getOrCreateQuote(const string& date) {
        if (date.empty()) {
        throw invalid_argument("Date cannot be empty");
    }

    try {
        if (dao.checkExistence(date)) {
            return dao.getQuoteByDate(date);
        } else {
            double quote = generateSmartQuote(date);
            dao.saveQuote(date, quote);
            return quote;
        }
    } catch (const exception& e) {
        cerr << "Failed to get/create quote: " << e.what() << endl;
        throw;
    }
}
