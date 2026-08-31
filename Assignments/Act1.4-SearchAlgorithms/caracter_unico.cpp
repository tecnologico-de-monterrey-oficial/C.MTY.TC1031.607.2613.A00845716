// Programa 2: Caracter unico en strings con caracteres duplicados y continuos.
// Diego Contreras
// A00845716
// Se asume que el string tiene un caracter unico y todos los demas estan duplicados

#include <iostream>
#include <string>

using namespace std;

// Busqueda secuencial del caracter unico.
char buscarSecuencial(const string& s, int& comparaciones) {
    comparaciones = 0;
    int n = static_cast<int>(s.size());
    int i = 0;
    while (i < n) {
        if (i == n - 1) {
            // Ultimo caracter solo: es el unico, sin comparar.
            return s[i];
        }
        comparaciones++;
        if (s[i] != s[i + 1]) {
            return s[i];
        }
        i += 2;
    }
    return s[n - 1];
}

// Busqueda binaria del caracter unico.
char buscarBinaria(const string& s, int& comparaciones) {
    comparaciones = 0;
    int n = static_cast<int>(s.size());
    int inicio = 0;
    int fin = (n - 1) / 2;   // indice del ultimo par
    while (true) {
        int medio = (inicio + fin) / 2;
        int idx = 2 * medio;
        comparaciones++;
        if (idx + 1 < n && s[idx] == s[idx + 1]) {
            // Par valido: el caracter unico esta a la derecha.
            inicio = medio + 1;
        } else {
            // Par roto (o caracter solo): este es el caracter unico.
            return s[idx];
        }
    }
}

int main() {
    int n;
    cin >> n;

    for (int k = 0; k < n; k++) {
        string s;
        cin >> s;

        int compSec = 0;
        int compBin = 0;
        char unicoSec = buscarSecuencial(s, compSec);
        char unicoBin = buscarBinaria(s, compBin);

        cout << unicoSec << " " << compSec << " "
             << unicoBin << " " << compBin << "\n";
    }

    return 0;
}
