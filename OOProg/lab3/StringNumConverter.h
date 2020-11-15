#include <iostream>
#include <string>

#pragma once
class StringNumConverter
{
private:
    std::string value;
    void fixFormat();

public:
    //конструкторы
    StringNumConverter(const StringNumConverter& value);//StringNumConverter
    StringNumConverter(const char *value);//str
    StringNumConverter(short value);//int+-
    StringNumConverter(unsigned short value);//int+
    StringNumConverter(int value);//int
    StringNumConverter(unsigned int value);//int+
    StringNumConverter(long value);//int +-
    StringNumConverter(unsigned long value);//int+
    StringNumConverter(long long value);//int+-
    StringNumConverter(unsigned long long value);//int-
    StringNumConverter(float value);//float+-
    StringNumConverter(double value);//float+-
    StringNumConverter(long double value);//float+-

    // операторы конкатенации и присваивания
    StringNumConverter operator+(const std:: string& str) const;
    StringNumConverter& operator=(const StringNumConverter& value);

    // операторы сравнения
    bool operator==(const StringNumConverter& value) const;
    bool operator!=(const StringNumConverter& value) const;
    bool operator<(const StringNumConverter& value) const;
    bool operator>(const StringNumConverter& value) const;
    bool operator<=(const StringNumConverter& value) const;
    bool operator>=(const StringNumConverter& value) const;

    //приведение типа
    explicit operator int() const;
    explicit operator short() const;
    explicit operator unsigned short() const;
    explicit operator unsigned int() const;
    explicit operator long() const;
    explicit operator unsigned long() const;
    explicit operator long long() const;
    explicit operator unsigned long long() const;
    explicit operator float() const;
    explicit operator double() const;
    explicit operator long double() const;
    explicit operator std::string() const;

    friend std::ostream& operator<<(std::ostream& out, const StringNumConverter& SNC);
    friend std::istream& operator>>(std::istream& in, StringNumConverter& SNC);
};


