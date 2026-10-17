// Diego Contreras
// A00845716

// Lista ligada simple con head y tail. Viene de la Act 2.1.
// Se le agregó tail para que insertar al final sea O(1) y no tenga que
// recorrer toda la lista. Así la Pila y la Fila quedan en O(1).

#pragma once
#include "Node.h"
#include <iostream>

template <typename T>
class LinkedList {
private:
    Node<T>* head;   // primer nodo
    Node<T>* tail;   // último nodo
    int count;       // cuántos nodos hay

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~LinkedList();

    // La lista es dueña de sus nodos, así que no se deja copiar.
    // Si se copiara, las dos listas borrarían los mismos nodos al final.
    LinkedList(const LinkedList<T>& other) = delete;
    LinkedList<T>& operator=(const LinkedList<T>& other) = delete;

    void insertFront(const T& data);
    void insertBack(const T& data);
    bool removeFront(T& valor);
    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
    void print() const;
};

template <typename T>
void LinkedList<T>::insertFront(const T& data) {
    // 1. crear el nodo nuevo apuntando al que era el primero
    Node<T>* node = new Node<T>(data, head);
    // 2. el nodo nuevo ahora es el primero
    head = node;
    // 3. si la lista estaba vacía, también es el último
    if (tail == nullptr) {
        tail = node;
    }
    count++;
}

template <typename T>
void LinkedList<T>::insertBack(const T& data) {
    // 1. crear el nodo nuevo, que no apunta a nadie porque va al final
    Node<T>* node = new Node<T>(data);
    if (tail == nullptr) {
        // 2. si la lista está vacía, head y tail apuntan al mismo nodo
        head = node;
        tail = node;
    } else {
        // 3. si no, se cuelga después del último y pasa a ser el último
        tail->next = node;
        tail = node;
    }
    count++;
}

template <typename T>
bool LinkedList<T>::removeFront(T& valor) {
    // 1. si la lista está vacía no hay nada que quitar
    if (head == nullptr) {
        return false;
    }
    // 2. guardar el dato del primero para regresarlo
    Node<T>* borrar = head;
    valor = borrar->data;
    // 3. el segundo pasa a ser el primero
    head = head->next;
    // 4. si ya no quedan nodos, tail también vuelve a nullptr
    if (head == nullptr) {
        tail = nullptr;
    }
    delete borrar;
    count--;
    return true;
}

template <typename T>
void LinkedList<T>::print() const {
    // recorrer la lista desde head hasta el final
    Node<T>* aux = head;
    while (aux != nullptr) {
        std::cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            std::cout << "-";
        }
    }
    std::cout << std::endl;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* aux = head;
    while (aux != nullptr) {
        // guardar el siguiente antes de borrar el actual
        Node<T>* siguiente = aux->next;
        delete aux;
        aux = siguiente;
    }
}
