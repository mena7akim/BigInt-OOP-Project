#include "BigDecimalInt.h"
using namespace std;

BigDecimalInt::BigDecimalInt(): bigInt("0"), sign(1){}

BigDecimalInt::BigDecimalInt(string decStr) {
    // reject bad inputs
    regex valid ("[-+]?[0-9]+");
    if(!regex_match(decStr,valid)){
        throw invalid_argument("grb '3rha\n");
    }

    // extract sign
    if(decStr[0] == '-') decStr.erase(decStr.begin()), sign = 0;
    else{
        if(decStr[0] == '+') decStr.erase(decStr.begin());
        sign = 1;
    }

    // removing zeros to the left
    string temp = "";
    bool foundDigit = 0;
    for(int i = 0; i < decStr.size(); i++){
        if(decStr[i] != '0') foundDigit = 1;
        if(foundDigit) temp += decStr[i];
    }
    bigInt = temp;
}

BigDecimalInt::BigDecimalInt(int decInt) {
    sign = (decInt >= 0); // extract sign if (decInt >= 0) sign = 1 , else sign = 0
    decInt = abs(decInt); // remove the sign in case if decInt was less than zero
    bigInt = to_string(decInt); // convert the number to string
}

BigDecimalInt::BigDecimalInt(const BigDecimalInt &anotherDec) : bigInt(anotherDec.bigInt), sign(anotherDec.sign) {}

BigDecimalInt BigDecimalInt::operator+(const BigDecimalInt &anotherDec) const{
    if(sign != anotherDec.sign){ // if signs was not the same (-x + y = y - x) , (x + -y = x - y)
        BigDecimalInt left = *this, right = anotherDec;
        if(sign) {
            right.sign = 1;
            return left - right;
        }
        left.sign = 1;
        return right - left;
    }
    int carry = 0;
    string result = "", firstNumber = bigInt, secondNumber = anotherDec.bigInt;

    // make the two string the same size
    if(firstNumber.size() > secondNumber.size()){
        secondNumber = string(firstNumber.size() - secondNumber.size(),'0') + secondNumber;
    }
    else if(firstNumber.size() < secondNumber.size()){
        firstNumber = string(secondNumber.size() - firstNumber.size(), '0') + firstNumber;
    }
    for(int i = firstNumber.size() - 1; i >= 0; i--){
        int x = (firstNumber[i] - '0') + (secondNumber[i] - '0') + carry;
        carry = (x > 9);
        result += char(x % 10 + '0');
    }
    if(carry) result += '1'; // after the addition if there was a carry add it
    reverse(result.begin(), result.end());
    BigDecimalInt ret(result);
    ret.sign = sign; // if the two signs was equal the sign of the answer would be the same as the two number (x + y = z) , (-x + -y) = -(x + y) = z

    return ret;
}

BigDecimalInt BigDecimalInt::operator-(const BigDecimalInt &anotherDec) const{
    BigDecimalInt left = *this, right = anotherDec;
    if(sign != anotherDec.sign){ // if(signs was not the same we can use + operator exp: ( (+x) - (-y) = x + y ), ( (-x) - (+y) = (-x) - y = -(x + y) )
        if(sign){
            right.sign = 1;
            return left + right;
        }
        right.sign = 0;
        return left + right;
    }
    BigDecimalInt ret;
    left.sign = 1;
    right.sign = 1;
    if(*this == anotherDec) return ret;
    ret.sign = this->sign;
    if(left < right) {
        BigDecimalInt temp;
        temp = left;
        left = right;
        right = temp;
        ret.sign = !ret.sign;
    }

    if(left.size() != right.size()) right.bigInt = string(left.size() - right.size(), '0') + right.bigInt; // make the two string the same size
    ret.bigInt = string(left.size(), '0');
    for(int i = left.bigInt.size() - 1; i >= 0; i--){
        if(left.bigInt[i] < right.bigInt[i]){
            left.bigInt[i - 1] -= 1;
            left.bigInt[i] += 10;
        }
        ret.bigInt[i] = ((left.bigInt[i] - '0') - (right.bigInt[i] - '0')) + '0';
    }

    // removing the zeros in the left of the number
    string temp = "";
    bool foundDigit = 0;
    for(int i = 0; i < ret.bigInt.size(); i++){
        if(ret.bigInt[i] != '0') foundDigit = 1;
        if(foundDigit) temp += ret.bigInt[i];
    }
    ret.bigInt = temp;

    return ret;
}

bool BigDecimalInt::operator<(const BigDecimalInt &anotherDec) const {
    if(sign != anotherDec.sign){
        return sign < anotherDec.sign;
    }
    if(bigInt.size() != anotherDec.bigInt.size()){
        if(sign) return bigInt.size() < anotherDec.bigInt.size();
        else return anotherDec.bigInt.size() < bigInt.size();
    }
    for(int i = 0; i < bigInt.size(); i++){
        if(bigInt[i] != anotherDec.bigInt[i]){
            if(sign) return bigInt[i] < anotherDec.bigInt[i];
            return anotherDec.bigInt[i] < bigInt[i];
        }
    }
}

bool BigDecimalInt::operator>(const BigDecimalInt &anotherDec) const {
    return anotherDec < *this;
}

bool BigDecimalInt::operator==(const BigDecimalInt &anotherDec) const {
    if(!(*this < anotherDec) && !(anotherDec < *this)){
        return true;
    }
    return false;
}

BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt &anotherDec) {
    BigDecimalInt ret;
    bigInt = anotherDec.bigInt;
    sign = anotherDec.sign;
    return *this;
}

int BigDecimalInt::size() const {
    return bigInt.size();
}

int BigDecimalInt::getSign() const{
    return sign;
}

ostream& operator << (ostream& out,const BigDecimalInt &b) {
    if(!b.sign){
        out << '-';
    }
    out << b.bigInt;
    return out;
}

