#include "Date.h"
#include <iomanip>
#include <sstream>

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::setDay(int day) { this->day = day; }
void Date::setMonth(int month) { this->month = month; }
void Date::setYear(int year) { this->year = year; }

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << std::setfill('0') << std::setw(2) << date.day << "."
       << std::setw(2) << date.month << "." << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    char dot;
    is >> date.day >> dot >> date.month >> dot >> date.year;
    return is;
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    
    int daysInMonth;
    switch (month) {
        case 2:
            daysInMonth = (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) ? 29 : 28;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
    }
    
    return day >= 1 && day <= daysInMonth;
}