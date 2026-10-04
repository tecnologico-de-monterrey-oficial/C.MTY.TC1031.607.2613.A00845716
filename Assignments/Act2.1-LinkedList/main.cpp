// Diego Contreras Alvarez
// A00845716
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "LinkedList.h"
using namespace std;

// muestra la lista y cuantos elementos tiene
template <typename T>
void mostrar(LinkedList<T>& lista) {
    cout << "Lista: ";
    lista.print();
    cout << "Tamano: " << lista.getSize() << endl;
}

// llena una lista de enteros con numeros al azar entre 1 y 100
void llenarAleatorio(LinkedList<int>& lista, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        int numero = rand() % 100 + 1;
        // insertar en la ultima posicion para que queden en orden
        lista.insert(lista.getSize(), numero);
    }
}

// llena una lista de strings con palabras al azar de un arreglo fijo
void llenarAleatorio(LinkedList<string>& lista, int cantidad) {
    string palabras[10] = {"perro", "gato", "casa", "sol", "luna",
                           "arbol", "mar", "libro", "mesa", "flor"};
    for (int i = 0; i < cantidad; i++) {
        string palabra = palabras[rand() % 10];
        lista.insert(lista.getSize(), palabra);
    }
}

// pide al usuario cada elemento y lo agrega a la lista
template <typename T>
void llenarCapturado(LinkedList<T>& lista, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        T valor;
        cout << "Elemento " << i + 1 << ": ";
        cin >> valor;
        lista.insert(lista.getSize(), valor);
    }
}

// el mismo menu sirve para listas de int y de string
template <typename T>
void menu(LinkedList<T>& lista) {
    int opcion = -1;
    while (opcion != 0) {
        cout << endl;
        cout << "1) Agregar al principio" << endl;
        cout << "2) Agregar al final" << endl;
        cout << "3) Insertar en un índice" << endl;
        cout << "4) Borrar un elemento dado" << endl;
        cout << "5) Borrar en una posicion" << endl;
        cout << "6) Obtener el elemento de una posicion" << endl;
        cout << "7) Actualizar un elemento dado" << endl;
        cout << "8) Actualizar el elemento de una posicion" << endl;
        cout << "9) Buscar un elemento" << endl;
        cout << "10) Obtener con operador []" << endl;
        cout << "11) Actualizar con operador []" << endl;
        cout << "12) Igualar listas con operador =" << endl;
        cout << "0) Salir" << endl;
        cout << "Opcion: ";
        // si ya no se puede leer nada (fin de la entrada) se sale del menu
        if (!(cin >> opcion)) {
            break;
        }

        T valor;
        int pos;

        // si algo falla (posicion invalida) se muestra el error y el menu sigue
        try {
            switch (opcion) {
                case 1:
                    cout << "Valor: ";
                    cin >> valor;
                    lista.addFirst(valor);
                    mostrar(lista);
                    break;
                case 2:
                    cout << "Valor: ";
                    cin >> valor;
                    lista.addLast(valor);
                    mostrar(lista);
                    break;
                case 3:
                    cout << "Indice: ";
                    cin >> pos;
                    cout << "Valor: ";
                    cin >> valor;
                    lista.insert(pos, valor);
                    mostrar(lista);
                    break;
                case 4:
                    cout << "Valor a borrar: ";
                    cin >> valor;
                    if (lista.deleteData(valor)) {
                        cout << "Elemento borrado" << endl;
                    } else {
                        cout << "No se pudo borrar" << endl;
                    }
                    mostrar(lista);
                    break;
                case 5:
                    cout << "Posicion a borrar: ";
                    cin >> pos;
                    if (lista.deleteAt(pos)) {
                        cout << "Elemento borrado" << endl;
                    } else {
                        cout << "No se pudo borrar" << endl;
                    }
                    mostrar(lista);
                    break;
                case 6:
                    cout << "Posicion: ";
                    cin >> pos;
                    cout << "Elemento: " << lista.getData(pos) << endl;
                    mostrar(lista);
                    break;
                case 7: {
                    T nuevo;
                    cout << "Valor actual: ";
                    cin >> valor;
                    cout << "Valor nuevo: ";
                    cin >> nuevo;
                    lista.updateData(valor, nuevo);
                    mostrar(lista);
                    break;
                }
                case 8:
                    cout << "Posicion: ";
                    cin >> pos;
                    cout << "Valor nuevo: ";
                    cin >> valor;
                    lista.updateAt(pos, valor);
                    mostrar(lista);
                    break;
                case 9:
                    cout << "Valor a buscar: ";
                    cin >> valor;
                    pos = lista.findData(valor);
                    if (pos == -1) {
                        cout << "Elemento no encontrado" << endl;
                    } else {
                        cout << "Esta en la posicion " << pos << endl;
                    }
                    mostrar(lista);
                    break;
                case 10:
                    cout << "Posicion: ";
                    cin >> pos;
                    cout << "Elemento: " << lista[pos] << endl;
                    mostrar(lista);
                    break;
                case 11:
                    cout << "Posicion: ";
                    cin >> pos;
                    cout << "Valor nuevo: ";
                    cin >> valor;
                    lista[pos] = valor;
                    mostrar(lista);
                    break;
                case 12: {
                    LinkedList<T> copia;
                    copia = lista;
                    cout << "Original: ";
                    lista.print();
                    cout << "Copia: ";
                    copia.print();
                    // cambiar solo la copia para ver que son independientes
                    cout << "Valor nuevo para el primer elemento de la copia: ";
                    cin >> valor;
                    copia.updateAt(0, valor);
                    cout << "Original: ";
                    lista.print();
                    cout << "Copia: ";
                    copia.print();
                    mostrar(lista);
                    break;
                }
                case 0:
                    cout << "Adios" << endl;
                    break;
                default:
                    cout << "Opcion invalida" << endl;
            }
        } catch (out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

// pregunta como llenar la lista y despues abre el menu
template <typename T>
void iniciar(LinkedList<T>& lista) {
    int forma, cantidad;
    cout << "1) Datos aleatorios" << endl;
    cout << "2) Datos capturados" << endl;
    cout << "Opcion: ";
    cin >> forma;
    cout << "Cuantos elementos? ";
    cin >> cantidad;

    if (forma == 1) {
        llenarAleatorio(lista, cantidad);
    } else {
        llenarCapturado(lista, cantidad);
    }
    mostrar(lista);
    menu(lista);
}

int main() {
    srand(time(0));

    int tipo;
    cout << "Tipo de lista:" << endl;
    cout << "1) int" << endl;
    cout << "2) string" << endl;
    cout << "Opcion: ";
    cin >> tipo;

    if (tipo == 1) {
        LinkedList<int> lista;
        iniciar(lista);
    } else {
        LinkedList<string> lista;
        iniciar(lista);
    }

    return 0;
}
