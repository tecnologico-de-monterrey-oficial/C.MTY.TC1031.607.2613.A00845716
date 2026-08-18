#include <iostream>
using namespace std;

template <typename T>
T sum(T a, T b) {
    return a + b;
}

int main() {

    double a= 5.5;
    double b= 10.5;
    cout << "sum of" << a << "and" << b << "is:" << sum(a,b << endl)
    
    return 0;
}