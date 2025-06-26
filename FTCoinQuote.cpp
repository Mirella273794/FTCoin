#include "FTCoinQuote.hpp"

FTCoinQuote::FTCoinQuote(const std::string& date, double value)
    : date(date), value(value) {}

std::string FTCoinQuote::getDate() const {
    return date;
}

double FTCoinQuote::getValue() const {
    return value;
}

void FTCoinQuote::setDate(const std::string& newDate) {
    date = newDate;
}

void FTCoinQuote::setValue(double newValue) {
    value = newValue;
}

