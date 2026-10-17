// Diego Contreras
// A00845716

// Carga de un archivo de log en dos etapas:
// 1. Se lee el archivo y cada línea se forma en una Fila (el buffer de lectura).
// 2. Se atiende la Fila: cada línea se parsea y, si es válida, se agrega
//    al final de la lista doble. Si no, se avisa con su número y su motivo.
// También escribe la lista en un archivo de salida.

#pragma once
#include <string>
#include "registro.h"
#include "DoublyLinkedList.h"

// Una línea tal como salió del archivo, junto con su número de línea,
// para poder decir cuál se omitió.
struct LineaLeida {
    int numero = 0;
    std::string texto;
};

// Carga el archivo de ruta en la lista. Antes de cargar, vacía la lista
// anterior y la deja con ordenada = false.
// Si el archivo no se puede abrir, avisa con la ruta, no toca la lista
// y regresa false para que el menú siga.
bool cargarArchivo(const std::string& ruta, DoublyLinkedList<Registro>& lista);

// Escribe la lista en un archivo, una línea por nodo y en el orden de la lista.
// Regresa false si el archivo no se pudo crear.
bool escribirArchivo(const std::string& ruta, const DoublyLinkedList<Registro>& lista);
