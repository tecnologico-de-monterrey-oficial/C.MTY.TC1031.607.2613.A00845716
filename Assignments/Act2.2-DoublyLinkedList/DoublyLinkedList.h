// Diego Contreras Alvarez
// Matrícula:A00845716
// Fecha: 9 de octubre de 2026
// Descripción: lista doblemente ligada con template. Cada nodo conoce al de
// atrás y al de adelante, y la lista guarda el primero (head), el último (tail)
// y cuántos elementos tiene (size). La implementación va en este mismo archivo
// porque los templates necesitan verla al compilar.
#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "Node.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    void validarIndice(int index) const;
    Node<T>* getNode(int index) const;
    void removeNode(Node<T>* borrar);
    void copiarDe(const DoublyLinkedList<T>& other);
    static Node<T>* mergeSort(Node<T>* inicio);
    static Node<T>* merge(Node<T>* a, Node<T>* b);

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();

    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteData(T data);
    bool deleteAt(int index);
    T getData(int index) const;
    void updateData(T oldData, T newData);
    void updateAt(int index, T newData);
    int findData(T data) const;

    T& operator[](int index);
    const T& operator[](int index) const;
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);

    void clear();
    void sort();
    void duplicate();
    void removeDuplicates();
    void print() const;

    int getSize() const { return size; }      // O(1)
    bool isEmpty() const { return size == 0; } // O(1)

    template <typename U>
    friend ostream& operator<<(ostream& os, const DoublyLinkedList<U>& lista);
};

// ---------------------------------------------------------------------------
// Funciones de apoyo (privadas)
// ---------------------------------------------------------------------------

// Lanza out_of_range si el índice no existe en la lista. O(1)
template <typename T>
void DoublyLinkedList<T>::validarIndice(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Indice invalido");
    }
}

// Regresa el nodo en la posición index (ya validada). O(n)
// Como podemos caminar en los dos sentidos, empezamos por el extremo más
// cercano: así a lo mucho recorremos la mitad de la lista.
template <typename T>
Node<T>* DoublyLinkedList<T>::getNode(int index) const {
    Node<T>* aux;
    if (index < size / 2) {
        // está en la primera mitad, caminamos desde head hacia adelante
        aux = head;
        for (int i = 0; i < index; i++) {
            aux = aux->next;
        }
    } else {
        // está en la segunda mitad, caminamos desde tail hacia atrás
        aux = tail;
        for (int i = size - 1; i > index; i--) {
            aux = aux->prev;
        }
    }
    return aux;
}

// Saca un nodo de la lista, libera su memoria y baja size. O(1)
// La usan deleteData, deleteAt y removeDuplicates.
//
//   antes:   [A] <-> [borrar] <-> [B]
//   después: [A] <-> [B]
template <typename T>
void DoublyLinkedList<T>::removeNode(Node<T>* borrar) {
    // 1. el de atrás (A) ahora apunta hacia adelante a B
    if (borrar->prev != nullptr) {
        borrar->prev->next = borrar->next;
    } else {
        // no hay nadie atrás: borrar era head, el nuevo head es B
        head = borrar->next;
    }
    // 2. el de adelante (B) ahora apunta hacia atrás a A
    if (borrar->next != nullptr) {
        borrar->next->prev = borrar->prev;
    } else {
        // no hay nadie adelante: borrar era tail, el nuevo tail es A
        tail = borrar->prev;
    }
    // 3. ya nadie apunta a borrar, se puede liberar
    // (si era el único nodo, los dos casos de arriba dejan head = tail = nullptr)
    delete borrar;
    size--;
}

// Copia los datos de otra lista al final de esta, en el mismo orden. O(n)
template <typename T>
void DoublyLinkedList<T>::copiarDe(const DoublyLinkedList<T>& other) {
    Node<T>* aux = other.head;
    while (aux != nullptr) {
        // se crea un nodo nuevo por cada dato, no se comparten nodos
        addLast(aux->data);
        aux = aux->next;
    }
}

