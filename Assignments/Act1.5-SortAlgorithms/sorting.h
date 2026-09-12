// Diego Contreras
// A00845716

// Los 7 algoritmos de ordenamiento (ascendentes, hechos a mano).

#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <utility>
#include <algorithm> // solo para is_sorted (verificar, no ordenar)

using namespace std;

// 1. Swap Sort: compara cada elemento con los de adelante e intercambia.
template <typename T>
void swapSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lista[j] < lista[i]) {
                swap(lista[i], lista[j]);
            }
        }
    }
}

// 2. Bubble Sort: sube el mayor comparando vecinos. Para si ya esta ordenado.
template <typename T>
void bubbleSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 0; i < n - 1; i++) {
        bool huboCambio = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (lista[j] > lista[j + 1]) {
                swap(lista[j], lista[j + 1]);
                huboCambio = true;
            }
        }
        if (!huboCambio) break;
    }
}

// 3. Selection Sort: busca el menor que falta y lo pone al inicio.
template <typename T>
void selectionSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 0; i < n - 1; i++) {
        int posMinimo = i;
        for (int j = i + 1; j < n; j++) {
            if (lista[j] < lista[posMinimo]) {
                posMinimo = j;
            }
        }
        if (posMinimo != i) {
            swap(lista[i], lista[posMinimo]);
        }
    }
}

// 4. Insertion Sort: inserta cada elemento en su lugar de la parte ordenada.
template <typename T>
void insertionSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 1; i < n; i++) {
        T actual = lista[i];
        int j = i - 1;
        while (j >= 0 && lista[j] > actual) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = actual;
    }
}

// 5. Merge Sort. Mezcla dos partes ya ordenadas del vector.
template <typename T>
void merge(vector<T>& lista, int izq, int medio, int der) {
    vector<T> parteIzq(lista.begin() + izq, lista.begin() + medio + 1);
    vector<T> parteDer(lista.begin() + medio + 1, lista.begin() + der + 1);

    int i = 0, j = 0, k = izq;
    while (i < static_cast<int>(parteIzq.size()) &&
           j < static_cast<int>(parteDer.size())) {
        if (parteIzq[i] <= parteDer[j]) {
            lista[k++] = parteIzq[i++];
        } else {
            lista[k++] = parteDer[j++];
        }
    }
    while (i < static_cast<int>(parteIzq.size())) lista[k++] = parteIzq[i++];
    while (j < static_cast<int>(parteDer.size())) lista[k++] = parteDer[j++];
}

// Divide en dos mitades, ordena cada una y las mezcla.
template <typename T>
void mergeSort(vector<T>& lista, int izq, int der) {
    if (izq >= der) return;
    int medio = izq + (der - izq) / 2;
    mergeSort(lista, izq, medio);
    mergeSort(lista, medio + 1, der);
    merge(lista, izq, medio, der);
}

template <typename T>
void mergeSort(vector<T>& lista) {
    if (lista.size() > 1) {
        mergeSort(lista, 0, static_cast<int>(lista.size()) - 1);
    }
}

// 6. Quick Sort. Deja como pivote la mediana de tres (evita el peor caso).
template <typename T>
void elegirPivote(vector<T>& lista, int izq, int der) {
    int medio = izq + (der - izq) / 2;
    if (lista[medio] < lista[izq]) swap(lista[izq], lista[medio]);
    if (lista[der] < lista[izq])   swap(lista[izq], lista[der]);
    if (lista[der] < lista[medio]) swap(lista[medio], lista[der]);
    swap(lista[medio], lista[der]);
}

// Deja los menores a la izquierda del pivote y regresa su posicion.
template <typename T>
int particion(vector<T>& lista, int izq, int der) {
    elegirPivote(lista, izq, der);
    T pivote = lista[der];
    int i = izq - 1;
    for (int j = izq; j < der; j++) {
        if (lista[j] <= pivote) {
            swap(lista[++i], lista[j]);
        }
    }
    swap(lista[i + 1], lista[der]);
    return i + 1;
}

template <typename T>
void quickSort(vector<T>& lista, int izq, int der) {
    if (izq < der) {
        int p = particion(lista, izq, der);
        quickSort(lista, izq, p - 1);
        quickSort(lista, p + 1, der);
    }
}

template <typename T>
void quickSort(vector<T>& lista) {
    if (lista.size() > 1) {
        quickSort(lista, 0, static_cast<int>(lista.size()) - 1);
    }
}

// 7. Shell Sort (extra): insertion sort con saltos que se van reduciendo.
template <typename T>
void shellSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int salto = n / 2; salto > 0; salto /= 2) {
        for (int i = salto; i < n; i++) {
            T actual = lista[i];
            int j = i;
            while (j >= salto && lista[j - salto] > actual) {
                lista[j] = lista[j - salto];
                j -= salto;
            }
            lista[j] = actual;
        }
    }
}

// Aplica el algoritmo por su numero (1 a 7) para no repetir el switch.
template <typename T>
void aplicarOrden(int id, vector<T>& lista) {
    switch (id) {
        case 1: swapSort(lista);      break;
        case 2: bubbleSort(lista);    break;
        case 3: selectionSort(lista); break;
        case 4: insertionSort(lista); break;
        case 5: mergeSort(lista);     break;
        case 6: quickSort(lista);     break;
        case 7: shellSort(lista);     break;
    }
}

// Verifica que el vector quedo ordenado.
template <typename T>
bool estaOrdenado(const vector<T>& lista) {
    return is_sorted(lista.begin(), lista.end());
}

#endif // SORTING_H
