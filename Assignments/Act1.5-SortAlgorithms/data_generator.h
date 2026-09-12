// Diego Contreras
// A00845716

// Aqui se generan los vectores con datos aleatorios para las pruebas.
// Se manejan 3 tipos: enteros (int), reales (double) y textos (string).
// Usamos la libreria <random> de C++ moderno para los numeros al azar.

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include <string>
#include <random>

using namespace std;

// Un solo generador de numeros al azar para todo el programa.
// Se crea una vez y se reutiliza (asi los datos salen bien mezclados).
inline mt19937& generador() {
    static random_device semilla;      // fuente de aleatoriedad del sistema
    static mt19937 motor(semilla());   // motor de numeros aleatorios
    return motor;
}

// Genera un vector de "n" numeros enteros al azar entre 0 y 1,000,000.
inline vector<int> generarEnteros(int n) {
    vector<int> datos(n);
    uniform_int_distribution<int> rango(0, 1000000);
    for (int i = 0; i < n; i++) {
        datos[i] = rango(generador());
    }
    return datos;
}

// Genera un vector de "n" numeros reales (double) al azar entre 0 y 1,000,000.
inline vector<double> generarDoubles(int n) {
    vector<double> datos(n);
    uniform_real_distribution<double> rango(0.0, 1000000.0);
    for (int i = 0; i < n; i++) {
        datos[i] = rango(generador());
    }
    return datos;
}

// Genera un vector de "n" textos al azar.
// Cada texto tiene entre 5 y 10 letras/numeros.
inline vector<string> generarStrings(int n) {
    const string caracteres =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    uniform_int_distribution<int> largo(5, 10);
    uniform_int_distribution<int> letra(0, static_cast<int>(caracteres.size()) - 1);

    vector<string> datos(n);
    for (int i = 0; i < n; i++) {
        int cantidad = largo(generador());
        string palabra;
        for (int c = 0; c < cantidad; c++) {
            palabra += caracteres[letra(generador())];
        }
        datos[i] = palabra;
    }
    return datos;
}

#endif // DATA_GENERATOR_H
