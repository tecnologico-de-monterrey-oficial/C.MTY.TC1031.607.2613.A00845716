// Diego Contreras
// A00845716

// Datos de cada algoritmo, prediccion del usuario y registro de corridas en CSV.

#pragma once
#include <string>

struct InfoAlgoritmo {
    std::string nombre;
    std::string mejorCaso;
    std::string peorCaso;
    bool estable;
};

struct Corrida {
    std::string algoritmo;
    std::string archivo;
    int registros;
    double ms;
    std::string mejorCaso;
    std::string peorCaso;
    int prediccion;     // 1 rapido, 2 medio, 3 lento
    int resultado;      // la categoria que salio segun el tiempo medido
    std::string razon;
};

const int NUM_ALGORITMOS = 8;

const InfoAlgoritmo& infoAlgoritmo(int opcion);
std::string nombreCategoria(int categoria);
int pedirPrediccion(std::string& razon);
int clasificarTiempo(double ms);
bool guardarCorrida(const Corrida& c, const std::string& ruta);
void mostrarHistorial(const std::string& ruta);
