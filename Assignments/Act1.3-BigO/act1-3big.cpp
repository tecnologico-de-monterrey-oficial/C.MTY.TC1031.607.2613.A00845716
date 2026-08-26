// Actividad 1.3 - Big O
// Suma de los enteros impares contenidos en un vector de enteros positivos.

#include <iostream>
#include <vector>

using namespace std;

// Version iterativa
// Recorre una sola vez el vector, realizando trabajo constante por elemento.
// Complejidad: O(n)
int sumaImparesIterativa(const vector<int>& v) {
    int suma = 0;
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] % 2 != 0) {
            suma += v[i];
        }
    }
    return suma;
}

// Version recursiva
// Procesa un elemento por llamada y se llama a si misma n veces (una por indice).
// Complejidad: O(n)
int sumaImparesRecursiva(const vector<int>& v, int i) {
    if (i >= (int)v.size()) {
        return 0;
    }
    int actual = (v[i] % 2 != 0) ? v[i] : 0;
    return actual + sumaImparesRecursiva(v, i + 1);
}

int main() {
    vector<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Suma impares (iterativa): " << sumaImparesIterativa(numeros) << endl;
    cout << "Suma impares (recursiva): " << sumaImparesRecursiva(numeros, 0) << endl;

    return 0;
}
