#include <iomanip>
#include <ctime>

#include "Date.h"

using namespace std;

Date::Date()
	{
	time_t now = time(NULL);
	tm *currentTime = localtime(&now);
	day = currentTime->tm_mday;
	month = currentTime->tm_mon;
	year = currentTime->tm_year;
	}

Date::Date(string isoFormat)
	{
	day = stoi(isoFormat.substr(8, 10));
	month = stoi(isoFormat.substr(5, 7));
	year = stoi(isoFormat.substr(0, 4));
	}

Date::Date(int day, int month, int year) :
		day(day), month(month), year(year)
	{
	}

Date::~Date()
	{
	}

int Date::getYear()
	{
	return year;
	}

int Date::getMonth()
	{
	return month;
	}

int Date::getDay()
	{
	return day;
	}

string Date::getIsoFormat()
	{
	return (to_string(year) + "-" + to_string(month) + "-" + to_string(day));
	}

bool Date::operator==(const Date &other) const
	{
	return year == other.year && month == other.month && day == other.day;
	}

bool Date::operator!=(const Date &other) const
	{
	return !(*this == other);
	}

bool Date::operator>(const Date &other) const
	{
	if (year != other.year)
		return year > other.year;
	if (month != other.month)
		return month > other.month;
	return day > other.day;
	}

bool Date::operator>=(const Date &other) const
	{
	return (*this == other) || (*this > other);
	}

bool Date::operator<(const Date &other) const
	{
	return !(*this >= other);
	}

bool Date::operator<=(const Date &other) const
	{
	return !(*this > other);
	}

ostream& operator<<(ostream &os, const Date &date)
	{
	os << setfill('0') << setw(4) << date.year << ".";
	os << setfill('0') << setw(2) << date.month << ".";
	os << setfill('0') << setw(2) << date.day;
	return os;
	}

istream& operator>>(std::istream &is, Date &date)
	{
	char separator;
	is >> date.day >> separator >> date.month >> separator >> date.year;
	return is;
	}