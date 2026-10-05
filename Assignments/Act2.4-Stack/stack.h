// Diego Contreras
// A00845716

#pragma once

#include "node.h"
#include <stdexcept>

template <typename T>
class Stack {
    private:
        Node<T>* head; // el elemento de arriba de la pila
        int count;
    public:
        Stack() : head(nullptr), count(0) {}
        ~Stack();

        void push(const T& value);
        T pop();
        T top();
        int size();
        bool isEmpty();
};

// Borra todos los nodos que queden en la pila
template <typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) { // mientras quede alguna página
    pop();           // pop borra el nodo; el valor que regresa no se usa
}
}

// Pone un elemento arriba de la pila
template <typename T>
void Stack<T>::push(const T& value) {
    head = new Node<T>(value, head); // el nuevo queda arriba y apunta al que estaba antes
count++;                         
}

// Saca el elemento de arriba de la pila y lo regresa
template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {                                        // no hay página que cerrar
    throw std::out_of_range("El historial esta vacio");
}
T valor = head->data;                                   
Node<T>* viejo = head;
head = head->next;
delete viejo;
count--;
return valor;
}

// Regresa el elemento de arriba sin sacarlo
template <typename T>
T Stack<T>::top() {
    if (isEmpty()) {                                       
    throw std::out_of_range("El historial esta vacio"); 
}
return head->data;                                     
}

// Regresa cuantos elementos hay en la pila
template <typename T>
int Stack<T>::size() {
    return count;
}

// Regresa true si la pila no tiene elementos
template <typename T>
bool Stack<T>::isEmpty() {
    return count == 0;
}
