// Diego Contreras
// A00845716

// Lista doblemente ligada. Viene de la Act 2.2.
// Cada nodo conoce al de atrás y al de adelante, y la lista guarda el primero
// (head), el último (tail) y cuántos nodos hay. Se puede recorrer en los dos
// sentidos con getHead()/next y con getTail()/prev.

#pragma once
#include "DNode.h"
#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    DNode<T>* head;
    DNode<T>* tail;
    int count;
    bool ordenada = false;   // true después de ordenar con mergeSort

    // Partes del merge sort (ver mergeSort más abajo)
    static DNode<T>* dividir(DNode<T>* inicio);
    static DNode<T>* mezclar(DNode<T>* a, DNode<T>* b, long long& comparaciones);
    static DNode<T>* mergeSortRec(DNode<T>* inicio, int profundidad,
    long long& comparaciones, int& maxProfundidad);

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinkedList();

    // La lista es dueña de sus nodos, así que no se deja copiar.
    // Si se copiara, las dos listas borrarían los mismos nodos al final.
    DoublyLinkedList(const DoublyLinkedList<T>& other) = delete;
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other) = delete;

    void insertFront(const T& valor);
    void insertBack(const T& valor);
    void insertAfter(DNode<T>* nodo, const T& valor);
    bool remove(DNode<T>* nodo);
    void clear();

    void printForward() const;
    void printBackward() const;

    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
    DNode<T>* getHead() const { return head; }
    DNode<T>* getTail() const { return tail; }

    bool isOrdenada() const { return ordenada; }
    void setOrdenada(bool valor) { ordenada = valor; }

    void mergeSort(long long& comparaciones, int& maxProfundidad);
};

// Inserta al principio. O(1)
template <typename T>
void DoublyLinkedList<T>::insertFront(const T& valor) {
    // el nuevo no tiene a nadie atrás y adelante tiene al head actual
    DNode<T>* nuevo = new DNode<T>(valor, nullptr, head);
    if (head != nullptr) {
        // el head viejo ahora tiene al nuevo atrás
        head->prev = nuevo;
    } else {
        // la lista estaba vacía: el nuevo también es el último
        tail = nuevo;
    }
    head = nuevo;
    count++;
}

// Inserta al final. O(1) gracias a que guardamos tail
template <typename T>
void DoublyLinkedList<T>::insertBack(const T& valor) {
    // el nuevo tiene atrás al tail actual y adelante a nadie
    DNode<T>* nuevo = new DNode<T>(valor, tail, nullptr);
    if (tail != nullptr) {
        // el tail viejo ahora tiene al nuevo adelante
        tail->next = nuevo;
    } else {
        // la lista estaba vacía: el nuevo también es el primero
        head = nuevo;
    }
    tail = nuevo;
    count++;
}

// Inserta un nodo nuevo justo después de nodo. O(1)
// Si nodo es nullptr no hace nada.
//
//   antes:   [nodo] <-> [siguiente]
//   después: [nodo] <-> [nuevo] <-> [siguiente]
template <typename T>
void DoublyLinkedList<T>::insertAfter(DNode<T>* nodo, const T& valor) {
    if (nodo == nullptr) {
        return;
    }
    // 1. si nodo es el último, es lo mismo que insertar al final
    //    (así tail se actualiza en un solo lugar)
    if (nodo == tail) {
        insertBack(valor);
        return;
    }
    // 2. el nuevo nodo ya nace apuntando a sus dos vecinos
    DNode<T>* siguiente = nodo->next;
    DNode<T>* nuevo = new DNode<T>(valor, nodo, siguiente);
    // 3. ahora los vecinos apuntan al nuevo, cada uno desde su lado
    nodo->next = nuevo;       // nodo -> nuevo
    siguiente->prev = nuevo;  // nuevo <- siguiente
    count++;
}

// Saca nodo de la lista y libera su memoria. O(1)
// Regresa false si nodo es nullptr.
// Se revisa cada caso por separado porque aquí es donde más fácil se
// rompen los apuntadores prev.
template <typename T>
bool DoublyLinkedList<T>::remove(DNode<T>* nodo) {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo == head && nodo == tail) {
        // Caso 1: es el único nodo. La lista queda vacía.
        head = nullptr;
        tail = nullptr;
    } else if (nodo == head) {
        // Caso 2: es el primero. El segundo pasa a ser head
        // y ya no tiene a nadie atrás.
        //   [nodo] <-> [B] ...   ->   [B] ...
        head = nodo->next;
        head->prev = nullptr;
    } else if (nodo == tail) {
        // Caso 3: es el último. El penúltimo pasa a ser tail
        // y ya no tiene a nadie adelante.
        //   ... [A] <-> [nodo]   ->   ... [A]
        tail = nodo->prev;
        tail->next = nullptr;
    } else {
        // Caso 4: está en medio. Sus dos vecinos se apuntan entre sí.
        //   [A] <-> [nodo] <-> [B]   ->   [A] <-> [B]
        nodo->prev->next = nodo->next;
        nodo->next->prev = nodo->prev;
    }

    delete nodo;
    count--;
    return true;
}

// Imprime de head a tail usando next. O(n)
template <typename T>
void DoublyLinkedList<T>::printForward() const {
    if (head == nullptr) {
        std::cout << "(vacia)";
    }
    for (DNode<T>* aux = head; aux != nullptr; aux = aux->next) {
        std::cout << aux->data;
        if (aux->next != nullptr) {
            std::cout << " <-> ";
        }
    }
    std::cout << std::endl;
}

