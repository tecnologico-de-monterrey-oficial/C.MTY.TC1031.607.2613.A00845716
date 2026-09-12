// Diego Contreras
// A00845716

// Aqui estan los 7 algoritmos de ordenamiento hechos a mano.
// Todos ordenan de menor a mayor (ascendente) y funcionan con
// cualquier tipo de dato que se pueda comparar con <, gracias a
// que estan hechos como plantillas (template).

#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <utility>   // para std::swap
#include <algorithm> // solo para std::is_sorted (verificar, NO ordenar)

using namespace std;

// ------------------------------------------------------------------
// 1. SWAP SORT
// ------------------------------------------------------------------
// Recorre el vector comparando cada elemento con todos los que estan
// mas adelante. Si encuentra uno menor, los intercambia. Al final
// cada posicion queda con el valor mas pequeno que le corresponde.
template <typename T>
void swapSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // si el de adelante es menor, los cambiamos de lugar
            if (lista[j] < lista[i]) {
                swap(lista[i], lista[j]);
            }
        }
    }
}

// ------------------------------------------------------------------
// 2. BUBBLE SORT
// ------------------------------------------------------------------
// Compara pares de vecinos y los intercambia si estan en desorden.
// Los valores grandes van "subiendo" hasta el final como burbujas.
// Optimizacion: si en una pasada no hubo ningun intercambio, ya
// esta ordenado y terminamos antes.
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
        // si esta pasada no movio nada, el vector ya quedo ordenado
        if (!huboCambio) {
            break;
        }
    }
}

// ------------------------------------------------------------------
// 3. SELECTION SORT
// ------------------------------------------------------------------
// En cada vuelta busca el elemento mas pequeno de la parte que falta
// por ordenar y lo coloca al inicio de esa parte.
template <typename T>
void selectionSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 0; i < n - 1; i++) {
        int posMinimo = i;
        // buscamos el menor desde i+1 hasta el final
        for (int j = i + 1; j < n; j++) {
            if (lista[j] < lista[posMinimo]) {
                posMinimo = j;
            }
        }
        // lo ponemos en su lugar
        if (posMinimo != i) {
            swap(lista[i], lista[posMinimo]);
        }
    }
}

// ------------------------------------------------------------------
// 4. INSERTION SORT
// ------------------------------------------------------------------
// Toma un elemento a la vez y lo va "insertando" en el lugar correcto
// de la parte que ya esta ordenada a su izquierda.
template <typename T>
void insertionSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 1; i < n; i++) {
        T actual = lista[i];
        int j = i - 1;
        // corremos hacia la derecha los que sean mayores que "actual"
        while (j >= 0 && lista[j] > actual) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = actual;
    }
}

// ------------------------------------------------------------------
// 5. MERGE SORT
// ------------------------------------------------------------------
// Divide el vector en dos mitades, ordena cada mitad por separado
// (recursivamente) y luego las mezcla en orden.

// Funcion auxiliar: mezcla dos partes YA ordenadas del vector.
// La parte izquierda va de "izq" a "medio" y la derecha de
// "medio+1" a "der".
template <typename T>
void merge(vector<T>& lista, int izq, int medio, int der) {
    // copiamos cada mitad en un vector temporal
    vector<T> parteIzq(lista.begin() + izq, lista.begin() + medio + 1);
    vector<T> parteDer(lista.begin() + medio + 1, lista.begin() + der + 1);

    int i = 0;          // indice para la parte izquierda
    int j = 0;          // indice para la parte derecha
    int k = izq;        // indice donde vamos escribiendo en el original

    // vamos tomando el menor de las dos partes y lo colocamos
    while (i < static_cast<int>(parteIzq.size()) &&
           j < static_cast<int>(parteDer.size())) {
        if (parteIzq[i] <= parteDer[j]) {
            lista[k] = parteIzq[i];
            i++;
        } else {
            lista[k] = parteDer[j];
            j++;
        }
        k++;
    }
    // si sobraron elementos en alguna parte, se copian tal cual
    while (i < static_cast<int>(parteIzq.size())) {
        lista[k] = parteIzq[i];
        i++;
        k++;
    }
    while (j < static_cast<int>(parteDer.size())) {
        lista[k] = parteDer[j];
        j++;
        k++;
    }
}

