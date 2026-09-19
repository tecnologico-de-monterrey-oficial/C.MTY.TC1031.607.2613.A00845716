// Diego Contreras
// A00845716

// Programa principal: menu para cargar un archivo de log, ordenarlo y
// buscar registros por rango de fechas.

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include "registro.h"
#include "entrada.h"
#include "ordenamientos.h"

// Los dos archivos que se pueden analizar.
const std::string RUTAS[2]   = {"data/log607-1.txt", "data/log607-2.txt"};
const std::string NOMBRES[2] = {"log607-1.txt (desordenado)", "log607-2.txt (casi ordenado)"};

// Los algoritmos que puede elegir el usuario. Los primeros siete son los de la
// Act 1.5. El octavo es una variante de quick sort que sirve para comparar.
const int NUM_ALGORITMOS = 8;
const std::string ALGORITMOS[NUM_ALGORITMOS] = {
    "Bubble sort", "Selection sort", "Insertion sort", "Merge sort",
    "Quick sort (mediana de tres)", "Swap sort", "Shell sort",
    "Quick sort (pivote al final)"
};

// Ejecuta el algoritmo que corresponde a la opcion del menu.
void ejecutarAlgoritmo(int opcion, std::vector<Registro>& v) {
    switch (opcion) {
        case 1: bubbleSort(v);            break;
        case 2: selectionSort(v);         break;
        case 3: insertionSort(v);         break;
        case 4: mergeSort(v);             break;
        case 5: quickSort(v);             break;
        case 6: swapSort(v);              break;
        case 7: shellSort(v);             break;
        case 8: quickSortPivoteFinal(v);  break;
    }
}

// Imprime el menu principal.
void mostrarMenu() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Analizador de logs 607" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Ordenar un archivo" << std::endl;
    std::cout << "2. Buscar por rango de fechas" << std::endl;
    std::cout << "3. Ver historial de corridas" << std::endl;
    std::cout << "0. Salir" << std::endl;
}

int main() {
    std::vector<Registro> original;   // los datos tal como vienen del archivo
    std::vector<Registro> ordenados;  // resultado de la ultima corrida, es lo que usa la busqueda
    std::string archivoActual = "";   // cuál archivo está cargado
    bool hayOrdenado = false;         // se vuelve true en la Fase 3 al ordenar

    while (true) {
        mostrarMenu();
        int opcion = leerEntero("Opcion: ", 0, 3);

        if (opcion == 0) {
            std::cout << "Hasta luego." << std::endl;
            break;
        }

        if (opcion == 1) {
            // Submenu para escoger cual de los dos archivos se carga.
            std::cout << "\nQue archivo quieres usar?" << std::endl;
            std::cout << "1. " << NOMBRES[0] << std::endl;
            std::cout << "2. " << NOMBRES[1] << std::endl;
            std::cout << "0. Regresar al menu" << std::endl;

            int cual = leerEntero("Archivo: ", 0, 2);
            if (cual == 0) {
                continue;
            }

            original.clear();
            if (!leerArchivo(RUTAS[cual - 1], original)) {
                // leerArchivo ya explico el problema, nada mas volvemos al menu.
                continue;
            }

            archivoActual = NOMBRES[cual - 1];
            // Los datos recien cargados vienen como estan en el archivo, sin ordenar.
            hayOrdenado = false;

            std::cout << "Se cargaron " << original.size() << " registros de "
                      << archivoActual << "." << std::endl;

            // Submenu de algoritmos. En la Fase 4 se le agregan los demas.
            std::cout << "\nQue algoritmo quieres usar?" << std::endl;
            for (int i = 0; i < NUM_ALGORITMOS; i++) {
                std::cout << (i + 1) << ". " << ALGORITMOS[i] << std::endl;
            }
            std::cout << "0. Regresar al menu" << std::endl;

            int algoritmo = leerEntero("Algoritmo: ", 0, NUM_ALGORITMOS);
            if (algoritmo == 0) {
                continue;
            }

            // Siempre se ordena una copia de los datos como vienen del archivo.
            // La copia se hace antes de empezar a medir, porque copiar no es parte
            // del algoritmo. Asi cada corrida arranca con los mismos datos y los
            // tiempos se pueden comparar entre si.
            std::vector<Registro> copia = original;

            auto inicio = std::chrono::steady_clock::now();
            ejecutarAlgoritmo(algoritmo, copia);
            auto fin = std::chrono::steady_clock::now();

            double ms = std::chrono::duration<double, std::milli>(fin - inicio).count();

            if (!estaOrdenado(copia)) {
                std::cout << "Error: el algoritmo no ordeno correctamente." << std::endl;
                continue;
            }

            ordenados = copia;
            hayOrdenado = true;

            std::cout << "\n----------------------------------------" << std::endl;
            std::cout << "Algoritmo: " << ALGORITMOS[algoritmo - 1] << std::endl;
            std::cout << "Archivo:   " << archivoActual << std::endl;
            std::cout << "Registros: " << ordenados.size() << std::endl;
            std::cout << "Tiempo:    " << std::fixed << std::setprecision(3)
                      << ms << " ms" << std::endl;
            std::cout << "Verificacion: datos ordenados correctamente" << std::endl;

            if (escribirArchivo("out/output607.txt", ordenados)) {
                std::cout << "Salida guardada en out/output607.txt" << std::endl;
            }
            std::cout << "----------------------------------------" << std::endl;
            continue;
        }

        if (opcion == 2) {
            // La busqueda binaria da resultados falsos si los datos no estan ordenados.
            if (!hayOrdenado) {
                std::cout << "Primero ordena un archivo con la opcion 1. "
                          << "La busqueda binaria solo funciona sobre datos ordenados."
                          << std::endl;
                continue;
            }
            std::cout << "Busqueda pendiente (Fase 6). Hay " << ordenados.size()
                      << " registros ordenados listos." << std::endl;
            continue;
        }

        if (opcion == 3) {
            std::cout << "Historial pendiente (Fase 5)." << std::endl;
            continue;
        }
    }

    return 0;
}
