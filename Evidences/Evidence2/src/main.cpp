// Diego Contreras
// A00845716

// Programa principal: al iniciar pregunta qué archivo cargar y después
// muestra el menú para trabajar con los registros. La estructura viene del
// main de la Evidencia 1.

#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <iomanip>
#include "registro.h"
#include "entrada.h"
#include "carga.h"
#include "DoublyLinkedList.h"

// Los archivos que se pueden cargar. Los dos primeros son los logs de la
// actividad. El tercero es un archivo chico con errores a proposito, para poder
// mostrar como se comporta el programa con lineas vacias y fechas imposibles.
const int NUM_ARCHIVOS = 3;
const std::string RUTAS[NUM_ARCHIVOS] = {
    "data/log607-1.txt", "data/log607-2.txt", "data/prueba-malformada.txt"
};
const std::string NOMBRES[NUM_ARCHIVOS] = {
    "log607-1.txt (aleatorio)",
    "log607-2.txt (casi ordenado)",
    "prueba-malformada.txt (archivo de prueba de manejo de errores)"
};

// Pregunta qué archivo cargar hasta que uno se cargue bien.
// Regresa el número del archivo (1 a 3), o 0 si el usuario prefiere salir.
int elegirYCargar(DoublyLinkedList<Registro>& lista) {
    while (true) {
        std::cout << "\nQue archivo quieres cargar?" << std::endl;
        for (int i = 0; i < NUM_ARCHIVOS; i++) {
            std::cout << (i + 1) << ". " << NOMBRES[i] << std::endl;
        }
        std::cout << "0. Salir" << std::endl;

        int cual = leerEntero("Archivo: ", 0, NUM_ARCHIVOS);
        if (cual == 0) {
            return 0;
        }

        // cargarArchivo ya explica el problema si el archivo no abre,
        // así que solo se vuelve a preguntar.
        if (cargarArchivo(RUTAS[cual - 1], lista)) {
            return cual;
        }
    }
}

// Revisa la lista después de ordenar:
// - hacia adelante, cada registro no es menor que el de atrás
// - cada prev apunta al nodo de atrás, así que recorrerla hacia atrás
//   da exactamente lo mismo pero al revés
// - el último nodo es el tail y hacia atrás se cuentan los mismos nodos
bool verificarOrden(const DoublyLinkedList<Registro>& lista) {
    DNode<Registro>* anterior = nullptr;
    int adelante = 0;
    for (DNode<Registro>* aux = lista.getHead(); aux != nullptr; aux = aux->next) {
        if (aux->prev != anterior) {
            return false;
        }
        if (anterior != nullptr && aux->data < anterior->data) {
            return false;
        }
        anterior = aux;
        adelante++;
    }
    if (anterior != lista.getTail()) {
        return false;
    }
    int atras = 0;
    for (DNode<Registro>* aux = lista.getTail(); aux != nullptr; aux = aux->prev) {
        atras++;
    }
    return adelante == lista.size() && atras == lista.size();
}

// Imprime el menú principal.
void mostrarMenu(const std::string& archivoActual, int registros) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Analizador de logs - Evidencia 2" << std::endl;
    std::cout << "  Archivo: " << archivoActual << " (" << registros
              << " registros)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Ordenar" << std::endl;
    std::cout << "2. Buscar por dia" << std::endl;
    std::cout << "3. Mostrar descendente" << std::endl;
    std::cout << "4. Estadisticas" << std::endl;
    std::cout << "5. Salir" << std::endl;
}

