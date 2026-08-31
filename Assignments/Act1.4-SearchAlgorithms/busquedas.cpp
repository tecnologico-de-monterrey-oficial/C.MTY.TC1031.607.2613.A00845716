// Diego Contreras
// A00845716
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Busqueda secuencial: recorre el vector elemento por elemento.
int busquedaSecuencial(const vector<int>& v, int objetivo) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == objetivo) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Busqueda binaria: requiere que el vector este ordenado.
int busquedaBinaria(const vector<int>& v, int objetivo) {
    int inicio = 0;
    int fin = static_cast<int>(v.size()) - 1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        if (v[medio] == objetivo) {
            return medio;
        } else if (v[medio] < objetivo) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return -1;
}

int main() {
    const int N = 10000;      
    const int MIN_VAL = 1;
    const int MAX_VAL = 1000000;

    // Semilla para numeros aleatorios.
    srand(static_cast<unsigned int>(time(nullptr)));

    // Se llena el vector con 10,000 numeros aleatorios entre 1 y 1,000,000.
    vector<int> numeros(N);
    for (int i = 0; i < N; i++) {
        numeros[i] = MIN_VAL + rand() % MAX_VAL; // valores en [1, 1000000]
    }

    // Se ordena el vector (necesario para la busqueda binaria).
    sort(numeros.begin(), numeros.end());

    cout << "Se generaron y ordenaron " << N
         << " numeros aleatorios entre " << MIN_VAL << " y " << MAX_VAL << ".\n";

    int objetivo;
    do {
        cout << "\nIngresa un numero entero entre 1 y 1,000,000 (0 para salir): ";
        cin >> objetivo;

        if (objetivo == 0) {
            cout << "Fin del programa.\n";
            break;
        }

        if (objetivo < MIN_VAL || objetivo > MAX_VAL) {
            cout << "El numero debe estar entre 1 y 1,000,000.\n";
            continue;
        }

        // Busqueda secuencial con medicion de tiempo 
        auto inicioSec = chrono::high_resolution_clock::now();
        int posSec = busquedaSecuencial(numeros, objetivo);
        auto finSec = chrono::high_resolution_clock::now();
        double tiempoSec =
            chrono::duration<double, micro>(finSec - inicioSec).count();

        // Busqueda binaria con medicion de tiempo 
        auto inicioBin = chrono::high_resolution_clock::now();
        int posBin = busquedaBinaria(numeros, objetivo);
        auto finBin = chrono::high_resolution_clock::now();
        double tiempoBin =
            chrono::duration<double, micro>(finBin - inicioBin).count();

        // Resultado (basta con una de las dos, deben coincidir).
        if (posSec != -1) {
            cout << "El numero " << objetivo << " SI se encuentra en la lista.\n";
        } else {
            cout << "El numero " << objetivo << " NO se encuentra en la lista.\n";
        }

        cout << "  Busqueda secuencial: " << tiempoSec << " microsegundos\n";
        cout << "  Busqueda binaria:    " << tiempoBin << " microsegundos\n";

    } while (objetivo != 0);

    return 0;
}