// Imprime de tail a head usando prev. O(n)
// Si algún prev estuviera mal, no saldría al revés que printForward.
template <typename T>
void DoublyLinkedList<T>::printBackward() const {
    if (tail == nullptr) {
        std::cout << "(vacia)";
    }
    for (DNode<T>* aux = tail; aux != nullptr; aux = aux->prev) {
        std::cout << aux->data;
        if (aux->prev != nullptr) {
            std::cout << " <-> ";
        }
    }
    std::cout << std::endl;
}

// ---------- Merge sort ----------
// Se ordenan los nodos que ya existen: no se crean nodos nuevos ni se
// copian registros, solo se cambian los apuntadores next y prev.

// Parte la cadena que empieza en inicio en dos mitades y regresa el
// primer nodo de la segunda mitad. La cadena tiene al menos 2 nodos.
// lento avanza de 1 en 1 y rapido de 2 en 2: cuando rapido llega al
// final, lento está a la mitad.
//
//   antes:   [1] <-> [2] <-> [3] <-> [4]
//   después: [1] <-> [2]     [3] <-> [4]
//                            ^ mitad
template <typename T>
DNode<T>* DoublyLinkedList<T>::dividir(DNode<T>* inicio) {
    DNode<T>* lento = inicio;
    DNode<T>* rapido = inicio->next;
    while (rapido != nullptr && rapido->next != nullptr) {
        lento = lento->next;
        rapido = rapido->next->next;
    }
    DNode<T>* mitad = lento->next;
    // cortar: la primera mitad ya no sigue y la segunda ya no tiene a nadie atrás
    mitad->prev->next = nullptr;
    mitad->prev = nullptr;
    return mitad;
}

// Junta dos cadenas ya ordenadas en una sola ordenada y regresa su primer
// nodo. Va enganchando los nodos que ya existen, uno por uno.
// Cada comparación suma 1 al contador.
template <typename T>
DNode<T>* DoublyLinkedList<T>::mezclar(DNode<T>* a, DNode<T>* b,
    long long& comparaciones) {
    DNode<T>* inicio = nullptr;  // primer nodo del resultado
    DNode<T>* ultimo = nullptr;  // último nodo que ya se enganchó

    while (a != nullptr && b != nullptr) {
        comparaciones++;
        DNode<T>* tomado;
        // Solo se toma el de b si es estrictamente menor. Si son iguales
        // gana el de a (el de la izquierda), y eso hace estable al merge sort:
        // dos registros con la misma fecha quedan en el orden del archivo.
        if (!(b->data < a->data)) {
            tomado = a;
            a = a->next;
        } else {
            tomado = b;
            b = b->next;
        }
        // enganchar el nodo tomado después del último, en los dos sentidos
        tomado->prev = ultimo;
        if (ultimo == nullptr) {
            inicio = tomado;
        } else {
            ultimo->next = tomado;
        }
        ultimo = tomado;
    }

    // Lo que sobre de una de las dos cadenas ya está ordenado y sus prev
    // ya están bien entre ellos; solo hay que pegar su primer nodo.
    DNode<T>* resto = (a != nullptr) ? a : b;
    if (ultimo == nullptr) {
        inicio = resto;
    } else {
        ultimo->next = resto;
        if (resto != nullptr) {
            resto->prev = ultimo;
        }
    }
    return inicio;
}

// Ordena la cadena que empieza en inicio y regresa su nuevo primer nodo.
// profundidad dice en qué nivel de la recursión vamos (la primera llamada es 1).
// Las cadenas de 0 o 1 nodo ya están ordenadas y no cuentan para la profundidad.
template <typename T>
DNode<T>* DoublyLinkedList<T>::mergeSortRec(DNode<T>* inicio, int profundidad,
                                            long long& comparaciones,
                                            int& maxProfundidad) {
    if (inicio == nullptr || inicio->next == nullptr) {
        return inicio;
    }
    if (profundidad > maxProfundidad) {
        maxProfundidad = profundidad;
    }
    DNode<T>* mitad = dividir(inicio);
    DNode<T>* izquierda = mergeSortRec(inicio, profundidad + 1, comparaciones, maxProfundidad);
    DNode<T>* derecha = mergeSortRec(mitad, profundidad + 1, comparaciones, maxProfundidad);
    return mezclar(izquierda, derecha, comparaciones);
}

// Ordena la lista de menor a mayor con merge sort. O(n log n) siempre.
// Deja en comparaciones cuántas veces se compararon dos registros y en
// maxProfundidad el nivel más hondo de la recursión (contando la primera
// llamada como 1). Al final marca ordenada = true.
template <typename T>
void DoublyLinkedList<T>::mergeSort(long long& comparaciones, int& maxProfundidad) {
    comparaciones = 0;
    maxProfundidad = 0;
    head = mergeSortRec(head, 1, comparaciones, maxProfundidad);

    // El head quedó bien, pero tail sigue apuntando al nodo que era el
    // último antes de ordenar. Hay que caminar hasta el final para fijarlo.
    tail = head;
    if (tail != nullptr) {
        while (tail->next != nullptr) {
            tail = tail->next;
        }
    }
    ordenada = true;
}

// Deja la lista vacía, libera todos los nodos y marca ordenada = false,
// porque una lista vacía ya no tiene un orden que recordar. O(n)
template <typename T>
void DoublyLinkedList<T>::clear() {
    DNode<T>* aux = head;
    while (aux != nullptr) {
        // guardar el siguiente antes de borrar el actual
        DNode<T>* siguiente = aux->next;
        delete aux;
        aux = siguiente;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
    ordenada = false;
}

// Destructor: libera todos los nodos. O(n)
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}
