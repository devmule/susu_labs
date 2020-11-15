#include "Date.h"
#include <iostream>

static const int defaultYear = 1985;
static const int defaultMonth = Date::nov;
static const int defaultDay = 4;

int Date::dayInMonth() {
    int result;

    if (this->month == Date::feb)
        result = (this->year % 4) ? 28 : 29;
    else if (this->month == Date::apr || this->month == Date::jun ||
             this->month == Date::sep || this->month == Date::nov)
        result = 30;
    else result = 31;

    return result;
}

Date::Date() {
    this->day = Date::defaultDay;
    this->month = Date::defaultMonth;
    this->year = Date::defaultYear;
}

Date::Date(const Date &other) {
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
}

Date::Date(int year) {
    this->day = Date::defaultDay;
    this->month = Date::defaultMonth;
    this->year = year;
}

Date::Date(int year, int month) {
    this->day = Date::defaultDay;
    this->month = month;
    this->year = year;
}

Date::Date(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day - 1;
}

Date::~Date() = default;

void Date::addYear(int n) {
    this->year += n;
}

void Date::addMonth(int n) {
    int month = this->month + n;
    this->year += (month / 12);
    this->month = month % 12;
    if (month < 0) {
        this->month += 12;
        this->year--;
    }
}

void Date::addDay(int n) {
    if (n >= 0)
        while (n > 0) {
            if (n >= this->dayInMonth() - (this->day)) {
                n -= (this->dayInMonth() - (this->day));
                this->day = 0;
                this->addMonth(1);
            } else {
                (this->day) += n;
                n = 0;
            }
        }
    else
        while (n < 0) {

            if (n < -(this->day)) {
                n += this->day + 1;
                this->addMonth(-1);
                this->day = (this->dayInMonth() - 1);
            } else {
                this->day += n;
                n = 0;
            }
        }
}

Date &Date::operator=(const Date &other) {
    if (this == &other)return *this;
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    return *this;
}

bool Date::operator==(const Date &other) const {
    return (this->year == other.year &&
            this->month == other.month &&
            this->day == other.day);
}

bool Date::operator!=(const Date &other) const {
    return !(this->year == other.year &&
             this->month == other.month &&
             this->day == other.day);
}

bool Date::operator>(const Date &other) const {
    bool result;
    if (this->year != other.year) {
        result = this->year > other.year;
    } else {
        if (this->month != other.month) {
            result = this->month > other.month;
        } else {
            result = this->day > other.day;
        }
    }
    return result;
}

bool Date::operator<(const Date &other) const {
    bool result;
    if (this->year != other.year) {
        result = (this->year < other.year);
    } else {
        if (this->month != other.month) {
            result = (this->month < other.month);
        } else {
            result = (this->day < other.day);
        }
    }
    return result;
}

Date &Date::operator++() {
    this->addDay(1);
    return *this;
}

Date &Date::operator--() {
    this->addDay(-1);
    return *this;
}

Date Date::operator++(int value) {
    Date newDate(*this);
    this->addDay(1);
    return newDate;
}

Date Date::operator--(int value) {
    Date newDate(*this);
    this->addDay(-1);
    return newDate;
}

Date &Date::operator+=(int n) {
    this->addDay(n);
    return *this;
}

Date &Date::operator-=(int n) {
    this->addDay(-n);
    return *this;
}

Date Date::operator+(int n) {
    Date result(*this);
    result.addDay(n);
    return result;
}

Date Date::operator-(int n) {
    Date result(*this);
    result.addDay(-n);
    return result;
}

std::ostream &operator<<(std::ostream &os, Date date) {
    os << date.day + 1 << "." << date.month << "." << date.year;
    return os;
}

std::istream &operator>>(std::istream &is, Date &date) {
    return is;
}
