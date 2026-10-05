// Diego Contreras
// A00845716

#include <iostream>
#include <string>
#include <limits>
#include "stack.h"

using namespace std;

// Datos de cada pagina que se visita
struct PaginaWeb {
    string titulo;
    string url;
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
    Stack<PaginaWeb> historial;
    int opcion = 0;

    while (opcion != 5) {
        cout << endl;
        cout << "===== Navegador =====" << endl;
        cout << "1. Visitar una nueva pagina" << endl;
        cout << "2. Retroceder a la pagina anterior" << endl;
        cout << "3. Ver la pagina actual" << endl;
        cout << "4. Mostrar cuantas paginas hay en el historial" << endl;
        cout << "5. Salir" << endl;

        opcion = leerNumero("Elige una opcion: ", 1, 5);

        if (opcion == 1) {
            PaginaWeb pagina;
            cout << "Titulo de la pagina: ";
            getline(cin, pagina.titulo);
            cout << "URL de la pagina: ";
            getline(cin, pagina.url);
            historial.push(pagina);
            cout << "Visitaste " << pagina.titulo << "." << endl;
        } else if (opcion == 2) {
            try {
                PaginaWeb pagina = historial.pop();
                cout << "Se cerro " << pagina.titulo
                    << " (" << pagina.url << ")." << endl;
            } catch (exception& e) {
                cout << "No hay paginas en el historial" << endl;
            }
        } else if (opcion == 3) {
            try {
                PaginaWeb pagina = historial.top();
                cout << "Estas en " << pagina.titulo
                     << " (" << pagina.url << ")." << endl;
            } catch (exception& e) {
                cout << "No hay paginas en el historial" << endl;
            }
        } else if (opcion == 4) {
            cout << "Hay " << historial.size() << " paginas en el historial." << endl;
        }
    }

    cout << "Hasta luego." << endl;
    return 0;
}
