#include "fraction.h"

#include <iostream>
#include <cmath>
#include <cstring>

namespace {
    const int precision = 1e4;
    const char digits[] = "0123456789";
    const char kbufferLength = 64;
}

int fraction::GetWhole() const {
    return whole;
}

int fraction::GetNumerator() const {
    return numerator;
}

int fraction::GetDenominator() const {
    return denominator;
}

bool fraction::GetIsNegative() const {
    return isNegative;
}

int fraction::GetFullNumerator() const {
    return whole * denominator + numerator;
}

void fraction::normalize() {
    if (denominator != 0) {
        int newNumerator = GetFullNumerator();
        if (denominator < 0) {
            denominator *= -1;
            newNumerator *= -1;
        }
        if (newNumerator < 0) {
            newNumerator *= -1;
            isNegative = !isNegative;
        }
        whole = newNumerator / denominator;
        numerator = newNumerator - whole * denominator;

        if (numerator / denominator != 1 && numerator != 0) {
            for (int i = numerator; i >= 2; --i) {
                if (numerator % i == 0 && denominator % i == 0) {
                    numerator /= i;
                    denominator /= i;
                    break;
                }
            }
        }
    } else {
        std::cout << "Деление на 0, замена на стандартную дробь 0 0/1\n";
        numerator = 0;
        denominator = 1;
        whole = 0;
    }
}

fraction::fraction(): whole(0), numerator(0), denominator(1), isNegative(false) {}



fraction::fraction(int whole): whole(whole), numerator(0), denominator(1), isNegative(false) {}

fraction::fraction(double du) {
    if (du < 0) {
        isNegative = true;
        du *=-1;
    }
    double Whole {};
    double notWhole {};

    notWhole = modf(du, &Whole);
    whole = static_cast<int>(Whole);

    if (notWhole != 0) {
        numerator = round(notWhole * precision);
        denominator = precision;
        normalize();
    }
}

fraction::fraction(int numerator, int denominator): whole(), numerator(numerator), denominator(denominator), isNegative() {
    normalize();
}

fraction::fraction(int whole, int numerator, int denominator): whole(whole), numerator(numerator), denominator(denominator), isNegative() {
    normalize();
}

fraction::fraction(const char* str) {

    int firstIndex = 0;
    if (str[0] == '-') {
        isNegative = true;
        ++firstIndex;
    }

    int fractionVars [3] {};
    int amountOfReadVarible = 0;
    bool isItBeginOfVarible = true;

    for (int i = firstIndex; str[i] != '\0'; ++i) {
        if (std::strchr(digits, str[i]) && amountOfReadVarible < 3) {
            if (isItBeginOfVarible) {
                ++amountOfReadVarible;
            }

            fractionVars[amountOfReadVarible - 1] *= 10;
            fractionVars[amountOfReadVarible - 1] += str[i] - '0';

            isItBeginOfVarible = false;
        } else {
            isItBeginOfVarible = true;
        }
    }

    if (amountOfReadVarible > 3 || amountOfReadVarible == 0) {
        std::cout << "Неправильно введенная строка. Максимальное количество переменных: 3\n";
        std::cout << "Замена на стандартную дробь 0 0/1\n";
        numerator = 0;
        denominator = 1;
        whole = 0;
    }

    if (amountOfReadVarible == 1) {
        whole = fractionVars[0];
    } else if (amountOfReadVarible == 2) {
        numerator = fractionVars[0];
        denominator = fractionVars[1];
        normalize();
    } else if (amountOfReadVarible == 3) {
        whole = fractionVars[0];
        numerator = fractionVars[1];
        denominator = fractionVars[2];
        normalize();
    }
}

fraction& fraction::operator=(const fraction& other) {
    if (this == &other) {
        return *this;
    }
    isNegative = other.isNegative;
    whole = other.whole;
    numerator = other.numerator;
    denominator = other.denominator;

    return *this;
}

fraction& fraction::operator+=(const fraction& other) {
    if (denominator == other.denominator) {
        if (isNegative == other.isNegative) {
            whole += other.whole;
            numerator += other.numerator;
        } else {
            whole -= other.whole;
            numerator -= other.numerator;
        }
    } else {
        if (isNegative == other.isNegative) {
            numerator = GetFullNumerator() * other.denominator + other.GetFullNumerator() * denominator;
            whole = 0;
            denominator *= other.denominator;

        } else {
            numerator = GetFullNumerator() * other.denominator - other.GetFullNumerator() * denominator;
            whole = 0;
            denominator *= other.denominator;
        }
    }

    normalize();

    return *this;
}

fraction operator+(fraction a, const fraction& b) {
    a += b;
    return a;
}

fraction& fraction::operator-=(const fraction& other) {
    if (denominator == other.denominator) {
        if (isNegative != other.isNegative) {
            whole += other.whole;
            numerator += other.numerator;
        } else {
            whole -= other.whole;
            numerator -= other.numerator;
        }
    } else {
        if (isNegative != other.isNegative) {
            numerator = GetFullNumerator() * other.denominator + other.GetFullNumerator() * denominator;
            whole = 0;
            denominator *= other.denominator;
        } else {
            numerator = GetFullNumerator() * other.denominator - other.GetFullNumerator() * denominator;
            whole = 0;
            denominator *= other.denominator;
        }
    }

    normalize();

    return *this;
}

fraction operator-(fraction a, const fraction& b) {
    a -= b;
    return a;
}

fraction& fraction::operator*=(const fraction& other) {
    if (isNegative == other.isNegative) {
        isNegative = false;
    } else {
        isNegative = true;
    }

    numerator = GetFullNumerator() * other.GetFullNumerator();
    denominator *= other.denominator;
    whole = 0;

    normalize();

    return *this;
}

fraction operator*(fraction a, const fraction& b) {
    a *= b;
    return a;
}

fraction& fraction::operator/=(const fraction& other) {
    if (other.GetFullNumerator() == 0) {
        std::cout << "Деление на 0, операция отменяется\n";
        return *this;
    }

    if (isNegative == other.isNegative) {
        isNegative = false;
    } else {
        isNegative = true;
    }

    numerator = GetFullNumerator() * other.denominator;
    denominator *= other.GetFullNumerator();
    whole = 0;

    normalize();

    return *this;
}

fraction operator/(fraction a, const fraction& b) {
    a /= b;
    return a;
}

std::istream& operator>>(std::istream& in, fraction& obj) {
    char buffer[kbufferLength] {};
    in.getline(buffer, kbufferLength);
    fraction frFromStream(buffer);
    obj = frFromStream;

    return in;
}

std::ostream& operator<<(std::ostream& out, fraction& obj) {
    if (obj.GetIsNegative()) {
        out << '-';
    }

    if (obj.GetWhole()!=0 || obj.GetNumerator()==0){
        out << obj.GetWhole();
    }

    if (obj.GetNumerator()) {
        out << ' ' << obj.GetNumerator() << '/' << obj.GetDenominator();
    }


    return out;
}
