#include <sstream>
#include <time.h>
#include "Date.h"

// Seconds in a given month. Non-leap year
int secondsPerMonth[12] = {
	3600 * 24 * 31, // january
	3600 * 24 * 28, // february
	3600 * 24 * 31,
	3600 * 24 * 30,
	3600 * 24 * 31,
	3600 * 24 * 30,
	3600 * 24 * 31,	// July
	3600 * 24 * 31, // August
	3600 * 24 * 30,
	3600 * 24 * 31,
	3600 * 24 * 30,
	3600 * 24 * 31	// December
};


// Default Constructor -- Initializes a Date object to the current date
Date::Date() {
	time_t current;
	time(&current);

	// Number of seconds in one astronomical year (365.25 days): 31557600
	year = 1970 + (unsigned int) current / 31557600;

	month = 1;
	int s = current % 31557600; // s -> number of seconds in the current year
	for (int i = 0; (s - secondsPerMonth[i]) > 0 && i < 12; s -= secondsPerMonth[i], i++)
		month++;
	// s -> number of seconds in the current month

	day = 1 + (s - (11 * 3600)) / (3600 * 24);

	//int hours = ((s - (11 * 3600)) % (3600 * 24)) / 3600;
	//int minutes = ((s % (3600 * 24)) % 3600) / 60;
}

Date::Date(string data) {
	stringstream str_in; char tmp;
	str_in.str(data);
	str_in >> this->day >> tmp >> this->month >> tmp >> this->year;
}

Date::Date(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

int Date::get_day() const {
	return day;
}

int Date::get_month() const {
	return month;
}

int Date::get_year() const {
	return year;
}

bool operator<=(const Date& d1, const Date& d2)
{
	if (d1.year < d2.year)
		return true;
	else if (d1.year == d2.year)
	{
		if (d1.month < d2.month)
			return true;
		else if (d1.month == d2.month)
			return d1.day <= d2.day;
		else
			return false;
	}
	else
		return false;
}

bool operator<(const Date& d1, const Date& d2)
{
	if (d1.year < d2.year)
		return true;
	else if (d1.year == d2.year)
	{
		if (d1.month < d2.month)
			return true;
		else if (d1.month == d2.month)
			return d1.day < d2.day;
		else
			return false;
	}
	else
		return false;
}

bool operator==(const Date & d1, const Date & d2)
{
	return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

bool operator!=(const Date& d1, const Date& d2) {
	return ! (d1 == d2);
}


ostream& operator<<(ostream& out, const Date & date) {
	out << (date.day < 10 ? "0" : "") << date.day << '/'
		<< (date.month < 10 ? "0" : "") << date.month << '/' << date.year;
	return out;
}

istream& operator>>(istream& in, Date& date) {
	char c;
	in >> date.day >> c >> date.month >> c >> date.year;

	return in;
}

// Helper for algorithm to find difference in days between two dates
int rdn(const Date & d1) {
	int d = d1.get_day(), m = d1.get_month(), y = d1.get_year();
	if (m < 3)
		y--, m += 12;
	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

int dateDifference(const Date & d1, const Date & d2) {
	return rdn(d2) - rdn(d1);
}