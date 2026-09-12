// Diego Contreras
// A00845716

// Mide los tiempos (en nanosegundos) y hace la comparacion que se guarda en CSV.
// Solo se mide el ordenamiento, no la generacion ni la impresion.

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

#include "sorting.h"
#include "data_generator.h"

using namespace std;

const int NUM_ALGORITMOS = 7;

// Nombre del algoritmo segun su numero.
inline string nombreAlgoritmo(int id) {
    switch (id) {
        case 1: return "Swap Sort";
        case 2: return "Bubble Sort";
        case 3: return "Selection Sort";
        case 4: return "Insertion Sort";
        case 5: return "Merge Sort";
        case 6: return "Quick Sort";
        case 7: return "Shell Sort";
        default: return "Desconocido";
    }
}

// Ordena una copia y regresa cuantos nanosegundos tardo solo el ordenamiento.
template <typename T>
long long medirAlgoritmo(int id, const vector<T>& original) {
    vector<T> copia = original; // copia fuera del cronometro

    auto inicio = chrono::high_resolution_clock::now();
    aplicarOrden(id, copia);
    auto fin = chrono::high_resolution_clock::now();

    if (!estaOrdenado(copia)) {
        cerr << "  [AVISO] " << nombreAlgoritmo(id)
             << " no dejo el vector ordenado!\n";
    }

    return chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();
}

// Mide los 7 algoritmos de un tipo en los 3 tamanos y escribe una fila por algoritmo.
template <typename T>
void medirTipo(const string& nombreTipo,
               const vector<T>& original1000,
               const vector<T>& original10000,
               const vector<T>& original100000,
               ofstream& archivoCSV) {
    for (int id = 1; id <= NUM_ALGORITMOS; id++) {
        cout << "  Midiendo " << nombreAlgoritmo(id)
             << " (" << nombreTipo << ")..." << endl;

        long long t1000   = medirAlgoritmo(id, original1000);
        long long t10000  = medirAlgoritmo(id, original10000);
        long long t100000 = medirAlgoritmo(id, original100000);

        cout << "    " << nombreAlgoritmo(id) << "," << nombreTipo << ","
             << t1000 << "," << t10000 << "," << t100000 << endl;

        archivoCSV << nombreAlgoritmo(id) << "," << nombreTipo << ","
                   << t1000 << "," << t10000 << "," << t100000 << "\n";
    }
}

// Analisis completo: 7 algoritmos x 3 tipos x 3 tamanos = 21 filas en el CSV.
inline void analisisComparativo() {
    const string nombreArchivo = "resultados_tiempos.csv";
    ofstream archivoCSV(nombreArchivo);
    if (!archivoCSV.is_open()) {
        cout << "No se pudo crear el archivo " << nombreArchivo << "\n";
        return;
    }

    archivoCSV << "algoritmo,tipo_dato,tiempo1000,tiempo10000,tiempo100000\n";

    cout << "\n=== ANALISIS COMPARATIVO (tiempos en nanosegundos) ===\n";
    cout << "algoritmo,tipo_dato,tiempo1000,tiempo10000,tiempo100000\n";

    cout << "\n>> Generando datos int...\n";
    vector<int> int1000   = generarEnteros(1000);
    vector<int> int10000  = generarEnteros(10000);
    vector<int> int100000 = generarEnteros(100000);
    medirTipo("int", int1000, int10000, int100000, archivoCSV);

    cout << "\n>> Generando datos double...\n";
    vector<double> dbl1000   = generarDoubles(1000);
    vector<double> dbl10000  = generarDoubles(10000);
    vector<double> dbl100000 = generarDoubles(100000);
    medirTipo("double", dbl1000, dbl10000, dbl100000, archivoCSV);

    cout << "\n>> Generando datos string...\n";
    vector<string> str1000   = generarStrings(1000);
    vector<string> str10000  = generarStrings(10000);
    vector<string> str100000 = generarStrings(100000);
    medirTipo("string", str1000, str10000, str100000, archivoCSV);

    archivoCSV.close();

    cout << "\nListo. Los resultados se guardaron en: " << nombreArchivo << "\n";
}

#endif // BENCHMARK_H
