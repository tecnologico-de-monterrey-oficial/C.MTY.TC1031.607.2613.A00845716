// Diego Contreras Alvarez
// Matrícula:A00845716
// Fecha: 9 de octubre de 2026
// Descripción: menú para probar la lista doblemente ligada con int, double,
// char o string. La lista se llena con datos aleatorios o capturados y se
// muestra después de cada operación.
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "DoublyLinkedList.h"
using namespace std;

// Se lanza cuando ya no hay nada que leer (por ejemplo Ctrl+D), para salir
// del programa limpiamente y que los destructores liberen la memoria
struct FinDeEntrada {};

// Tira lo que quede escrito en la línea, incluido el Enter
void limpiarLinea() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Pide un número entero y lo vuelve a pedir si escriben letras
// o si no está entre minimo y maximo
int leerNumero(const string& mensaje, int minimo, int maximo) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero && numero >= minimo && numero <= maximo) {
            limpiarLinea();
            return numero;
        }
        if (cin.eof()) {
            throw FinDeEntrada();
        }
        cout << "Dato no valido, intenta de nuevo." << endl;
        // quitar el error de cin y tirar lo que se escribió mal
        cin.clear();
        limpiarLinea();
    }
}

// Pide un índice; se aceptan negativos a propósito para poder probar
// que la lista los rechaza
int leerIndice(const string& mensaje) {
    return leerNumero(mensaje, numeric_limits<int>::min(), numeric_limits<int>::max());
}

// Pide un valor del tipo de la lista y lo vuelve a pedir si no se puede leer
// (por ejemplo letras cuando la lista es de int)
template <typename T>
T leerValor(const string& mensaje) {
    T valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            limpiarLinea();
            return valor;
        }
        if (cin.eof()) {
            throw FinDeEntrada();
        }
        cout << "Dato no valido, intenta de nuevo." << endl;
        cin.clear();
        limpiarLinea();
    }
}

// Muestra la lista en los dos sentidos y cuántos elementos tiene
template <typename T>
void mostrar(const DoublyLinkedList<T>& lista) {
    lista.print();
    cout << "Tamano: " << lista.getSize() << endl;
}

// Un valor al azar para cada tipo de dato
int valorAleatorio(int) {
    return rand() % 100 + 1; // entre 1 y 100
}

double valorAleatorio(double) {
    return (rand() % 10000) / 100.0; // entre 0.00 y 99.99
}

char valorAleatorio(char) {
    return 'a' + rand() % 26; // una letra minúscula
}

string valorAleatorio(string) {
    string palabras[10] = {"perro", "gato", "casa", "sol", "luna",
                           "arbol", "mar", "libro", "mesa", "flor"};
    return palabras[rand() % 10];
}

// Agrega cantidad valores al azar al final de la lista
template <typename T>
void llenarAleatorio(DoublyLinkedList<T>& lista, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        // T() solo sirve para que se elija la versión de valorAleatorio del tipo T
        lista.addLast(valorAleatorio(T()));
    }
}

// Pide al usuario cada elemento y lo agrega al final
template <typename T>
void llenarCapturado(DoublyLinkedList<T>& lista, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        lista.addLast(leerValor<T>("Elemento " + to_string(i + 1) + ": "));
    }
}

