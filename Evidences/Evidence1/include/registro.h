// Diego Contreras
// A00845716

// Estructura de un registro del log y funciones para leer los archivos.

#pragma once
#include <string>
#include <vector>

struct Registro {
    long long clave;    // Oct 02 2024 23:04:24 se guarda como 20241002230424
    std::string linea;  // la línea original completa
};

// Un registro es menor que otro si su fecha es anterior.
// Así los algoritmos de ordenamiento pueden usar < directamente.
inline bool operator<(const Registro& a, const Registro& b) {
    return a.clave < b.clave;
}

std::string limpiarEspacios(const std::string& texto);
int mesANumero(const std::string& mes);
bool fechaAClave(const std::string& texto, long long& clave);
std::string claveATexto(long long clave);
bool parsearLinea(const std::string& linea, Registro& reg);
bool leerArchivo(const std::string& ruta, std::vector<Registro>& datos);
bool escribirArchivo(const std::string& ruta, const std::vector<Registro>& datos);
