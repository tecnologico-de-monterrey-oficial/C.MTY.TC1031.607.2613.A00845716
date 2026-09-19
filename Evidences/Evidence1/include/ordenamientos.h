// Diego Contreras
// A00845716

// Algoritmos de ordenamiento. Todos son templates y ordenan de menor a mayor usando <.

#pragma once
#include <vector>
#include <utility>

// Bubble sort: sube el mayor comparando vecinos.
// Es estable porque solo intercambia con menor estricto, asi que dos registros
// con la misma fecha conservan el orden en el que venian en el archivo.
template <class T>
void bubbleSort(std::vector<T>& v) {
    int n = (int)v.size();

    for (int i = 0; i < n - 1; i++) {
        bool huboIntercambio = false;

        // Cada pasada deja el mayor al final, asi que el ciclo interno
        // puede recorrer una posicion menos cada vez.
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j + 1] < v[j]) {
                std::swap(v[j], v[j + 1]);
                huboIntercambio = true;
            }
        }

        // Si una pasada completa no intercambio nada, ya esta ordenado.
        // Por esto tarda casi nada con un archivo que ya viene casi en orden.
        if (!huboIntercambio) {
            break;
        }
    }
}

// Revisa que el vector quedo de menor a mayor. Sirve para comprobar
// que el algoritmo funciono, no es una opcion del usuario.
template <class T>
bool estaOrdenado(const std::vector<T>& v) {
    for (size_t i = 0; i + 1 < v.size(); i++) {
        if (v[i + 1] < v[i]) {
            return false;
        }
    }
    return true;
}
