#include <iostream>

class Date {
    friend std::ostream &operator<<(std::ostream &os, Date date);

    friend std::istream &operator>>(std::istream &is, Date &date);

public:
    enum MonthName {
        jan = 1, feb = 2, mar = 3, apr = 4, may = 5, jun = 6, jul = 7, aug = 8, sep = 9, oct = 10, nov = 11, dec = 12
    };

private:
    static const int defaultYear = 1985;
    static const int defaultMonth = Date::nov;
    static const int defaultDay = 4;

    int day;
    int month;
    int year;

    int dayInMonth();

public:
    Date();

    Date(const Date &other);

    Date(int year);

    Date(int year, int month);

    Date(int year, int month, int day);

    ~Date();

    void addYear(int n);

    void addMonth(int n);

    void addDay(int n);

    Date &operator=(const Date &other);

    bool operator==(Date &other);

    bool operator!=(Date &other);

    bool operator>(Date &other);

    bool operator<(Date &other);

    Date &operator++();

    Date &operator--();

    const Date operator++(int value);

    const Date operator--(int value);

    Date &operator+=(int n);

    Date &operator-=(int n);

    Date operator+(int n);

    Date operator-(int n);
};