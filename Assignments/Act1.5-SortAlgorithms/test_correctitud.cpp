// Diego Contreras
// A00845716

// Prueba interna: revisa que los 7 algoritmos ordenen bien en varios casos.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "sorting.h"
#include "data_generator.h"
#include "benchmark.h"
using namespace std;

// Compara el resultado del algoritmo contra el orden correcto.
template <typename T>
bool probar(int id, vector<T> v) {
    vector<T> esperado = v;
    sort(esperado.begin(), esperado.end()); // referencia, solo para el test
    aplicarOrden(id, v);
    return v == esperado;
}

template <typename T>
int correrCasos(const string& tipo, const vector<vector<T>>& casos) {
    int fallos = 0;
    for (int id = 1; id <= 7; id++) {
        for (size_t c = 0; c < casos.size(); c++) {
            if (!probar(id, casos[c])) {
                cout << "FALLO: " << nombreAlgoritmo(id) << " tipo " << tipo
                     << " caso " << c << "\n";
                fallos++;
            }
        }
    }
    return fallos;
}

int main() {
    int fallos = 0;

    // Casos: vacio, uno, repetidos, ordenado, inverso, mezclado, aleatorio.
    vector<vector<int>> casosInt = {
        {}, {5}, {3, 3, 3, 3}, {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1},
        {9, 1, 8, 2, 7, 3, 6, 4, 5, 0}, {2, 1}, generarEnteros(500)
    };
    fallos += correrCasos("int", casosInt);

    vector<vector<double>> casosDouble = {
        {}, {2.5}, {1.1, 1.1, 1.1}, {0.5, 1.5, 2.5}, {2.5, 1.5, 0.5},
        generarDoubles(500)
    };
    fallos += correrCasos("double", casosDouble);

    vector<vector<string>> casosStr = {
        {}, {"hola"}, {"b", "a", "c"}, {"casa", "arbol", "zorro", "arbol"},
        generarStrings(500)
    };
    fallos += correrCasos("string", casosStr);

    if (fallos == 0) {
        cout << "TODAS LAS PRUEBAS PASARON correctamente.\n";
    } else {
        cout << "HUBO " << fallos << " fallos.\n";
    }
    return fallos == 0 ? 0 : 1;
}
