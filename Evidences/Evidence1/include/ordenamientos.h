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

// Selection sort: busca el menor que falta y lo pone al inicio de lo que falta.
// No es estable: al intercambiar, un registro puede brincar por encima de otro
// con la misma fecha. Siempre recorre todo, asi que no le ayuda que los datos
// ya vengan casi ordenados.
template <class T>
void selectionSort(std::vector<T>& v) {
    int n = (int)v.size();

    for (int i = 0; i < n - 1; i++) {
        int posMinimo = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[posMinimo]) {
                posMinimo = j;
            }
        }
        // Solo intercambia si el minimo no estaba ya en su lugar.
        if (posMinimo != i) {
            std::swap(v[i], v[posMinimo]);
        }
    }
}

// Insertion sort: toma cada elemento y lo mete en su lugar dentro de la parte
// que ya esta ordenada, recorriendo los demas a la derecha en vez de intercambiar.
// Es estable porque el while usa menor estricto, asi que se detiene al topar con
// un registro de la misma fecha en lugar de pasarle por encima.
template <class T>
void insertionSort(std::vector<T>& v) {
    int n = (int)v.size();

    for (int i = 1; i < n; i++) {
        T actual = v[i];
        int j = i - 1;

        // Corre a la derecha todo lo que sea mayor que el elemento actual.
        while (j >= 0 && actual < v[j]) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = actual;
    }
}

// Mezcla dos mitades que ya estan ordenadas, usando el vector auxiliar.
// Cuando los dos elementos tienen la misma fecha se toma primero el de la
// izquierda, y eso es lo que hace estable al merge sort.
template <class T>
void mezclar(std::vector<T>& v, std::vector<T>& aux, int izq, int medio, int der) {
    for (int k = izq; k <= der; k++) {
        aux[k] = v[k];
    }

    int i = izq;        // avanza por la mitad izquierda
    int j = medio + 1;  // avanza por la mitad derecha
    int k = izq;        // donde se va escribiendo el resultado

    while (i <= medio && j <= der) {
        // Solo se toma el de la derecha si es estrictamente menor.
        if (aux[j] < aux[i]) {
            v[k++] = aux[j++];
        } else {
            v[k++] = aux[i++];
        }
    }

    while (i <= medio) v[k++] = aux[i++];
    while (j <= der)   v[k++] = aux[j++];
}

// Parte recursiva: divide a la mitad, ordena cada mitad y las mezcla.
template <class T>
void mergeSortRec(std::vector<T>& v, std::vector<T>& aux, int izq, int der) {
    if (izq >= der) {
        return;
    }
    int medio = izq + (der - izq) / 2;
    mergeSortRec(v, aux, izq, medio);
    mergeSortRec(v, aux, medio + 1, der);
    mezclar(v, aux, izq, medio, der);
}

// Merge sort. El vector auxiliar se crea una sola vez aqui y se pasa por
// referencia a toda la recursion. Si se creara dentro de cada llamada,
// el programa estaria reservando memoria miles de veces y tardaria mucho mas.
template <class T>
void mergeSort(std::vector<T>& v) {
    if (v.size() <= 1) {
        return;
    }
    std::vector<T> aux(v.size());
    mergeSortRec(v, aux, 0, (int)v.size() - 1);
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
