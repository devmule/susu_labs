#include "StringNumConverter.h"
#include <iostream>
#include <regex>

using namespace std;

void StringNumConverter::fixFormat() {

    // удалить всё кроме минуса, цифр и точки
    this->value = regex_replace(this->value, regex("[^-\\^0-9\\^.]"), "");

    // убрать нули в начале и в конце, если есть точка
    if (this->value.find('.') != string::npos) { // значит число флоатовое
        while (this->value.at(this->value.length() - 1) == '0') {
            this->value.erase(this->value.length() - 1, 1);
        }
    }

    int i = this->value[0] == '-' ? 1 : 0;
    while (this->value.length() >= 1 && this->value[i] == '0' && this->value[i + 1] == '0') {
        this->value.erase(i, 1);
    }
}

//конструкторы
StringNumConverter::StringNumConverter(const char *strVal) {
    this->value = strVal;
    this->fixFormat();
}

StringNumConverter::StringNumConverter(short val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(unsigned short val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(int val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(unsigned int val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(long val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(unsigned long val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(long long val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(unsigned long long val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(float val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(double val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(long double val) {
    this->value = std::to_string(val);
    this->fixFormat();
}

StringNumConverter::StringNumConverter(const StringNumConverter &other) {
    this->value = other.value;
    this->fixFormat();
}


StringNumConverter StringNumConverter::operator+(const std::string &strVal) const {
    return StringNumConverter((this->value + strVal).c_str());
}

StringNumConverter &StringNumConverter::operator=(const StringNumConverter &other) {
    if (&other == this) return *this; // Проверка на самоприсваивание
    this->value = other.value;
    this->fixFormat();
    return *this;
}


bool StringNumConverter::operator==(const StringNumConverter &other) const {
    return !(*this < other) && !(*this > other);
}

bool StringNumConverter::operator!=(const StringNumConverter &other) const {
    return !(*this == other);
}

bool StringNumConverter::operator<(const StringNumConverter &other) const {
    // проверка на знаки, если знаки разные, то результат очевиден
    if (this->value[0] == '-' && other.value[0] != '-') return true;
    if (this->value[0] != '-' && other.value[0] == '-') return false;

    // проверка на длину целой части, здесь знак одинаковый, результат зависит от знака
    if ((this->value.find('.') == string::npos ? this->value.length() : this->value.find('.')) <
        (other.value.find('.') == string::npos ? other.value.length() : other.value.find('.')))
        return other.value[0] != '-';
    if ((this->value.find('.') == string::npos ? this->value.length() : this->value.find('.')) >
        (other.value.find('.') == string::npos ? other.value.length() : other.value.find('.')))
        return other.value[0] == '-';

    //
    int i = other.value[0] == '-' ? 1 : 0, tv, ov;

    // проверка на значение до точки, здесь расстояние до точки одинаковое
    if (isdigit(this->value.at(i)) && isdigit(other.value.at(i))) {
        tv = (int) this->value.at(i), ov = (int) other.value.at(i);
        while (tv == ov) { // двигаемся вперёд
            i++; // если дошли до конца или до точки (до знака, которое не является числом) - завершаем
            if ((i >= other.value.length()) || !isdigit(this->value.at(i)) || !isdigit(other.value.at(i))) break;
            else {
                tv = (int) this->value.at(i);
                ov = (int) other.value.at(i);
            }
        }
        if (tv != ov) return tv < ov; // результат зависит от разницы величин
    }

    // проверка на значение после точки, длина не имеет значения, расстояние от начала до точки одинаковое
    i = this->value.find('.'), tv = 0, ov = 0;
    if (i != string::npos) {
        while (tv == ov && i < other.value.length() && i < this->value.length()) { // двигаемся вперёд
            i++; // если закончилась строка - заершаем
            if (i >= other.value.length() || i >= this->value.length()) {
                if (other.value.length() != this->value.length())
                    // если закончилась только одна строка - определяем какая длиннее
                    return other.value.length() > this->value.length();
                else break;
            } else {
                tv = (int) this->value.at(i);
                ov = (int) other.value.at(i);
            }
        }
        if (tv != ov) return tv < ov; // результат зависит от разницы величин
    }

    // числа равны
    return false;
}

bool StringNumConverter::operator>(const StringNumConverter &other) const {
    return other < *this;
}

bool StringNumConverter::operator<=(const StringNumConverter &other) const {
    return (*this < other) || (*this == other);
}

bool StringNumConverter::operator>=(const StringNumConverter &other) const {
    return (*this > other) || (*this == other);
}


StringNumConverter::operator int() const {
    return std::stoi(this->value);
}

StringNumConverter::operator short() const {
    return std::stoi(this->value);
}

StringNumConverter::operator unsigned short() const {
    return std::stoi(this->value);
}

StringNumConverter::operator unsigned int() const {
    return std::stoi(this->value);
}

StringNumConverter::operator long() const {
    return std::stol(this->value);
}

StringNumConverter::operator unsigned long() const {
    return std::stoul(this->value);
}

StringNumConverter::operator long long() const {
    return std::stoll(this->value);
}

StringNumConverter::operator unsigned long long() const {
    return std::stoull(this->value);
}

StringNumConverter::operator float() const {
    return std::stof(this->value);
}

StringNumConverter::operator double() const {
    return std::stod(this->value);
}

StringNumConverter::operator long double() const {
    return std::stold(this->value);
}

StringNumConverter::operator std::string() const {
    return this->value;
}


std::ostream &operator<<(std::ostream &out, const StringNumConverter &SNC) {
    out << SNC.value;
    return out;
}

std::istream &operator>>(std::istream &in, StringNumConverter &SNC) {
    in >> SNC.value;
    SNC.fixFormat();
    return in;
}
