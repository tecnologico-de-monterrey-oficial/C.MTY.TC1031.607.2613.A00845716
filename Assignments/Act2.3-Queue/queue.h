// Diego Contreras
// A00845716

#pragma once

#include "node.h"
#include <stdexcept>

template <typename T>
class Queue {
    private:
        Node <T>* head;
        Node <T>* tail;
        int count;
    public:
        Queue() : head(nullptr), tail(nullptr), count(0) {}
        ~Queue();

        void push(const T& value);
        T pop();
        T front();
        int size();
        bool isEmpty();
};

// Borra todos los nodos que queden en la fila
template <typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) { // mientras quede alguien
    pop();           // pop borra el nodo; el valor que regresa no se usa
}
}

// Mete un elemento al final de la fila
template <typename T>
void Queue<T>::push(const T& value) {
    Node<T>* nuevo = new Node<T>(value); // nodo nuevo, su next ya es nullptr
    if (head == nullptr) {               
    head = nuevo;                    
    tail = nuevo;                    
    } else {
    tail->next = nuevo;              
    tail = nuevo;                    
    }
    count++;                             // hay uno más en la fila
}

// Saca el primer elemento de la fila y lo regresa
template <typename T>
T Queue<T>::pop() {
    if (isEmpty()) {                                   // no hay a quién sacar
    throw std::out_of_range("La fila esta vacia");
}
T valor = head->data;                              
Node<T>* viejo = head;                             // guardamos el nodo a borrar
head = head->next;                                
delete viejo;                                      // liberamos la memoria
count--;                                           
if (head == nullptr) {                             
    tail = nullptr;                                
}
return valor;
}

// Regresa el primer elemento sin sacarlo
template <typename T>
T Queue<T>::front() {
    if (isEmpty()) {                                   // no hay a quién ver
    throw std::out_of_range("La fila esta vacia"); // la atrapa el main
}
return head->data;                                 // el primero, sin moverlo
}

// Regresa cuantos elementos hay en la fila
template <typename T>
int Queue<T>::size() {
    return count; // ya sabemos cuántos hay, no hace falta recorrer
}

// Regresa true si la fila no tiene elementos
template <typename T>
bool Queue<T>::isEmpty() {
    return count == 0; // true si no hay nadie en la fila
}
