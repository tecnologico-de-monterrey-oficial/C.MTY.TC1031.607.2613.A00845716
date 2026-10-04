// Diego Contreras Alvarez
// A00845716
#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    void push_front(T data);
    void push_back(T data);
    void print();
    void insert(int pos, T data);
};

template <typename T>
void LinkedList<T>::push_front(T data) {
    // crear un nodo nuevo
    Node<T>* node = new Node<T>(data);
    // actualizo el next del nodo nuevo para que apunte a head
    node->next = head;
    // actualizo head
    head = node;
    size++;
}

template <typename T>
void LinkedList<T>::print() {
    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;
    // recorremos la lista mientras aux sea diferente de nullptr
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << "-";
        }
    }
    cout << endl;
}

template <typename T>
void LinkedList<T>::insert(int pos, T data) {
    // 1. validar que la posición exista
    if (pos < 0 || pos > size) {
        throw out_of_range("Posicion invalida");
    }
    // 2. si es al inicio, ya tenemos función para eso
    if (pos == 0) {
        push_front(data);
        return;
    }
    // 3. caminar hasta el nodo ANTERIOR a pos
    Node<T>* aux = head;
    for (int i = 0; i < pos - 1; i++) {
        aux = aux->next;
    }
    // 4. crear el nodo apuntando al siguiente y reconectar
    Node<T>* node = new Node<T>(data, aux->next);
    aux->next = node;
    size++;
}









#endif /* LinkedList_h */