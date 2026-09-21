// Diego Contreras
// A00845716

// Tabla de complejidades, prediccion antes de ordenar y registro de corridas.

#include "corridas.h"
#include "entrada.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>

// Datos de cada algoritmo, en el mismo orden del menu.
// Shell sort usa la secuencia clasica de saltos n/2, n/4, ..., 1.
static const InfoAlgoritmo INFO[NUM_ALGORITMOS] = {
    {"Bubble sort",                            "O(n)",         "O(n^2)",     true },
    {"Selection sort",                         "O(n^2)",       "O(n^2)",     false},
    {"Insertion sort",                         "O(n)",         "O(n^2)",     true },
    {"Merge sort",                             "O(n log n)",   "O(n log n)", true },
    {"Quick sort (mediana de tres)",           "O(n log n)",   "O(n^2)",     false},
    {"Swap sort",                              "O(n^2)",       "O(n^2)",     false},
    {"Shell sort",                             "O(n log n)",   "O(n^2)",     false},
    {"Quick sort (pivote al final, variante)", "O(n log n)",   "O(n^2)",     false}
};

// Regresa los datos del algoritmo segun el numero del menu (1 a 8).
const InfoAlgoritmo& infoAlgoritmo(int opcion) {
    return INFO[opcion - 1];
}

// Convierte 1, 2 o 3 en el nombre de la categoria.
std::string nombreCategoria(int categoria) {
    if (categoria == 1) return "rapido";
    if (categoria == 2) return "medio";
    return "lento";
}

// Pide la prediccion antes de ordenar. Deja la razon en el parametro
// y regresa la categoria que eligio el usuario.
int pedirPrediccion(std::string& razon) {
    std::cout << "\nAntes de ordenar, haz tu prediccion." << std::endl;
    std::cout << "Que tan rapido crees que sera este algoritmo con este archivo?"
              << std::endl;
    std::cout << "1. Rapido (menos de 10 ms)" << std::endl;
    std::cout << "2. Medio (entre 10 y 60 ms)" << std::endl;
    std::cout << "3. Lento (mas de 60 ms)" << std::endl;

    int categoria = leerEntero("Prediccion: ", 1, 3);
    razon = leerTextoNoVacio(
        "Por que? Menciona el tamano de los datos y que tan ordenado esta el archivo: ");
    return categoria;
}

// Clasifica el tiempo medido en la misma escala que la prediccion.
int clasificarTiempo(double ms) {
    if (ms < 10.0) return 1;
    if (ms > 60.0) return 3;
    return 2;
}

// Prepara un texto para guardarlo en el CSV. Lo encierra en comillas y
// duplica las comillas que traiga adentro, que es la regla del formato CSV.
// Sin esto, una coma o una comilla en la razon romperia la linea.
static std::string comoCampoCSV(const std::string& texto) {
    std::string salida = "\"";
    for (char c : texto) {
        if (c == '"') {
            salida += "\"\"";
        } else {
            salida += c;
        }
    }
    salida += "\"";
    return salida;
}

// Regresa la fecha y hora de ahorita como texto.
static std::string fechaDeHoy() {
    std::time_t ahora = std::time(nullptr);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&ahora));
    return std::string(buffer);
}