// ---------------------------------------------------------------------------
// Constructor de copia, destructor y operador =
// ---------------------------------------------------------------------------

// Constructor de copia: arranca vacía y copia nodo por nodo. O(n)
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), size(0) {
    copiarDe(other);
}

// Destructor: libera todos los nodos. O(n)
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// Copia profunda. O(n + m), n = nodos que se borran, m = nodos que se copian
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    // 1. si es la misma lista (a = a) no hay nada que hacer; si siguiéramos,
    //    clear() borraría los nodos que queremos copiar
    if (this == &other) {
        return *this;
    }
    // 2. liberar los nodos que tenía esta lista
    clear();
    // 3. copiar cada dato de la otra lista en nodos nuevos
    copiarDe(other);
    // 4. regresar esta lista para poder encadenar a = b = c
    return *this;
}

// ---------------------------------------------------------------------------
// Agregar
// ---------------------------------------------------------------------------

// Inserta al principio. O(1)
template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    // el nuevo no tiene a nadie atrás y adelante tiene al head actual
    Node<T>* nuevo = new Node<T>(data, nullptr, head);
    if (head != nullptr) {
        // el head viejo ahora tiene al nuevo atrás
        head->prev = nuevo;
    } else {
        // la lista estaba vacía: el nuevo también es el último
        tail = nuevo;
    }
    head = nuevo;
    size++;
}

// Inserta al final. O(1) gracias a que guardamos tail
template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // el nuevo tiene atrás al tail actual y adelante a nadie
    Node<T>* nuevo = new Node<T>(data, tail, nullptr);
    if (tail != nullptr) {
        // el tail viejo ahora tiene al nuevo adelante
        tail->next = nuevo;
    } else {
        // la lista estaba vacía: el nuevo también es el primero
        head = nuevo;
    }
    tail = nuevo;
    size++;
}

// Inserta DESPUÉS de la posición index. O(n)
// Índices válidos: 0 a size - 1. En una lista vacía no hay ningún índice
// válido, así que lanza out_of_range (para eso están addFirst y addLast).
//
//   antes:   [actual] <-> [siguiente]
//   después: [actual] <-> [nuevo] <-> [siguiente]
template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // 1. validar que la posición exista
    validarIndice(index);
    // 2. si es después del último, es lo mismo que agregar al final
    //    (así tail se actualiza en un solo lugar)
    if (index == size - 1) {
        addLast(data);
        return;
    }
    // 3. llegar al nodo de esa posición; sabemos que tiene un siguiente
    Node<T>* actual = getNode(index);
    Node<T>* siguiente = actual->next;
    // 4. el nuevo nodo ya nace apuntando a sus dos vecinos
    Node<T>* nuevo = new Node<T>(data, actual, siguiente);
    // 5. ahora los vecinos apuntan al nuevo, cada uno desde su lado
    actual->next = nuevo;    // actual -> nuevo
    siguiente->prev = nuevo; // nuevo <- siguiente
    size++;
}

// ---------------------------------------------------------------------------
// Borrar
// ---------------------------------------------------------------------------

// Borra la primera vez que aparece data. O(n)
template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    // 1. buscar el primer nodo con ese dato
    Node<T>* aux = head;
    while (aux != nullptr && aux->data != data) {
        aux = aux->next;
    }
    // 2. si llegamos al final (o la lista estaba vacía) no estaba
    if (aux == nullptr) {
        return false;
    }
    // 3. sacarlo de la lista (ver removeNode)
    removeNode(aux);
    return true;
}

// Borra el nodo en la posición index. O(n)
// A diferencia de la lista simple, no hace falta llegar al nodo de ANTES:
// el nodo a borrar ya sabe quién está atrás gracias a prev.
template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    // 1. validar sin lanzar excepción; aquí se regresa false
    if (index < 0 || index >= size) {
        return false;
    }
    // 2. llegar al nodo a borrar (desde el extremo más cercano)
    Node<T>* borrar = getNode(index);
    // 3. reconectar a sus vecinos entre sí y liberarlo; removeNode cubre
    //    los casos de head, tail y lista de un solo elemento
    removeNode(borrar);
    return true;
}

