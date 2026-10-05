// Diego Contreras
// A00845716

#include <iostream>
#include <string>
#include <limits>
#include "queue.h"

using namespace std;

// Datos de cada persona que llega a comprar boletos
struct Cliente {
    string nombre;
    int boletos;
};

// Pide un numero entero y lo vuelve a pedir si escriben letras
// o si no esta entre minimo y maximo
int leerNumero(const string& mensaje, int minimo, int maximo) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero && numero >= minimo && numero <= maximo) {
            // Quitamos el Enter que queda despues del numero
            // para que el siguiente getline no lea una linea vacia
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
        cout << "Dato no valido, intenta de nuevo." << endl;
        // Limpiamos el error de cin y tiramos lo que se escribio mal
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Queue<Cliente> fila;
    int opcion = 0;

    while (opcion != 5) {
        cout << endl;
        cout << "===== Venta de boletos =====" << endl;
        cout << "1. Llegada de un nuevo cliente" << endl;
        cout << "2. Atender al siguiente cliente" << endl;
        cout << "3. Ver al siguiente cliente sin atenderlo" << endl;
        cout << "4. Mostrar cuantas personas hay en la fila" << endl;
        cout << "5. Salir" << endl;

        opcion = leerNumero("Elige una opcion: ", 1, 5);

        if (opcion == 1) {
            Cliente cliente;
            cout << "Nombre del cliente: ";
            getline(cin, cliente.nombre);
            cliente.boletos = leerNumero("Cantidad de boletos: ", 1, numeric_limits<int>::max());
            fila.push(cliente);
            cout << cliente.nombre << " se formo en la fila." << endl;
        } else if (opcion == 2) {
            try {
                Cliente cliente = fila.pop();
                cout << "Se atendio a " << cliente.nombre
                    << ", que pidio " << cliente.boletos << " boletos." << endl;
            } catch (exception& e) {
                cout << "No hay clientes en la fila" << endl;
            }
        } else if (opcion == 3) {
            try {
                Cliente cliente = fila.front();
                cout << "El siguiente es " << cliente.nombre
                     << ", que pide " << cliente.boletos << " boletos." << endl;
            } catch (exception& e) {
                cout << "No hay clientes en la fila" << endl;
            }
        } else if (opcion == 4) {
            cout << "Hay " << fila.size() << " personas en la fila." << endl;
        }
    }

    cout << "Hasta luego." << endl;
    return 0;
}
