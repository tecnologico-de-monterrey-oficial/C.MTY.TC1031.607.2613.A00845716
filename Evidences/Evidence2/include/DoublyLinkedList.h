// Diego Contreras
// A00845716

// Lista doblemente ligada. Viene de la Act 2.2.
// Cada nodo conoce al de atrás y al de adelante, y la lista guarda el primero
// (head), el último (tail) y cuántos nodos hay. Se puede recorrer en los dos
// sentidos con getHead()/next y con getTail()/prev.

#pragma once
#include "DNode.h"
#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    DNode<T>* head;
    DNode<T>* tail;
    int count;
    bool ordenada = false;   // se usa en la Fase 8

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinkedList();

    // La lista es dueña de sus nodos, así que no se deja copiar.
    // Si se copiara, las dos listas borrarían los mismos nodos al final.
    DoublyLinkedList(const DoublyLinkedList<T>& other) = delete;
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other) = delete;

    void insertFront(const T& valor);
    void insertBack(const T& valor);
    void insertAfter(DNode<T>* nodo, const T& valor);
    bool remove(DNode<T>* nodo);

    void printForward() const;
    void printBackward() const;

    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
    DNode<T>* getHead() const { return head; }
    DNode<T>* getTail() const { return tail; }

    bool isOrdenada() const { return ordenada; }
    void setOrdenada(bool valor) { ordenada = valor; }
};

// Inserta al principio. O(1)
template <typename T>
void DoublyLinkedList<T>::insertFront(const T& valor) {
    // el nuevo no tiene a nadie atrás y adelante tiene al head actual
    DNode<T>* nuevo = new DNode<T>(valor, nullptr, head);
    if (head != nullptr) {
        // el head viejo ahora tiene al nuevo atrás
        head->prev = nuevo;
    } else {
        // la lista estaba vacía: el nuevo también es el último
        tail = nuevo;
    }
    head = nuevo;
    count++;
}

// Inserta al final. O(1) gracias a que guardamos tail
template <typename T>
void DoublyLinkedList<T>::insertBack(const T& valor) {
    // el nuevo tiene atrás al tail actual y adelante a nadie
    DNode<T>* nuevo = new DNode<T>(valor, tail, nullptr);
    if (tail != nullptr) {
        // el tail viejo ahora tiene al nuevo adelante
        tail->next = nuevo;
    } else {
        // la lista estaba vacía: el nuevo también es el primero
        head = nuevo;
    }
    tail = nuevo;
    count++;
}

// Inserta un nodo nuevo justo después de nodo. O(1)
// Si nodo es nullptr no hace nada.
//
//   antes:   [nodo] <-> [siguiente]
//   después: [nodo] <-> [nuevo] <-> [siguiente]
template <typename T>
void DoublyLinkedList<T>::insertAfter(DNode<T>* nodo, const T& valor) {
    if (nodo == nullptr) {
        return;
    }
    // 1. si nodo es el último, es lo mismo que insertar al final
    //    (así tail se actualiza en un solo lugar)
    if (nodo == tail) {
        insertBack(valor);
        return;
    }
    // 2. el nuevo nodo ya nace apuntando a sus dos vecinos
    DNode<T>* siguiente = nodo->next;
    DNode<T>* nuevo = new DNode<T>(valor, nodo, siguiente);
    // 3. ahora los vecinos apuntan al nuevo, cada uno desde su lado
    nodo->next = nuevo;       // nodo -> nuevo
    siguiente->prev = nuevo;  // nuevo <- siguiente
    count++;
}

// Saca nodo de la lista y libera su memoria. O(1)
// Regresa false si nodo es nullptr.
// Se revisa cada caso por separado porque aquí es donde más fácil se
// rompen los apuntadores prev.
template <typename T>
bool DoublyLinkedList<T>::remove(DNode<T>* nodo) {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo == head && nodo == tail) {
        // Caso 1: es el único nodo. La lista queda vacía.
        head = nullptr;
        tail = nullptr;
    } else if (nodo == head) {
        // Caso 2: es el primero. El segundo pasa a ser head
        // y ya no tiene a nadie atrás.
        //   [nodo] <-> [B] ...   ->   [B] ...
        head = nodo->next;
        head->prev = nullptr;
    } else if (nodo == tail) {
        // Caso 3: es el último. El penúltimo pasa a ser tail
        // y ya no tiene a nadie adelante.
        //   ... [A] <-> [nodo]   ->   ... [A]
        tail = nodo->prev;
        tail->next = nullptr;
    } else {
        // Caso 4: está en medio. Sus dos vecinos se apuntan entre sí.
        //   [A] <-> [nodo] <-> [B]   ->   [A] <-> [B]
        nodo->prev->next = nodo->next;
        nodo->next->prev = nodo->prev;
    }

    delete nodo;
    count--;
    return true;
}

// Imprime de head a tail usando next. O(n)
template <typename T>
void DoublyLinkedList<T>::printForward() const {
    if (head == nullptr) {
        std::cout << "(vacia)";
    }
    for (DNode<T>* aux = head; aux != nullptr; aux = aux->next) {
        std::cout << aux->data;
        if (aux->next != nullptr) {
            std::cout << " <-> ";
        }
    }
    std::cout << std::endl;
}

// Imprime de tail a head usando prev. O(n)
// Si algún prev estuviera mal, no saldría al revés que printForward.
template <typename T>
void DoublyLinkedList<T>::printBackward() const {
    if (tail == nullptr) {
        std::cout << "(vacia)";
    }
    for (DNode<T>* aux = tail; aux != nullptr; aux = aux->prev) {
        std::cout << aux->data;
        if (aux->prev != nullptr) {
            std::cout << " <-> ";
        }
    }
    std::cout << std::endl;
}

// Destructor: libera todos los nodos. O(n)
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    DNode<T>* aux = head;
    while (aux != nullptr) {
        // guardar el siguiente antes de borrar el actual
        DNode<T>* siguiente = aux->next;
        delete aux;
        aux = siguiente;
    }
}