// Deja la lista vacía y libera todos los nodos. O(n)
template <typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* aux = head;
    while (aux != nullptr) {
        // guardar el siguiente antes de borrar el actual
        Node<T>* siguiente = aux->next;
        delete aux;
        aux = siguiente;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// ---------------------------------------------------------------------------
// Consultar y actualizar
// ---------------------------------------------------------------------------

// Regresa el dato de la posición index. O(n)
template <typename T>
T DoublyLinkedList<T>::getData(int index) const {
    validarIndice(index);
    return getNode(index)->data;
}

// Cambia la primera vez que aparece oldData por newData. O(n)
template <typename T>
void DoublyLinkedList<T>::updateData(T oldData, T newData) {
    Node<T>* aux = head;
    while (aux != nullptr) {
        if (aux->data == oldData) {
            aux->data = newData;
            return;
        }
        aux = aux->next;
    }
    // se terminó la lista y no apareció
    throw out_of_range("Elemento no encontrado");
}

// Cambia el dato de la posición index. O(n)
template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T newData) {
    validarIndice(index);
    getNode(index)->data = newData;
}

// Regresa la posición de la primera vez que aparece data, o -1. O(n)
template <typename T>
int DoublyLinkedList<T>::findData(T data) const {
    Node<T>* aux = head;
    int pos = 0;
    while (aux != nullptr) {
        if (aux->data == data) {
            return pos;
        }
        aux = aux->next;
        pos++;
    }
    return -1;
}

// Regresa el dato por referencia para poder leerlo y cambiarlo: lista[2] = 5. O(n)
template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    validarIndice(index);
    return getNode(index)->data;
}

// Versión para listas const: solo deja leer. O(n)
template <typename T>
const T& DoublyLinkedList<T>::operator[](int index) const {
    validarIndice(index);
    return getNode(index)->data;
}

// ---------------------------------------------------------------------------
// Ordenar, duplicar y quitar repetidos
// ---------------------------------------------------------------------------

// Junta dos cadenas ya ordenadas en una sola ordenada. O(a + b)
// Solo usa next; los prev se arreglan al final de sort().
template <typename T>
Node<T>* DoublyLinkedList<T>::merge(Node<T>* a, Node<T>* b) {
    Node<T>* inicio = nullptr; // primer nodo del resultado
    Node<T>* ultimo = nullptr; // último nodo que ya pegamos al resultado
    while (a != nullptr && b != nullptr) {
        // tomar el menor de los dos frentes; si son iguales se toma el de a
        // para que los iguales conserven su orden original
        Node<T>* menor;
        if (b->data < a->data) {
            menor = b;
            b = b->next;
        } else {
            menor = a;
            a = a->next;
        }
        // pegarlo al final del resultado
        if (ultimo == nullptr) {
            inicio = menor;
        } else {
            ultimo->next = menor;
        }
        ultimo = menor;
    }
    // lo que sobre de una de las dos cadenas ya está ordenado, se pega completo
    Node<T>* resto = (a != nullptr) ? a : b;
    if (ultimo == nullptr) {
        inicio = resto;
    } else {
        ultimo->next = resto;
    }
    return inicio;
}

// Ordena la cadena que empieza en inicio y regresa su nuevo primer nodo.
template <typename T>
Node<T>* DoublyLinkedList<T>::mergeSort(Node<T>* inicio) {
    // 0 o 1 nodo: ya está ordenada
    if (inicio == nullptr || inicio->next == nullptr) {
        return inicio;
    }
    // 1. encontrar la mitad: lento avanza de 1 en 1 y rapido de 2 en 2,
    //    cuando rapido llega al final, lento está a la mitad
    Node<T>* lento = inicio;
    Node<T>* rapido = inicio->next;
    while (rapido != nullptr && rapido->next != nullptr) {
        lento = lento->next;
        rapido = rapido->next->next;
    }
    // 2. cortar la cadena en dos
    Node<T>* mitad = lento->next;
    lento->next = nullptr;
    // 3. ordenar cada mitad y juntarlas
    return merge(mergeSort(inicio), mergeSort(mitad));
}

