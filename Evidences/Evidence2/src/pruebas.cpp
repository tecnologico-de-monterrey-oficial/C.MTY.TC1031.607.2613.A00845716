// Diego Contreras
// A00845716

// Programa de pruebas de las estructuras: LinkedList, Stack, Queue y
// DoublyLinkedList. Tiene su propio main y se compila aparte de la app:
//
//   g++ -std=c++20 -Wall -Wextra -Iinclude src/pruebas.cpp -o build/pruebas
//   ./build/pruebas > docs/salida_pruebas.txt
//
// Cada estructura se prueba en el mismo orden: vacía, un solo elemento,
// insertar y quitar varias veces en los extremos, e imprimir.
// Cada revisión escribe [OK] o [FALLA], y al final sale el total.

#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "DoublyLinkedList.h"

int numPrueba = 0;   // número de la prueba actual
int revisiones = 0;  // cuántas revisiones se hicieron
int fallas = 0;      // cuántas salieron mal

// Escribe el encabezado de cada estructura.
void seccion(const std::string& nombre) {
    std::cout << std::endl << "==================== " << nombre
            << " ====================" << std::endl;
}

// Escribe el título de una prueba con su número.
void prueba(const std::string& titulo) {
    numPrueba++;
    std::cout << std::endl << "Prueba " << numPrueba << ". " << titulo << std::endl;
}

// Anota si una condición se cumplió o no.
void revisar(bool seCumple, const std::string& descripcion) {
    revisiones++;
    if (seCumple) {
        std::cout << "  [OK] " << descripcion << std::endl;
    } else {
        std::cout << "  [FALLA] " << descripcion << std::endl;
        fallas++;
    }
}

// ---------- Ayudas para la lista doble ----------

// Junta los datos en un texto, por ejemplo "1 2 3".
std::string juntar(const std::vector<int>& datos) {
    if (datos.empty()) {
        return "(vacia)";
    }
    std::string texto;
    for (int i = 0; i < (int)datos.size(); i++) {
        if (i > 0) {
            texto += " ";
        }
        texto += std::to_string(datos[i]);
    }
    return texto;
}

// Recorre la lista doble hacia adelante (con next) y hacia atrás (con prev),
// escribe los dos recorridos y revisa que cuadren:
// - hacia atrás debe salir exactamente al revés que hacia adelante
// - cada prev debe apuntar al nodo que quedó antes
// - head no tiene a nadie atrás y tail no tiene a nadie adelante
// - el número de nodos debe ser igual a size()
// Si algún prev quedó mal, solo se nota en el recorrido hacia atrás.
void recorrer(const DoublyLinkedList<int>& lista, const std::string& esperado) {
    std::vector<int> adelante;
    std::vector<int> atras;
    bool prevBien = true;

    DNode<int>* anterior = nullptr;
    for (DNode<int>* aux = lista.getHead(); aux != nullptr; aux = aux->next) {
        if (aux->prev != anterior) {
            prevBien = false;
        }
        adelante.push_back(aux->data);
        anterior = aux;
    }
    for (DNode<int>* aux = lista.getTail(); aux != nullptr; aux = aux->prev) {
        atras.push_back(aux->data);
    }

    // voltear el recorrido hacia atrás para compararlo con el de adelante
    std::vector<int> atrasVolteado(atras.rbegin(), atras.rend());

    std::cout << "  Adelante: " << juntar(adelante) << std::endl;
    std::cout << "  Atras:    " << juntar(atras) << std::endl;
    revisar(juntar(adelante) == esperado, "la lista queda " + esperado);
    revisar(atrasVolteado == adelante, "hacia atras sale al reves que hacia adelante");
    revisar(prevBien, "cada prev apunta al nodo de atras");
    revisar(anterior == lista.getTail(), "el ultimo nodo recorrido es el tail");
    revisar((int)adelante.size() == lista.size(), "size() = " + std::to_string(lista.size()));
}

// ---------- LinkedList ----------

