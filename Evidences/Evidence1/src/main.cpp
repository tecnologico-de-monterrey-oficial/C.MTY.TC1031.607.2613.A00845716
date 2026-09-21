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
#include "corridas.h"
#include "busqueda.h"

// Los dos archivos que se pueden analizar.
const std::string RUTAS[2]   = {"data/log607-1.txt", "data/log607-2.txt"};
const std::string NOMBRES[2] = {"log607-1.txt (desordenado)", "log607-2.txt (casi ordenado)"};
const std::string NOMBRES_CORTOS[2] = {"log607-1.txt", "log607-2.txt"};

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

// Pide una fecha hasta que el usuario escriba una valida y regresa su clave.
// Toda la validacion la hace fechaAClave, la misma que se usa al leer el archivo.
long long leerFecha(const std::string& mensaje) {
    while (true) {
        std::string texto = leerTextoNoVacio(mensaje);
        long long clave = 0;
        if (fechaAClave(texto, clave)) {
            return clave;
        }
        std::cout << "Fecha invalida. Usa el formato Mmm dd aaaa hh:mm:ss, "
                  << "por ejemplo Oct 02 2024 23:04:24." << std::endl;
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
    std::string archivoCorto = "";    // el mismo nombre pero sin la descripción
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
            archivoCorto = NOMBRES_CORTOS[cual - 1];
            // Los datos recien cargados vienen como estan en el archivo, sin ordenar.
            hayOrdenado = false;

            std::cout << "Se cargaron " << original.size() << " registros de "
                      << archivoActual << "." << std::endl;

            // Submenu de algoritmos. En la Fase 4 se le agregan los demas.
            std::cout << "\nQue algoritmo quieres usar?" << std::endl;
            for (int i = 0; i < NUM_ALGORITMOS; i++) {
                std::cout << (i + 1) << ". " << infoAlgoritmo(i + 1).nombre << std::endl;
            }
            std::cout << "0. Regresar al menu" << std::endl;

            int algoritmo = leerEntero("Algoritmo: ", 0, NUM_ALGORITMOS);
            if (algoritmo == 0) {
                continue;
            }

            const InfoAlgoritmo& info = infoAlgoritmo(algoritmo);

            std::cout << "\nVas a ordenar " << original.size() << " registros de "
                      << archivoActual << " con " << info.nombre << "." << std::endl;

            // La prediccion se pide antes de empezar a medir. Si se pidiera en medio,
            // el tiempo que tarda el usuario en escribir contaria como tiempo del algoritmo.
            std::string razon = "";
            int prediccion = pedirPrediccion(razon);

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

            int resultado = clasificarTiempo(ms);

            std::cout << "\n----------------------------------------" << std::endl;
            std::cout << "Algoritmo:    " << info.nombre << std::endl;
            std::cout << "Archivo:      " << archivoActual << std::endl;
            std::cout << "Registros:    " << ordenados.size() << std::endl;
            std::cout << "Tiempo:       " << std::fixed << std::setprecision(3)
                      << ms << " ms" << std::endl;
            std::cout << "Complejidad:  mejor caso " << info.mejorCaso
                      << ", peor caso " << info.peorCaso << std::endl;
            std::cout << "Estable:      " << (info.estable ? "si" : "no") << std::endl;
            std::cout << "Prediccion:   " << nombreCategoria(prediccion) << std::endl;
            std::cout << "Resultado:    " << nombreCategoria(resultado) << std::endl;
            std::cout << "Coincidio:    " << (prediccion == resultado ? "si" : "no")
                      << std::endl;
            std::cout << "Verificacion: datos ordenados correctamente" << std::endl;

            if (escribirArchivo("out/output607.txt", ordenados)) {
                std::cout << "Salida guardada en out/output607.txt" << std::endl;
            }

            Corrida corrida;
            corrida.algoritmo  = info.nombre;
            corrida.archivo    = archivoCorto;
            corrida.registros  = (int)ordenados.size();
            corrida.ms         = ms;
            corrida.mejorCaso  = info.mejorCaso;
            corrida.peorCaso   = info.peorCaso;
            corrida.prediccion = prediccion;
            corrida.resultado  = resultado;
            corrida.razon      = razon;

            if (guardarCorrida(corrida, "out/corridas.csv")) {
                std::cout << "Corrida guardada en out/corridas.csv" << std::endl;
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
            std::cout << "\nHay " << ordenados.size() << " registros ordenados."
                      << std::endl;
            std::cout << "Los datos van de " << claveATexto(ordenados.front().clave)
                      << " a " << claveATexto(ordenados.back().clave) << "."
                      << std::endl;
            std::cout << "Las fechas que escribas no tienen que existir en el archivo."
                      << std::endl;

            // Se vuelven a pedir las dos fechas si el inicio queda despues del fin.
            // Se decidio volver a pedirlas en vez de intercambiarlas, para no
            // adivinar lo que el usuario quiso decir.
            long long inicio = 0;
            long long fin = 0;
            while (true) {
                inicio = leerFecha("Fecha de inicio: ");
                fin    = leerFecha("Fecha de fin:    ");
                if (inicio <= fin) {
                    break;
                }
                std::cout << "La fecha de inicio no puede ser posterior a la de fin."
                          << std::endl;
            }

            // Se busca sobre los datos ordenados, nunca sobre los originales.
            std::vector<Registro> resultado;
            buscarRango(ordenados, inicio, fin, resultado);

            std::cout << "\nRegistros encontrados: " << resultado.size() << std::endl;

            if (!resultado.empty()) {
                std::cout << std::endl;
                int total = (int)resultado.size();

                if (total <= 20) {
                    // Pocos resultados: se imprimen todos.
                    for (const Registro& r : resultado) {
                        std::cout << r.linea << std::endl;
                    }
                } else {
                    // Muchos: solo los primeros y los ultimos diez, para no
                    // llenar la pantalla. El archivo si lleva la lista completa.
                    for (int i = 0; i < 10; i++) {
                        std::cout << resultado[i].linea << std::endl;
                    }
                    std::cout << "... (" << (total - 20) << " registros mas) ..."
                              << std::endl;
                    for (int i = total - 10; i < total; i++) {
                        std::cout << resultado[i].linea << std::endl;
                    }
                    std::cout << "\nLa lista completa esta en out/range607.txt."
                              << std::endl;
                }
            } else {
                std::cout << "No hay registros en ese rango. Revisa que las fechas "
                          << "esten dentro del periodo que cubre el archivo." << std::endl;
            }

            // El archivo se escribe siempre, aunque el resultado este vacio.
            // Un archivo vacio tambien es un resultado valido.
            if (escribirArchivo("out/range607.txt", resultado)) {
                std::cout << "Resultado guardado en out/range607.txt" << std::endl;
            }
            continue;
        }

        if (opcion == 3) {
            mostrarHistorial("out/corridas.csv");
            continue;
        }
    }

    return 0;
}
