// Diego Contreras
// A00845716

// Main temporal de la Fase 1: solo prueba la lectura de los archivos.

#include <iostream>
#include "registro.h"

int main() {
    std::vector<Registro> datos;
    for (std::string ruta : {"data/log607-1.txt", "data/log607-2.txt",
                             "data/no-existe.txt", "data/prueba-malformada.txt"}) {
        datos.clear();
        std::cout << "\n== " << ruta << std::endl;
        if (leerArchivo(ruta, datos)) {
            std::cout << "Registros leidos: " << datos.size() << std::endl;
            if (!datos.empty())
                std::cout << "Clave del primero: " << datos[0].clave << std::endl;
        }
    }
    return 0;
}
