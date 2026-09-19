// Diego Contreras
// A00845716

// Programa principal: menu para cargar un archivo de log, ordenarlo y
// buscar registros por rango de fechas.

#include <iostream>
#include <string>
#include <vector>
#include "registro.h"
#include "entrada.h"

// Los dos archivos que se pueden analizar.
const std::string RUTAS[2]   = {"data/log607-1.txt", "data/log607-2.txt"};
const std::string NOMBRES[2] = {"log607-1.txt (desordenado)", "log607-2.txt (casi ordenado)"};

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
    std::string archivoActual = "";   // cuál archivo está cargado
    bool hayOrdenado = false;         // se vuelve true en la Fase 3 al ordenar

    while (true) {
        mostrarMenu();
        int opcion = leerEntero("Opción: ", 0, 3);

        if (opcion == 0) {
            std::cout << "Hasta luego." << std::endl;
            break;
        }

        if (opcion == 1) {
            // Submenu para escoger cual de los dos archivos se carga.
            std::cout << "\n¿Qué archivo quieres usar?" << std::endl;
            std::cout << "1. " << NOMBRES[0] << std::endl;
            std::cout << "2. " << NOMBRES[1] << std::endl;
            std::cout << "0. Regresar al menú" << std::endl;

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
            std::cout << "Ordenamiento pendiente (Fase 3)." << std::endl;
            continue;
        }

        if (opcion == 2) {
            // La busqueda binaria da resultados falsos si los datos no estan ordenados.
            if (!hayOrdenado) {
                std::cout << "Primero ordena un archivo con la opción 1. "
                          << "La búsqueda binaria solo funciona sobre datos ordenados."
                          << std::endl;
                continue;
            }
            std::cout << "Búsqueda pendiente (Fase 6)." << std::endl;
            continue;
        }

        if (opcion == 3) {
            std::cout << "Historial pendiente (Fase 5)." << std::endl;
            continue;
        }
    }

    return 0;
}
