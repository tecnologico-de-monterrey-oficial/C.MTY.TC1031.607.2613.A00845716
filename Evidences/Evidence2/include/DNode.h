// Diego Contreras
// A00845716

// Nodo de la lista doblemente ligada. Viene de la Act 2.2.
// Guarda su dato y dos apuntadores: al nodo de atrás (prev) y al de adelante (next).

#pragma once

template <typename T>
struct DNode {
    T data;
    DNode<T>* prev;
    DNode<T>* next;

    DNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    DNode(const T& value, DNode<T>* prevNode, DNode<T>* nextNode)
        : data(value), prev(prevNode), next(nextNode) {}
};