// Version recursiva que trabaja con indices.
template <typename T>
void mergeSort(vector<T>& lista, int izq, int der) {
    if (izq >= der) {
        return; // 0 o 1 elemento: ya esta ordenado
    }
    int medio = izq + (der - izq) / 2;
    mergeSort(lista, izq, medio);       // ordena mitad izquierda
    mergeSort(lista, medio + 1, der);   // ordena mitad derecha
    merge(lista, izq, medio, der);      // mezcla las dos mitades
}

// Version comoda para llamar sin pasar indices.
template <typename T>
void mergeSort(vector<T>& lista) {
    if (lista.size() > 1) {
        mergeSort(lista, 0, static_cast<int>(lista.size()) - 1);
    }
}

// ------------------------------------------------------------------
// 6. QUICK SORT
// ------------------------------------------------------------------
// Elige un valor de referencia (pivote), acomoda los menores a la
// izquierda y los mayores a la derecha, y repite en cada lado.
//
// Para elegir el pivote usamos la "mediana de tres" (primero, medio
// y ultimo). Esto evita que se vuelva muy lento y muy profundo cuando
// los datos ya vienen ordenados o al reves.

// Coloca en la ultima posicion un buen pivote (la mediana de tres).
template <typename T>
void elegirPivote(vector<T>& lista, int izq, int der) {
    int medio = izq + (der - izq) / 2;
    // ordenamos entre si el primero, el de en medio y el ultimo
    if (lista[medio] < lista[izq]) swap(lista[izq], lista[medio]);
    if (lista[der] < lista[izq])   swap(lista[izq], lista[der]);
    if (lista[der] < lista[medio]) swap(lista[medio], lista[der]);
    // dejamos la mediana (que quedo en "medio") justo antes del final
    swap(lista[medio], lista[der]);
}

// Particion: deja el pivote en su lugar definitivo y regresa su posicion.
template <typename T>
int particion(vector<T>& lista, int izq, int der) {
    elegirPivote(lista, izq, der);
    T pivote = lista[der]; // el pivote quedo al final
    int i = izq - 1;       // marca el limite de los menores al pivote
    for (int j = izq; j < der; j++) {
        if (lista[j] <= pivote) {
            i++;
            swap(lista[i], lista[j]);
        }
    }
    // colocamos el pivote justo despues de los menores
    swap(lista[i + 1], lista[der]);
    return i + 1;
}

// Version recursiva con indices.
template <typename T>
void quickSort(vector<T>& lista, int izq, int der) {
    if (izq < der) {
        int p = particion(lista, izq, der);
        quickSort(lista, izq, p - 1);   // lado de los menores
        quickSort(lista, p + 1, der);   // lado de los mayores
    }
}

// Version comoda para llamar sin pasar indices.
template <typename T>
void quickSort(vector<T>& lista) {
    if (lista.size() > 1) {
        quickSort(lista, 0, static_cast<int>(lista.size()) - 1);
    }
}

// ------------------------------------------------------------------
// 7. SHELL SORT  (algoritmo extra, no visto en clase)
// ------------------------------------------------------------------
// Es como el insertion sort pero comparando elementos separados por
// un "salto" (gap) que empieza grande y se va reduciendo a la mitad.
// Asi los valores llegan mas rapido a su zona correcta.
template <typename T>
void shellSort(vector<T>& lista) {
    int n = static_cast<int>(lista.size());
    for (int salto = n / 2; salto > 0; salto /= 2) {
        // insertion sort usando el salto actual
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

// ------------------------------------------------------------------
// Aplica el algoritmo indicado por su numero (1 a 7) sobre el vector.
// Sirve para no repetir el mismo switch en varias partes del programa.
//   1 = Swap, 2 = Bubble, 3 = Selection, 4 = Insertion,
//   5 = Merge, 6 = Quick, 7 = Shell
// ------------------------------------------------------------------
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

// ------------------------------------------------------------------
// Ayuda para verificar que un vector realmente quedo ordenado.
// (Usamos is_sorted SOLO para comprobar, nunca para ordenar.)
// ------------------------------------------------------------------
template <typename T>
bool estaOrdenado(const vector<T>& lista) {
    return is_sorted(lista.begin(), lista.end());
}

#endif // SORTING_H