// Ordena de menor a mayor con merge sort sobre los nodos (no copia datos).
// Complejidad: O(n log n) en tiempo, porque la lista se parte a la mitad
// log n veces y en cada nivel se recorren los n nodos al juntar.
// Memoria extra: O(log n) por las llamadas recursivas; no se crean nodos.
// (Insertion sort sería O(n^2) en el peor caso.)
template <typename T>
void DoublyLinkedList<T>::sort() {
    // 1. ordenar usando solo next
    head = mergeSort(head);
    // 2. recorrer una vez para arreglar todos los prev y encontrar el tail
    Node<T>* anterior = nullptr;
    Node<T>* aux = head;
    while (aux != nullptr) {
        aux->prev = anterior;
        anterior = aux;
        aux = aux->next;
    }
    tail = anterior;
}

// Hace que cada elemento aparezca dos veces seguidas: 1,2,3 -> 1,1,2,2,3,3. O(n)
// Por cada nodo se crea una copia y se mete justo después de él.
//
//   antes:   [actual] <-> [siguiente]
//   después: [actual] <-> [copia] <-> [siguiente]
template <typename T>
void DoublyLinkedList<T>::duplicate() {
    Node<T>* actual = head;
    while (actual != nullptr) {
        Node<T>* siguiente = actual->next;
        // 1. la copia nace apuntando a actual (atrás) y a siguiente (adelante)
        Node<T>* copia = new Node<T>(actual->data, actual, siguiente);
        // 2. actual ahora apunta hacia adelante a la copia
        actual->next = copia;
        // 3. siguiente ahora apunta hacia atrás a la copia;
        //    si no había siguiente, la copia es el nuevo tail
        if (siguiente != nullptr) {
            siguiente->prev = copia;
        } else {
            tail = copia;
        }
        size++;
        // 4. saltar al siguiente ORIGINAL; si avanzáramos solo un paso
        //    caeríamos en la copia y duplicaríamos sin parar
        actual = siguiente;
    }
}

// Ordena y luego deja una sola vez cada valor. O(n log n) por el sort;
// la pasada para borrar es O(n).
template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    // 1. al ordenar, los repetidos quedan juntos
    sort();
    // 2. si el de adelante es igual al actual, se borra el de adelante;
    //    no se avanza porque el nuevo de adelante también podría ser igual
    Node<T>* actual = head;
    while (actual != nullptr && actual->next != nullptr) {
        if (actual->next->data == actual->data) {
            removeNode(actual->next);
        } else {
            actual = actual->next;
        }
    }
}

// ---------------------------------------------------------------------------
// Imprimir
// ---------------------------------------------------------------------------

// Escribe la lista de head a tail (con next) y de tail a head (con prev).
// Si los prev estuvieran mal, la segunda línea no saldría al revés de la primera. O(n)
template <typename U>
ostream& operator<<(ostream& os, const DoublyLinkedList<U>& lista) {
    os << "head -> tail: ";
    if (lista.head == nullptr) {
        os << "(vacia)";
    }
    for (Node<U>* aux = lista.head; aux != nullptr; aux = aux->next) {
        os << aux->data;
        if (aux->next != nullptr) {
            os << " <-> ";
        }
    }
    os << endl << "tail -> head: ";
    if (lista.tail == nullptr) {
        os << "(vacia)";
    }
    for (Node<U>* aux = lista.tail; aux != nullptr; aux = aux->prev) {
        os << aux->data;
        if (aux->prev != nullptr) {
            os << " <-> ";
        }
    }
    os << endl;
    return os;
}

// Imprime en pantalla en los dos sentidos. O(n)
template <typename T>
void DoublyLinkedList<T>::print() const {
    cout << *this;
}

#endif /* DoublyLinkedList_h */