void probarLinkedList() {
    seccion("LinkedList");
    LinkedList<int> lista;
    int valor = -1;

    prueba("Lista vacia");
    revisar(lista.isEmpty(), "isEmpty() es verdadero");
    revisar(lista.size() == 0, "size() = 0");
    if (!lista.removeFront(valor)) {
        std::cout << "  removeFront: la lista esta vacia, no hay nada que quitar" << std::endl;
    }
    revisar(valor == -1, "removeFront sobre vacia regresa false y no cambia el valor");
    revisar(!lista.getFront(valor), "getFront sobre vacia regresa false");

    prueba("Un solo elemento");
    lista.insertBack(10);
    revisar(lista.size() == 1, "insertBack(10) en vacia deja size() = 1");
    revisar(lista.getFront(valor) && valor == 10, "el primero es 10");
    revisar(lista.removeFront(valor) && valor == 10, "removeFront saca el 10");
    revisar(lista.isEmpty(), "al quitar el unico nodo la lista queda vacia");
    lista.insertFront(20);
    revisar(lista.getFront(valor) && valor == 20, "insertFront(20) en vacia funciona despues de vaciarla");
    lista.removeFront(valor);

    prueba("Insertar y quitar varias veces en los extremos");
    lista.insertBack(2);
    lista.insertFront(1);
    lista.insertBack(3);
    lista.insertFront(0);
    revisar(lista.size() == 4, "insertFront(0,1) e insertBack(2,3) dejan 4 elementos");
    std::cout << "  Lista: ";
    lista.print();
    lista.removeFront(valor);
    revisar(valor == 0, "removeFront saca el 0");
    lista.insertBack(4);
    lista.removeFront(valor);
    revisar(valor == 1, "insertBack(4) y removeFront saca el 1");
    lista.removeFront(valor);
    lista.removeFront(valor);
    lista.removeFront(valor);
    revisar(valor == 4 && lista.isEmpty(), "se sacan 2, 3 y 4 y queda vacia");
    if (!lista.removeFront(valor)) {
        std::cout << "  removeFront: la lista esta vacia, no hay nada que quitar" << std::endl;
    }
    lista.insertBack(7);
    revisar(lista.getFront(valor) && valor == 7, "insertBack(7) despues de vaciarla (tail se reinicio bien)");
    lista.removeFront(valor);

    prueba("Imprimir");
    std::cout << "  Lista vacia: ";
    lista.print();
    lista.insertBack(5);
    lista.insertBack(6);
    lista.insertBack(7);
    std::cout << "  Lista 5, 6, 7: ";
    lista.print();
}

// ---------- Stack ----------

void probarStack() {
    seccion("Stack");
    Stack<int> pila;
    int valor = -1;

    prueba("Pila vacia");
    revisar(pila.isEmpty(), "isEmpty() es verdadero");
    revisar(pila.size() == 0, "size() = 0");
    if (!pila.pop(valor)) {
        std::cout << "  pop: la pila esta vacia" << std::endl;
    }
    revisar(valor == -1, "pop sobre vacia regresa false y no cambia el valor");
    if (!pila.peek(valor)) {
        std::cout << "  peek: la pila esta vacia" << std::endl;
    }
    revisar(valor == -1, "peek sobre vacia regresa false y no cambia el valor");

    prueba("Un solo elemento");
    pila.push(10);
    revisar(pila.size() == 1, "push(10) deja size() = 1");
    revisar(pila.peek(valor) && valor == 10, "peek ve el 10");
    revisar(pila.size() == 1, "peek no saca el elemento");
    revisar(pila.pop(valor) && valor == 10, "pop saca el 10");
    revisar(pila.isEmpty(), "la pila queda vacia");

    prueba("Insertar y quitar varias veces en el extremo (arriba)");
    pila.push(1);
    pila.push(2);
    pila.push(3);
    revisar(pila.peek(valor) && valor == 3, "push(1,2,3) deja el 3 arriba");
    pila.pop(valor);
    revisar(valor == 3, "pop saca el 3 (el ultimo que entro)");
    pila.push(4);
    pila.pop(valor);
    revisar(valor == 4, "push(4) y pop saca el 4");
    pila.pop(valor);
    revisar(valor == 2, "pop saca el 2");
    pila.pop(valor);
    revisar(valor == 1 && pila.isEmpty(), "pop saca el 1 y queda vacia");
    if (!pila.pop(valor)) {
        std::cout << "  pop: la pila esta vacia" << std::endl;
    }

    prueba("Imprimir (de arriba hacia abajo)");
    std::cout << "  Pila vacia: ";
    pila.print();
    pila.push(5);
    pila.push(6);
    pila.push(7);
    std::cout << "  Despues de push 5, 6, 7: ";
    pila.print();
}

