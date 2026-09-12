// Diego Contreras
// A00845716

// Programa principal: menu para generar vectores con datos al azar,
// ordenarlos con distintos algoritmos, medir su tiempo (en nanosegundos)
// y hacer una comparacion completa que se guarda en un CSV.

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <chrono>

#include "sorting.h"
#include "data_generator.h"
#include "benchmark.h"

using namespace std;

// ------------------------------------------------------------------
// Lectura segura de un numero entero dentro de un rango [min, max].
// Si el usuario escribe algo que no es numero, se avisa y se repite.
// ------------------------------------------------------------------
int leerOpcion(int minimo, int maximo, const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= minimo && valor <= maximo) {
            return valor;
        }
        // limpiamos el error y descartamos lo que quedo escrito
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Entrada no valida. Escribe un numero entre "
             << minimo << " y " << maximo << ".\n";
    }
}

// Convierte la opcion de tamano (1,2,3) al numero real de elementos.
int tamanoElegido(int opcion) {
    if (opcion == 1) return 1000;
    if (opcion == 2) return 10000;
    return 100000;
}

// ------------------------------------------------------------------
// Imprime un vector. Como pueden ser enormes, se pregunta como verlo:
//   1) completo, 2) resumen (primeros y ultimos), 3) no mostrarlo.
// ------------------------------------------------------------------
template <typename T>
void mostrarVector(const vector<T>& lista) {
    cout << "\nComo quieres ver el vector ordenado?\n";
    cout << "  1) Completo\n";
    cout << "  2) Resumen (primeros y ultimos 20)\n";
    cout << "  3) No mostrarlo\n";
    int opcion = leerOpcion(1, 3, "Opcion: ");

    int n = static_cast<int>(lista.size());

    if (opcion == 3) {
        return;
    }

    if (opcion == 1) {
        cout << "\nVector ordenado (" << n << " elementos):\n";
        for (int i = 0; i < n; i++) {
            cout << lista[i] << " ";
        }
        cout << "\n";
    } else {
        cout << "\nVector ordenado (resumen de " << n << " elementos):\n";
        int limite = (n < 20) ? n : 20;
        for (int i = 0; i < limite; i++) {
            cout << lista[i] << " ";
        }
        if (n > 40) {
            cout << "\n   ... (" << (n - 40) << " en medio) ...\n";
            for (int i = n - 20; i < n; i++) {
                cout << lista[i] << " ";
            }
        }
        cout << "\n";
    }
}

// ------------------------------------------------------------------
// Flujo para ordenar UN vector de un tipo dado.
// Pasos: generar -> (cronometro) ordenar -> (parar) -> mostrar tiempo
//        -> mostrar vector. La impresion NO entra en el tiempo medido.
// ------------------------------------------------------------------
template <typename T>
void ordenarIndividual(vector<T> datos, const string& nombreTipo) {
    cout << "\nElige el algoritmo de ordenamiento:\n";
    for (int i = 1; i <= NUM_ALGORITMOS; i++) {
        cout << "  " << i << ") " << nombreAlgoritmo(i) << "\n";
    }
    int algoritmo = leerOpcion(1, NUM_ALGORITMOS, "Opcion: ");

    int n = static_cast<int>(datos.size());

    // Aviso cuando la combinacion puede tardar mucho (algoritmos O(n^2)).
    bool esLento = (algoritmo == 1 || algoritmo == 2 ||
                    algoritmo == 3 || algoritmo == 4);
    if (esLento && n >= 100000) {
        cout << "\n[AVISO] " << nombreAlgoritmo(algoritmo)
             << " con " << n << " elementos puede tardar bastante.\n";
        cout << "Deseas continuar? (1 = si, 2 = no): ";
        int seguir = leerOpcion(1, 2, "");
        if (seguir == 2) {
            cout << "Operacion cancelada.\n";
            return;
        }
    }

    cout << "\nOrdenando " << n << " elementos de tipo " << nombreTipo
         << " con " << nombreAlgoritmo(algoritmo) << "...\n";

    // Solo medimos el ordenamiento (no la generacion ni la impresion).
    auto inicio = chrono::high_resolution_clock::now();
    aplicarOrden(algoritmo, datos);
    auto fin = chrono::high_resolution_clock::now();

    long long nanos =
        chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();

    // Primero el tiempo...
    cout << "\nTiempo de " << nombreAlgoritmo(algoritmo) << ": "
         << nanos << " nanosegundos\n";
    if (estaOrdenado(datos)) {
        cout << "Verificacion: el vector quedo correctamente ordenado.\n";
    } else {
        cout << "Verificacion: ERROR, el vector NO quedo ordenado.\n";
    }

    // ...y despues el vector (fuera de la medicion).
    mostrarVector(datos);
}

// Menu para elegir tipo y tamano, y luego ordenar un vector individual.
void menuOrdenarUno() {
    cout << "\nElige el tipo de dato:\n";
    cout << "  1) int (enteros)\n";
    cout << "  2) double (reales)\n";
    cout << "  3) string (textos)\n";
    int tipo = leerOpcion(1, 3, "Opcion: ");

    cout << "\nElige el tamano del vector:\n";
    cout << "  1) 1,000\n";
    cout << "  2) 10,000\n";
    cout << "  3) 100,000\n";
    int opcionTamano = leerOpcion(1, 3, "Opcion: ");
    int n = tamanoElegido(opcionTamano);

    // Generamos los datos (esto NO se mide).
    if (tipo == 1) {
        ordenarIndividual(generarEnteros(n), "int");
    } else if (tipo == 2) {
        ordenarIndividual(generarDoubles(n), "double");
    } else {
        ordenarIndividual(generarStrings(n), "string");
    }
}

int main() {
    cout << "==============================================\n";
    cout << " ALGORITMOS DE ORDENAMIENTO - Act1.5\n";
    cout << " Diego Contreras (A00845716)\n";
    cout << "==============================================\n";

    int opcion;
    do {
        cout << "\n--------------- MENU ---------------\n";
        cout << "1) Ordenar un vector (elegir tipo, tamano y algoritmo)\n";
        cout << "2) Analisis comparativo completo (genera CSV)\n";
        cout << "3) Salir\n";
        opcion = leerOpcion(1, 3, "Elige una opcion: ");

        if (opcion == 1) {
            menuOrdenarUno();
        } else if (opcion == 2) {
            cout << "\n[AVISO] El analisis mide los 7 algoritmos con los 3\n";
            cout << "tipos de dato y los 3 tamanos (hasta 100,000).\n";
            cout << "Los algoritmos O(n^2) con 100,000 pueden tardar varios\n";
            cout << "minutos. Deseas continuar? (1 = si, 2 = no): ";
            int seguir = leerOpcion(1, 2, "");
            if (seguir == 1) {
                analisisComparativo();
            } else {
                cout << "Analisis cancelado.\n";
            }
        }
    } while (opcion != 3);

    cout << "\nPrograma terminado. Hasta luego!\n";
    return 0;
}