// Agrega la corrida al final del CSV, sin borrar las anteriores.
bool guardarCorrida(const Corrida& c, const std::string& ruta) {
    // Si el archivo todavia no existe o esta vacio, hay que escribir el encabezado.
    bool necesitaEncabezado = true;
    std::ifstream revisar(ruta);
    if (revisar.is_open()) {
        if (revisar.peek() != std::ifstream::traits_type::eof()) {
            necesitaEncabezado = false;
        }
        revisar.close();
    }

    // El modo app agrega al final. Sin el, cada corrida borraria el historial.
    std::ofstream archivo(ruta, std::ios::app);
    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo escribir en \"" << ruta << "\"." << std::endl;
        std::cout << "Revisa que la carpeta out/ exista y que estes corriendo el "
                  << "programa desde la carpeta Evidence1." << std::endl;
        return false;
    }

    if (necesitaEncabezado) {
        archivo << "fecha,algoritmo,archivo,registros,tiempo_ms,mejor_caso,peor_caso,"
                << "prediccion,resultado,coincidio,razon\n";
    }

    // El nombre del algoritmo puede traer comas, por ejemplo
    // "Quick sort (pivote al final, variante)", asi que tambien va entrecomillado.
    archivo << fechaDeHoy() << ","
            << comoCampoCSV(c.algoritmo) << ","
            << comoCampoCSV(c.archivo) << ","
            << c.registros << ","
            << std::fixed << std::setprecision(3) << c.ms << ","
            << c.mejorCaso << ","
            << c.peorCaso << ","
            << nombreCategoria(c.prediccion) << ","
            << nombreCategoria(c.resultado) << ","
            << (c.prediccion == c.resultado ? "si" : "no") << ","
            << comoCampoCSV(c.razon) << "\n";

    archivo.close();
    return true;
}

// Parte una linea del CSV en campos. Una coma que va dentro de comillas
// no separa, porque es parte del texto de la razon.
static std::vector<std::string> partirLineaCSV(const std::string& linea) {
    std::vector<std::string> campos;
    std::string actual = "";
    bool dentroDeComillas = false;

    for (size_t i = 0; i < linea.size(); i++) {
        char c = linea[i];

        if (dentroDeComillas) {
            if (c == '"') {
                // Dos comillas seguidas son una comilla de verdad.
                if (i + 1 < linea.size() && linea[i + 1] == '"') {
                    actual += '"';
                    i++;
                } else {
                    dentroDeComillas = false;
                }
            } else {
                actual += c;
            }
        } else {
            if (c == '"') {
                dentroDeComillas = true;
            } else if (c == ',') {
                campos.push_back(actual);
                actual = "";
            } else {
                actual += c;
            }
        }
    }
    campos.push_back(actual);
    return campos;
}

// Muestra en forma de tabla todas las corridas guardadas.
void mostrarHistorial(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cout << "Aun no hay corridas registradas." << std::endl;
        return;
    }

    std::string linea;
    std::getline(archivo, linea);   // se salta el encabezado

    std::vector<std::vector<std::string>> corridas;
    while (std::getline(archivo, linea)) {
        if (!linea.empty()) {
            corridas.push_back(partirLineaCSV(linea));
        }
    }
    archivo.close();

    if (corridas.empty()) {
        std::cout << "Aun no hay corridas registradas." << std::endl;
        return;
    }

    std::cout << "\n" << std::right << std::setw(2) << "#" << "  " << std::left
              << std::setw(30) << "Algoritmo"
              << std::setw(15) << "Archivo"
              << std::right << std::setw(12) << "Tiempo (ms)" << "  "
              << std::left
              << std::setw(12) << "Prediccion"
              << std::setw(11) << "Resultado"
              << "Coincidio" << std::endl;

    for (size_t i = 0; i < corridas.size(); i++) {
        const std::vector<std::string>& c = corridas[i];
        // fecha 0, algoritmo 1, archivo 2, registros 3, tiempo 4,
        // mejor 5, peor 6, prediccion 7, resultado 8, coincidio 9, razon 10
        if (c.size() < 10) {
            continue;   // linea incompleta, se salta
        }
        std::cout << std::right << std::setw(2) << (i + 1) << "  " << std::left
                  << std::setw(30) << c[1]
                  << std::setw(15) << c[2]
                  << std::right << std::setw(12) << c[4] << "  "
                  << std::left
                  << std::setw(12) << c[7]
                  << std::setw(11) << c[8]
                  << c[9] << std::endl;
    }

    std::cout << "\nLa razon de cada prediccion esta en " << ruta << "." << std::endl;
}
