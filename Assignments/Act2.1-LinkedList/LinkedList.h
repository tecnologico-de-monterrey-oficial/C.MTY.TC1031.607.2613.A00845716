// Diego Contreras Alvarez
// A00845716
#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();

    void addFirst(T data);
    void addLast(T data);
    void insert(int pos, T data);
    bool deleteData(T data);
    bool deleteAt(int pos);
    T getData(int pos);
    void updateData(T oldData, T newData);
    void updateAt(int pos, T newData);
    int findData(T data);

    T& operator[](int pos);
    LinkedList<T>& operator=(const LinkedList<T>& other);

    void print();
    void clear();
    int getSize() { return size; }
};

template <typename T>
void LinkedList<T>::addFirst(T data) {
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
        addFirst(data);
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

template <typename T>
void LinkedList<T>::addLast(T data) {
    // 1. si la lista está vacía, el nuevo nodo también es el primero
    if (head == nullptr) {
        addFirst(data);
        return;
    }
    // 2. caminar hasta el último nodo
    Node<T>* aux = head;
    while (aux->next != nullptr) {
        aux = aux->next;
    }
    // 3. conectar el último con el nodo nuevo
    aux->next = new Node<T>(data);
    size++;
}

template <typename T>
void LinkedList<T>::clear() {
    Node<T>* aux = head;
    while (aux != nullptr) {
        // guardar el siguiente antes de borrar el actual
        Node<T>* siguiente = aux->next;
        delete aux;
        aux = siguiente;
    }
    // dejar la lista en estado de vacía
    head = nullptr;
    size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
bool LinkedList<T>::deleteData(T data) {
    // 1. si la lista está vacía no hay nada que borrar
    if (head == nullptr) {
        return false;
    }
    // 2. si el elemento está en el primer nodo
    if (head->data == data) {
        Node<T>* borrar = head;
        head = head->next;
        delete borrar;
        size--;
        return true;
    }
    // 3. caminar hasta el nodo ANTERIOR al que se quiere borrar
    Node<T>* aux = head;
    while (aux->next != nullptr && aux->next->data != data) {
        aux = aux->next;
    }
    // 4. si llegamos al final, el elemento no está
    if (aux->next == nullptr) {
        return false;
    }
    // 5. saltarse el nodo y borrarlo
    Node<T>* borrar = aux->next;
    aux->next = borrar->next;
    delete borrar;
    size--;
    return true;
}

template <typename T>
bool LinkedList<T>::deleteAt(int pos) {
    // 1. validar que la posición exista
    if (pos < 0 || pos >= size) {
        return false;
    }
    Node<T>* borrar;
    // 2. si es el primero, se mueve head
    if (pos == 0) {
        borrar = head;
        head = head->next;
    } else {
        // 3. caminar hasta el nodo ANTERIOR a pos
        Node<T>* aux = head;
        for (int i = 0; i < pos - 1; i++) {
            aux = aux->next;
        }
        // 4. saltarse el nodo
        borrar = aux->next;
        aux->next = borrar->next;
    }
    // 5. liberar memoria y actualizar tamaño
    delete borrar;
    size--;
    return true;
}

template <typename T>
T LinkedList<T>::getData(int pos) {
    // 1. validar que la posición exista
    if (pos < 0 || pos >= size) {
        throw out_of_range("Posicion invalida");
    }
    // 2. caminar hasta el nodo de esa posición
    Node<T>* aux = head;
    for (int i = 0; i < pos; i++) {
        aux = aux->next;
    }
    // 3. regresar su dato
    return aux->data;
}

template <typename T>
void LinkedList<T>::updateData(T oldData, T newData) {
    // 1. recorrer la lista buscando el primer nodo con oldData
    Node<T>* aux = head;
    while (aux != nullptr) {
        if (aux->data == oldData) {
            // 2. encontrado, se cambia el dato y se sale
            aux->data = newData;
            return;
        }
        aux = aux->next;
    }
    // 3. si se terminó la lista, el dato no estaba
    throw out_of_range("Elemento no encontrado");
}

template <typename T>
void LinkedList<T>::updateAt(int pos, T newData) {
    // 1. validar que la posición exista
    if (pos < 0 || pos >= size) {
        throw out_of_range("Posicion invalida");
    }
    // 2. caminar hasta el nodo de esa posición
    Node<T>* aux = head;
    for (int i = 0; i < pos; i++) {
        aux = aux->next;
    }
    // 3. cambiar su dato
    aux->data = newData;
}

template <typename T>
int LinkedList<T>::findData(T data) {
    // 1. recorrer la lista llevando la cuenta de la posición
    Node<T>* aux = head;
    int pos = 0;
    while (aux != nullptr) {
        if (aux->data == data) {
            // 2. encontrado, se regresa su posición
            return pos;
        }
        aux = aux->next;
        pos++;
    }
    // 3. no se encontró
    return -1;
}

template <typename T>
T& LinkedList<T>::operator[](int pos) {
    // 1. validar que la posición exista
    if (pos < 0 || pos >= size) {
        throw out_of_range("Posicion invalida");
    }
    // 2. caminar hasta el nodo de esa posición
    Node<T>* aux = head;
    for (int i = 0; i < pos; i++) {
        aux = aux->next;
    }
    // 3. regresar el dato por referencia
    return aux->data;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    // 1. si es la misma lista (a = a) no hay nada que hacer
    if (this == &other) {
        return *this;
    }
    // 2. borrar los nodos que tenía esta lista
    clear();
    // 3. recorrer la otra lista y copiar cada dato al final
    Node<T>* aux = other.head;
    while (aux != nullptr) {
        addLast(aux->data);
        aux = aux->next;
    }
    // 4. regresar esta lista
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), size(0) {
    // arrancar vacía y copiar con el operador =
    *this = other;
}

#endif /* LinkedList_h */