// ---------- Queue ----------

void probarQueue() {
    seccion("Queue");
    Queue<int> fila;
    int valor = -1;

    prueba("Fila vacia");
    revisar(fila.isEmpty(), "isEmpty() es verdadero");
    revisar(fila.size() == 0, "size() = 0");
    if (!fila.dequeue(valor)) {
        std::cout << "  dequeue: la fila esta vacia" << std::endl;
    }
    revisar(valor == -1, "dequeue sobre vacia regresa false y no cambia el valor");
    if (!fila.front(valor)) {
        std::cout << "  front: la fila esta vacia" << std::endl;
    }
    revisar(valor == -1, "front sobre vacia regresa false y no cambia el valor");

    prueba("Un solo elemento");
    fila.enqueue(10);
    revisar(fila.size() == 1, "enqueue(10) deja size() = 1");
    revisar(fila.front(valor) && valor == 10, "front ve el 10");
    revisar(fila.size() == 1, "front no saca el elemento");
    revisar(fila.dequeue(valor) && valor == 10, "dequeue saca el 10");
    revisar(fila.isEmpty(), "la fila queda vacia");

    prueba("Insertar y quitar varias veces en los extremos");
    fila.enqueue(1);
    fila.enqueue(2);
    fila.enqueue(3);
    revisar(fila.front(valor) && valor == 1, "enqueue(1,2,3) deja el 1 al frente");
    fila.dequeue(valor);
    revisar(valor == 1, "dequeue saca el 1 (el primero que entro)");
    fila.enqueue(4);
    fila.dequeue(valor);
    revisar(valor == 2, "enqueue(4) y dequeue saca el 2");
    fila.dequeue(valor);
    revisar(valor == 3, "dequeue saca el 3");
    fila.dequeue(valor);
    revisar(valor == 4 && fila.isEmpty(), "dequeue saca el 4 y queda vacia");
    if (!fila.dequeue(valor)) {
        std::cout << "  dequeue: la fila esta vacia" << std::endl;
    }
    fila.enqueue(8);
    revisar(fila.front(valor) && valor == 8, "enqueue(8) despues de vaciarla funciona");
    fila.dequeue(valor);

    prueba("Imprimir (del primero al ultimo)");
    std::cout << "  Fila vacia: ";
    fila.print();
    fila.enqueue(5);
    fila.enqueue(6);
    fila.enqueue(7);
    std::cout << "  Despues de enqueue 5, 6, 7: ";
    fila.print();
}

// ---------- DoublyLinkedList ----------

