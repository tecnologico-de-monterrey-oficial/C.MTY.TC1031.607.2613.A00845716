// Diego Contreras
// A00845716

// Carga de un archivo de log: archivo -> Fila -> lista doble.
// El ciclo de lectura viene de leerArchivo de la Evidencia 1, pero ahora
// está partido en dos etapas.

#include "carga.h"
#include "Queue.h"
#include <fstream>
#include <iostream>

bool cargarArchivo(const std::string& ruta, DoublyLinkedList<Registro>& lista) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo abrir el archivo \"" << ruta << "\"." << std::endl;
        std::cout << "Revisa que exista y que lo estes corriendo desde la carpeta Evidence2."
                  << std::endl;
        return false;
    }

    // El archivo sí abrió: se borra lo que hubiera de la carga anterior.
    // clear() también deja ordenada = false.
    lista.clear();

    // Etapa 1: leer el archivo y formar cada línea en la Fila.
    // getline también regresa la última línea aunque no termine en salto de línea.
    Queue<LineaLeida> buffer;
    std::string texto;
    int numeroLinea = 0;
    while (std::getline(archivo, texto)) {
        numeroLinea++;

        // Si el archivo viene de Windows cada línea termina en \r y hay que quitarlo.
        if (!texto.empty() && texto.back() == '\r') {
            texto.pop_back();
        }

        LineaLeida leida;
        leida.numero = numeroLinea;
        leida.texto = texto;
        buffer.enqueue(leida);
    }
    archivo.close();

    // Etapa 2: atender la Fila en orden. Cada línea válida se agrega
    // al final de la lista; las demás se reportan con su motivo.
    int cargados = 0;
    int omitidas = 0;
    LineaLeida leida;
    while (buffer.dequeue(leida)) {
        Registro reg;
        std::string motivo;
        if (parsearLinea(leida.texto, reg, motivo)) {
            lista.insertBack(reg);
            cargados++;
        } else {
            std::cout << "Linea " << leida.numero << " omitida: " << motivo << std::endl;
            omitidas++;
        }
    }

    std::cout << "Registros cargados: " << cargados
              << ". Lineas omitidas: " << omitidas << "." << std::endl;
    return true;
}
