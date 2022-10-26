//
// Created by over- on 13/10/2022.
//

#ifndef ASSIGNMENT_1_OOP_BIGDECIMALINT_H
#define ASSIGNMENT_1_OOP_BIGDECIMALINT_H

#include <bits/stdc++.h>
using namespace std;


class BigDecimalInt {
private:
    string bigInt;
    int sign;
public:
    BigDecimalInt();
    explicit BigDecimalInt (string decStr); // Initializes from string & rejects bad input
    explicit BigDecimalInt (int decInt); // Initialize from integer
    BigDecimalInt (const BigDecimalInt &anotherDes);
    BigDecimalInt operator+ (const BigDecimalInt &anotherDec) const; // member fn
    BigDecimalInt operator-(const BigDecimalInt &anotherDec) const; // member fn
    bool operator< (const BigDecimalInt &anotherDec) const; // member fn
    bool operator> (const BigDecimalInt &anotherDec) const; // member fn
    bool operator==(const BigDecimalInt &anotherDec) const; // member fn
    BigDecimalInt& operator= (const BigDecimalInt &anotherDec); // member fn
    int size() const; // member fn
    int getSign() const; // member fn
    friend ostream& operator << (ostream& out, const BigDecimalInt &b);
};


#endif //ASSIGNMENT_1_OOP_BIGDECIMALINT_H