void probarDoublyLinkedList() {
    seccion("DoublyLinkedList");
    DoublyLinkedList<int> lista;

    prueba("Lista vacia");
    revisar(lista.isEmpty(), "isEmpty() es verdadero");
    revisar(lista.getHead() == nullptr && lista.getTail() == nullptr, "head y tail son nullptr");
    if (!lista.remove(lista.getHead())) {
        std::cout << "  remove: la lista esta vacia, no hay nodo que quitar" << std::endl;
    }
    lista.insertAfter(nullptr, 5);
    revisar(lista.isEmpty(), "insertAfter(nullptr, 5) no hace nada");
    revisar(!lista.isOrdenada(), "ordenada empieza en false");
    recorrer(lista, "(vacia)");

    prueba("Un solo elemento");
    lista.insertBack(10);
    revisar(lista.getHead() == lista.getTail(), "insertBack(10) en vacia: head y tail son el mismo nodo");
    recorrer(lista, "10");
    lista.remove(lista.getHead());
    std::cout << "  remove del unico nodo:" << std::endl;
    revisar(lista.getHead() == nullptr && lista.getTail() == nullptr, "head y tail vuelven a nullptr");
    recorrer(lista, "(vacia)");
    lista.insertFront(20);
    revisar(lista.getHead() == lista.getTail(), "insertFront(20) en vacia: head y tail son el mismo nodo");
    recorrer(lista, "20");

    prueba("insertAfter sobre el tail");
    lista.insertAfter(lista.getTail(), 30);
    std::cout << "  insertAfter(tail, 30):" << std::endl;
    revisar(lista.getTail()->data == 30, "el 30 es el nuevo tail");
    recorrer(lista, "20 30");
    lista.insertAfter(lista.getTail(), 40);
    std::cout << "  insertAfter(tail, 40):" << std::endl;
    recorrer(lista, "20 30 40");

    prueba("insertAfter en medio y en el head");
    lista.insertAfter(lista.getHead(), 25);
    std::cout << "  insertAfter(head, 25):" << std::endl;
    recorrer(lista, "20 25 30 40");
    lista.insertAfter(lista.getHead()->next->next, 35);
    std::cout << "  insertAfter(nodo del 30, 35):" << std::endl;
    recorrer(lista, "20 25 30 35 40");

    prueba("Insertar en los extremos varias veces");
    lista.insertFront(10);
    std::cout << "  insertFront(10):" << std::endl;
    recorrer(lista, "10 20 25 30 35 40");
    lista.insertBack(50);
    std::cout << "  insertBack(50):" << std::endl;
    recorrer(lista, "10 20 25 30 35 40 50");

    prueba("remove del head");
    lista.remove(lista.getHead());
    std::cout << "  remove(head):" << std::endl;
    revisar(lista.getHead()->prev == nullptr, "el nuevo head no tiene a nadie atras");
    recorrer(lista, "20 25 30 35 40 50");

    prueba("remove del tail");
    lista.remove(lista.getTail());
    std::cout << "  remove(tail):" << std::endl;
    revisar(lista.getTail()->next == nullptr, "el nuevo tail no tiene a nadie adelante");
    recorrer(lista, "20 25 30 35 40");

    prueba("remove de un nodo en medio");
    lista.remove(lista.getHead()->next->next);
    std::cout << "  remove(nodo del 30):" << std::endl;
    recorrer(lista, "20 25 35 40");

    prueba("Quitar todo desde los extremos hasta el unico nodo");
    lista.remove(lista.getTail());
    std::cout << "  remove(tail):" << std::endl;
    recorrer(lista, "20 25 35");
    lista.remove(lista.getHead());
    std::cout << "  remove(head):" << std::endl;
    recorrer(lista, "25 35");
    lista.remove(lista.getHead());
    std::cout << "  remove(head):" << std::endl;
    recorrer(lista, "35");
    lista.remove(lista.getTail());
    std::cout << "  remove del unico nodo (por tail):" << std::endl;
    recorrer(lista, "(vacia)");
    if (!lista.remove(lista.getHead())) {
        std::cout << "  remove: la lista esta vacia, no hay nodo que quitar" << std::endl;
    }

    prueba("Imprimir en los dos sentidos");
    std::cout << "  Vacia, printForward:  ";
    lista.printForward();
    std::cout << "  Vacia, printBackward: ";
    lista.printBackward();
    lista.insertBack(1);
    lista.insertBack(2);
    lista.insertBack(3);
    std::cout << "  1, 2, 3, printForward:  ";
    lista.printForward();
    std::cout << "  1, 2, 3, printBackward: ";
    lista.printBackward();

    prueba("Atributo ordenada");
    lista.setOrdenada(true);
    revisar(lista.isOrdenada(), "setOrdenada(true) lo cambia a true");
    lista.setOrdenada(false);
    revisar(!lista.isOrdenada(), "setOrdenada(false) lo regresa a false");
}

int main() {
    std::cout << "Pruebas de estructuras - Evidencia 2" << std::endl;
    std::cout << "Diego Contreras Alvarez, A00845716" << std::endl;

    probarLinkedList();
    probarStack();
    probarQueue();
    probarDoublyLinkedList();

    std::cout << std::endl << "==================== Resumen ====================" << std::endl;
    std::cout << "Revisiones: " << revisiones << ", fallas: " << fallas << std::endl;

    // regresa 1 si algo falló, para que se note también desde la terminal
    return fallas == 0 ? 0 : 1;
}
