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

std::string limpiarEspacios(const std::string& texto);
int mesANumero(const std::string& mes);
bool fechaAClave(const std::string& texto, long long& clave);
bool parsearLinea(const std::string& linea, Registro& reg);
bool leerArchivo(const std::string& ruta, std::vector<Registro>& datos);
