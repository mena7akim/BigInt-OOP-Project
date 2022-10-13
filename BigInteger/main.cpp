#include "BigDecimalInt.h"

int main()
{
    BigDecimalInt a("4960");
    BigDecimalInt b("90");
    BigDecimalInt c;
    c = a + b;
    cout << a + b << endl;
    cout << c << endl;
    cout << a - b << endl;
    cout << (a < b) << endl;
    cout << (a > b) << endl;
    cout << (a == b) << endl;
}