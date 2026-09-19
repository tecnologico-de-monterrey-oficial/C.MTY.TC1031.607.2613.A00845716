// Diego Contreras
// A00845716

// Funciones para leer datos del usuario sin que el programa se rompa.

#pragma once
#include <string>

int leerEntero(const std::string& mensaje, int min, int max);
std::string leerTextoNoVacio(const std::string& mensaje);
