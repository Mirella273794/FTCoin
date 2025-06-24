#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;
    
public:
    Date(int d = 1, int m = 1, int y = 2000);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);

    std::string toString() const;

    bool isValid() const;
};

#endif