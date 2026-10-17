// Diego Contreras
// A00845716

// Nodo de la lista ligada: guarda un dato y apunta al siguiente nodo.
// Viene de la Act 2.1.

#pragma once

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(const T& value) : data(value), next(nullptr) {}
    Node(const T& value, Node<T>* nextNode) : data(value), next(nextNode) {}
};
