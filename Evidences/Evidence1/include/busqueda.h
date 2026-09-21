// Diego Contreras
// A00845716

// Busqueda por rango de fechas usando dos busquedas binarias de frontera.

#pragma once
#include <vector>
#include "registro.h"

int limiteInferior(const std::vector<Registro>& v, long long clave);
int limiteSuperior(const std::vector<Registro>& v, long long clave);
void buscarRango(const std::vector<Registro>& v, long long inicio, long long fin,
                 std::vector<Registro>& resultado);