int main() {
    DoublyLinkedList<Registro> lista;  // los registros del archivo cargado

    int cual = elegirYCargar(lista);
    if (cual == 0) {
        std::cout << "Hasta luego." << std::endl;
        return 0;
    }
    std::string archivoActual = NOMBRES[cual - 1];

    while (true) {
        mostrarMenu(archivoActual, lista.size());
        // Ojo: en la Evidencia 1 salir era 0, aquí la instrucción pide 5.
        int opcion = leerEntero("Opcion: ", 1, 5);

        if (opcion == 5) {
            std::cout << "Hasta luego." << std::endl;
            break;
        }

        if (opcion == 1) {
            if (lista.isOrdenada()) {
                std::cout << "La lista ya esta ordenada, no hay nada que hacer." << std::endl;
                continue;
            }

            int n = lista.size();
            std::cout << "\nVas a ordenar " << n << " registros de " << archivoActual
                      << " con Merge sort." << std::endl;

            // La prediccion se pide antes de empezar a medir, para que el tiempo
            // que tarda el usuario en escribir no cuente como tiempo del algoritmo.
            std::cout << "\nAntes de ordenar, haz tu prediccion." << std::endl;
            std::cout << "Cuantas comparaciones crees que hara?" << std::endl;
            std::cout << "1. Del orden de n log n" << std::endl;
            std::cout << "2. Del orden de n^2" << std::endl;
            int prediccion = leerEntero("Prediccion: ", 1, 2);

            // Se mide solo el ordenamiento.
            long long comparaciones = 0;
            int profundidad = 0;
            auto inicio = std::chrono::steady_clock::now();
            lista.mergeSort(comparaciones, profundidad);
            auto fin = std::chrono::steady_clock::now();
            double ms = std::chrono::duration<double, std::milli>(fin - inicio).count();

            // Para saber a cual se parece mas, se comparan las comparaciones
            // contra n log2 n y contra n^2 / 2, y se toma la mas cercana.
            double nLogN = (n > 1) ? n * std::log2((double)n) : 0.0;
            double nCuadradaMedios = (double)n * n / 2.0;
            int resultado = 1;
            if (std::fabs(comparaciones - nCuadradaMedios) < std::fabs(comparaciones - nLogN)) {
                resultado = 2;
            }
            std::string nombres[3] = {"", "n log n", "n^2"};

            std::cout << "\n----------------------------------------" << std::endl;
            std::cout << "Algoritmo:      Merge sort sobre la lista doble" << std::endl;
            std::cout << "Archivo:        " << archivoActual << std::endl;
            std::cout << "n:              " << n << std::endl;
            std::cout << "Tiempo:         " << std::fixed << std::setprecision(3)
                      << ms << " ms" << std::endl;
            std::cout << "Comparaciones:  " << comparaciones << std::endl;
            std::cout << "  n log2 n:     " << std::setprecision(0) << nLogN << std::endl;
            std::cout << "  n^2 / 2:      " << nCuadradaMedios << std::endl;
            std::cout << "Profundidad:    " << profundidad
                      << " (la primera llamada cuenta como 1)" << std::endl;
            std::cout << "Prediccion:     " << nombres[prediccion] << std::endl;
            std::cout << "Resultado:      " << nombres[resultado] << std::endl;
            std::cout << "Coincidio:      " << (prediccion == resultado ? "si" : "no")
                      << std::endl;
            std::cout << std::defaultfloat;

            if (verificarOrden(lista)) {
                std::cout << "Verificacion:   ordenada, y hacia atras sale exactamente al reves"
                          << std::endl;
            } else {
                std::cout << "Error: la lista no quedo bien ordenada o enlazada." << std::endl;
            }

            if (escribirArchivo("out/output608.out", lista)) {
                std::cout << "Salida guardada en out/output608.out" << std::endl;
            }
            std::cout << "----------------------------------------" << std::endl;
            continue;
        }

        if (opcion == 2) {
            std::cout << "Buscar por dia: pendiente." << std::endl;
            continue;
        }

        if (opcion == 3) {
            std::cout << "Mostrar descendente: pendiente." << std::endl;
            continue;
        }

        if (opcion == 4) {
            std::cout << "Estadisticas: pendiente." << std::endl;
            continue;
        }
    }

    return 0;
}
