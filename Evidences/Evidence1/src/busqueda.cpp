// Diego Contreras
// A00845716

// Dos busquedas binarias de frontera. Una busqueda binaria normal contesta
// "esta este valor y donde", pero aqui hace falta otra cosa: donde empieza y
// donde termina el pedazo que cae dentro del rango. Por eso son dos, y ninguna
// se detiene cuando encuentra el valor.

#include "busqueda.h"

// Primera posicion cuya fecha es mayor o igual a la clave.
// Si todas las fechas son menores, regresa v.size(), que significa "no hay ninguna".
int limiteInferior(const std::vector<Registro>& v, long long clave) {
    int bajo = 0;
    int alto = (int)v.size();          // size(), no size() - 1, para poder decir "ninguna"

    while (bajo < alto) {
        // Se resta antes de dividir para que la suma nunca se pase del limite del int.
        int medio = bajo + (alto - bajo) / 2;

        if (v[medio].clave < clave) {
            bajo = medio + 1;          // este y todos los de su izquierda no sirven
        } else {
            alto = medio;              // este podria servir, pero sigo buscando a la izquierda
        }
    }
    return bajo;
}

// Primera posicion cuya fecha es estrictamente mayor que la clave.
// Es igual a la de arriba salvo por el "igual" de la comparacion: ese menor o igual
// hace que se brinque todos los registros repetidos y caiga en el primero mayor.
int limiteSuperior(const std::vector<Registro>& v, long long clave) {
    int bajo = 0;
    int alto = (int)v.size();

    while (bajo < alto) {
        int medio = bajo + (alto - bajo) / 2;

        if (v[medio].clave <= clave) {
            bajo = medio + 1;
        } else {
            alto = medio;
        }
    }
    return bajo;
}

// Copia en resultado todos los registros cuya fecha cae entre inicio y fin,
// incluyendo los dos extremos. Como es un pedazo continuo del vector ordenado,
// no se puede perder ni repetir ningun registro.
void buscarRango(const std::vector<Registro>& v, long long inicio, long long fin,
                 std::vector<Registro>& resultado) {
    resultado.clear();

    int desde = limiteInferior(v, inicio);
    int hasta = limiteSuperior(v, fin);   // esta posicion NO se incluye

    // Si el rango esta vacio, desde queda mayor o igual que hasta y el ciclo no corre.
    for (int i = desde; i < hasta; i++) {
        resultado.push_back(v[i]);
    }
}
