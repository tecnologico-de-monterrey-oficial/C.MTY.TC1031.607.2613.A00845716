// Diego Contreras
// A00845716

#include <iostream>
#include <string>

using namespace std;




int sumIterative(int n) {
    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i;
    }
    return suma;
}

int  sumRecursive (int n) {
    if (n == 0) {
        return 0;
    }
    return n + sumRecursive(n - 1);
}

int sumFormula(int n) {
    return n * (n + 1) / 2;
}

int fibonacciIterative (int n){
    if (n<= 2) {
        return 1;
    }
    int a = 1;
    int b = 1;
    int fib = 0;
    for (int i = 3; i <= n; i++) {
        fib = a + b;
        a = b;
        b = fib;
    }
    return fib;
}

double bacteriaIterativa (int n) {
    double born = 3.78;
    double died = 2.34;
    double bac = 1;
    for (int i= 1; i <=n; i++) {
        bac = bac + bac * born - bac * died;
    }
    return bac;
}

double bacteriaRecursive (int n) {
    if (n ==0) {
        return 1;
    }
    return bacteriaRecursive (n-1) + bacteriaRecursive (n-1) *3.78 - bacteriaRecursive (n-1) * 2.34;
}



int main() {
    cout << "La suma de los primeros 6 numeros es : " << sumIterative(6) << endl;
    // suma iterativa
    cout << "La suma iterativa de los primeros 6 numeros es : " << sumRecursive(6) << endl;
    // suma recursiva
    cout << "La suma con formula de los primeros 6 numeros es : " << sumFormula(6) << endl;
    // suma formula
    cout << "El fibonacci del numero 6 es : " << fibonacciIterative(6) << endl;
    // fibonacci iterativo, imprime el 6to numero de la serie (8)
    cout << "Las bacterias despues de 6 dias (iterativo) son : " << bacteriaIterativa(6) << endl;
    // bacterias iterativas, imprime el total despues de 6 dias
    cout << "Las bacterias despues de 6 dias (recursivo) son : " << bacteriaRecursive(6) << endl;
    // bacterias recursivas, imprime el mismo total pero calculado con recursion

}