// Crea la lista, la llena y muestra el menú. Es un template para que el
// mismo código sirva para int, double, char y string.
template <typename T>
void runMenu() {
    DoublyLinkedList<T> lista;

    cout << "1) Datos aleatorios" << endl;
    cout << "2) Datos capturados" << endl;
    int forma = leerNumero("Opcion: ", 1, 2);
    int cantidad = leerNumero("Cuantos elementos? ", 0, 100000);
    if (forma == 1) {
        llenarAleatorio(lista, cantidad);
    } else {
        llenarCapturado(lista, cantidad);
    }
    mostrar(lista);

    int opcion = -1;
    while (opcion != 0) {
        cout << endl;
        cout << "1) addFirst: agregar al principio" << endl;
        cout << "2) addLast: agregar al final" << endl;
        cout << "3) insert: insertar despues de un indice" << endl;
        cout << "4) deleteData: borrar un elemento dado" << endl;
        cout << "5) deleteAt: borrar en una posicion" << endl;
        cout << "6) getData: obtener el elemento de una posicion" << endl;
        cout << "7) updateData: actualizar un elemento dado" << endl;
        cout << "8) updateAt: actualizar el elemento de una posicion" << endl;
        cout << "9) findData: buscar un elemento" << endl;
        cout << "10) Leer con operador []" << endl;
        cout << "11) Actualizar con operador []" << endl;
        cout << "12) Igualar listas con operador =" << endl;
        cout << "13) clear: vaciar la lista" << endl;
        cout << "14) sort: ordenar" << endl;
        cout << "15) duplicate: duplicar cada elemento" << endl;
        cout << "16) removeDuplicates: quitar repetidos" << endl;
        cout << "17) Imprimir" << endl;
        cout << "0) Salir" << endl;
        opcion = leerNumero("Opcion: ", 0, 17);

        // si algo falla (índice inválido, dato no encontrado) se muestra el
        // error y el menú sigue
        try {
            switch (opcion) {
                case 1:
                    lista.addFirst(leerValor<T>("Valor: "));
                    break;
                case 2:
                    lista.addLast(leerValor<T>("Valor: "));
                    break;
                case 3: {
                    int index = leerIndice("Insertar despues del indice: ");
                    T valor = leerValor<T>("Valor: ");
                    lista.insert(index, valor);
                    break;
                }
                case 4:
                    if (lista.deleteData(leerValor<T>("Valor a borrar: "))) {
                        cout << "Elemento borrado" << endl;
                    } else {
                        cout << "No se encontro el elemento" << endl;
                    }
                    break;
                case 5:
                    if (lista.deleteAt(leerIndice("Posicion a borrar: "))) {
                        cout << "Elemento borrado" << endl;
                    } else {
                        cout << "Posicion invalida, no se borro nada" << endl;
                    }
                    break;
                case 6: {
                    int index = leerIndice("Posicion: ");
                    // se guarda primero: si lanza, no se imprime nada a medias
                    T valor = lista.getData(index);
                    cout << "Elemento: " << valor << endl;
                    break;
                }
                case 7: {
                    T viejo = leerValor<T>("Valor actual: ");
                    T nuevo = leerValor<T>("Valor nuevo: ");
                    lista.updateData(viejo, nuevo);
                    break;
                }
                case 8: {
                    int index = leerIndice("Posicion: ");
                    T valor = leerValor<T>("Valor nuevo: ");
                    lista.updateAt(index, valor);
                    break;
                }
                case 9: {
                    int pos = lista.findData(leerValor<T>("Valor a buscar: "));
                    if (pos == -1) {
                        cout << "Elemento no encontrado (-1)" << endl;
                    } else {
                        cout << "Esta en la posicion " << pos << endl;
                    }
                    break;
                }
                case 10: {
                    int index = leerIndice("Posicion: ");
                    T valor = lista[index];
                    cout << "lista[" << index << "] = " << valor << endl;
                    break;
                }
                case 11: {
                    int index = leerIndice("Posicion: ");
                    T valor = leerValor<T>("Valor nuevo: ");
                    lista[index] = valor;
                    break;
                }
                case 12: {
                    // la otra lista ya tiene datos, para ver que = los borra
                    DoublyLinkedList<T> otra;
                    llenarAleatorio(otra, 3);
                    cout << "Otra lista antes de igualar:" << endl;
                    mostrar(otra);

                    otra = lista;
                    cout << "Despues de otra = lista" << endl;
                    cout << "Original:" << endl;
                    mostrar(lista);
                    cout << "Otra:" << endl;
                    mostrar(otra);

                    // cambiar solo la otra para ver que son independientes
                    otra.addFirst(leerValor<T>("Valor para agregar al inicio de la otra: "));
                    cout << "Original:" << endl;
                    mostrar(lista);
                    cout << "Otra:" << endl;
                    mostrar(otra);
                    cout << "La original no cambio, la copia es independiente" << endl;
                    break;
                }
                case 13:
                    lista.clear();
                    break;
                case 14:
                    lista.sort();
                    break;
                case 15:
                    lista.duplicate();
                    break;
                case 16:
                    lista.removeDuplicates();
                    break;
                case 17:
                    break;
                case 0:
                    cout << "Adios" << endl;
                    break;
            }
        } catch (out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }

        if (opcion != 0) {
            cout << "Lista:" << endl;
            mostrar(lista);
        }
    }
}

int main() {
    srand(time(0));

    try {
        cout << "Tipo de dato de la lista:" << endl;
        cout << "1) int" << endl;
        cout << "2) double" << endl;
        cout << "3) char" << endl;
        cout << "4) string" << endl;
        int tipo = leerNumero("Opcion: ", 1, 4);

        if (tipo == 1) {
            runMenu<int>();
        } else if (tipo == 2) {
            runMenu<double>();
        } else if (tipo == 3) {
            runMenu<char>();
        } else {
            runMenu<string>();
        }
    } catch (FinDeEntrada&) {
        cout << endl << "Fin de la entrada" << endl;
    }

    return 0;
}
