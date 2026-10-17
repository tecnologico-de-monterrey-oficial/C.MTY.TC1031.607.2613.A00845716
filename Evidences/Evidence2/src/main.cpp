// Diego Contreras
// A00845716

// Programa principal: al iniciar pregunta qué archivo cargar y después
// muestra el menú para trabajar con los registros. La estructura viene del
// main de la Evidencia 1.

#include <iostream>
#include <string>
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
            std::cout << "Ordenar: pendiente." << std::endl;
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
