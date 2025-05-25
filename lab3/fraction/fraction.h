#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class fraction {
 private:
    int whole = 0;
    int numerator = 0;
    int denominator = 1;
    bool isNegative = false;

    void normalize();

 public:
    int GetWhole() const;
    int GetNumerator() const;
    int GetDenominator() const;
    bool GetIsNegative() const;
    int GetFullNumerator() const;

    fraction();
    fraction(int whole);
    fraction(double dou);
    fraction(int numerator, int denominator);
    fraction(int whole, int numerator, int denominator);
    fraction(const char* str);

    fraction& operator=(const fraction& other);
    fraction& operator+=(const fraction& other);
    fraction& operator-=(const fraction& other);
    fraction& operator*=(const fraction& other);
    fraction& operator/=(const fraction& other);

   friend fraction operator+(fraction a, const fraction& b);
   friend fraction operator-(fraction a, const fraction& b);
   friend fraction operator*(fraction a, const fraction& b);
   friend fraction operator/(fraction a, const fraction& b);
};

std::istream& operator>>(std::istream& in, fraction& obj);
std::ostream& operator<<(std::ostream& out, fraction& obj);

#endif
