// Diego Contreras Alvarez
// Matrícula: A00845716
// Fecha: 9 de octubre de 2026
// Descripción: nodo de la lista doblemente ligada. Guarda su dato y dos
// apuntadores: uno al nodo de atrás (prev) y otro al de adelante (next).
#pragma once

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    Node(const T& value, Node<T>* prevNode, Node<T>* nextNode)
        : data(value), prev(prevNode), next(nextNode) {}
};
