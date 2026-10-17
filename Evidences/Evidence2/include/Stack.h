// Diego Contreras
// A00845716

// Pila (el último que entra es el primero que sale).
// Por dentro usa una LinkedList y no toca nodos directamente:
// la parte de arriba de la pila es el head de la lista.

#pragma once
#include "LinkedList.h"

template <typename T>
class Stack {
private:
    LinkedList<T> lista;

public:
    // Pone un elemento arriba de la pila. O(1)
    void push(const T& value) { lista.insertFront(value); }

    // Saca el de arriba y lo deja en valor.
    // Regresa false si la pila está vacía. O(1)
    bool pop(T& valor) { return lista.removeFront(valor); }

    // Copia el de arriba en valor sin sacarlo.
    // Regresa false si la pila está vacía. O(1)
    bool peek(T& valor) const { return lista.getFront(valor); }

    int size() const { return lista.size(); }
    bool isEmpty() const { return lista.isEmpty(); }
};
