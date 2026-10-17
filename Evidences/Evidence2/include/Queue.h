// Diego Contreras
// A00845716

// Fila (el primero que entra es el primero que sale).
// Por dentro usa una LinkedList y no toca nodos directamente:
// se forma por el tail de la lista y se atiende por el head.
// Como la lista tiene tail, formarse al final también es O(1).

#pragma once
#include "LinkedList.h"

template <typename T>
class Queue {
private:
    LinkedList<T> lista;

public:
    // Mete un elemento al final de la fila. O(1)
    void enqueue(const T& value) { lista.insertBack(value); }

    // Saca el primero de la fila y lo deja en valor.
    // Regresa false si la fila está vacía. O(1)
    bool dequeue(T& valor) { return lista.removeFront(valor); }

    // Copia el primero de la fila en valor sin sacarlo.
    // Regresa false si la fila está vacía. O(1)
    bool front(T& valor) const { return lista.getFront(valor); }

    int size() const { return lista.size(); }
    bool isEmpty() const { return lista.isEmpty(); }

    // Imprime del primero de la fila al último. O(n)
    void print() const { lista.print(); }
};
