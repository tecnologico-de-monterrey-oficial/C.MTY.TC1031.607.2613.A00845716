// Diego Contreras
// A00845716

// Convierte una fecha de texto en un numero comparable y lee los archivos de log.

#include "registro.h"
#include <fstream>
#include <iostream>
#include <cctype>

// Los tres primeros meses del ano van en el mismo orden que en el log.
static const std::string MESES[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Recibe "Jan" a "Dec" y regresa 1 a 12. Si no es un mes regresa -1.
int mesANumero(const std::string& mes) {
    for (int i = 0; i < 12; i++) {
        if (mes == MESES[i]) {
            return i + 1;
        }
    }
    return -1;
}

// Quita los espacios de los extremos del texto.
static std::string limpiarEspacios(const std::string& texto) {
    int inicio = 0;
    int fin = (int)texto.size() - 1;
    while (inicio <= fin && isspace((unsigned char)texto[inicio])) {
        inicio++;
    }
    while (fin >= inicio && isspace((unsigned char)texto[fin])) {
        fin--;
    }
    return texto.substr(inicio, fin - inicio + 1);
}

// Revisa que todos los caracteres de un pedazo del texto sean digitos.
static bool sonDigitos(const std::string& texto, int desde, int cuantos) {
    for (int i = desde; i < desde + cuantos; i++) {
        if (!isdigit((unsigned char)texto[i])) {
            return false;
        }
    }
    return true;
}

// Toma "Oct 02 2024 23:04:24", lo valida y arma la clave 20241002230424.
// Regresa false si la fecha no sirve, y en ese caso no toca la clave.
bool fechaAClave(const std::string& texto, long long& clave) {
    std::string f = limpiarEspacios(texto);

    // La fecha siempre mide 20 caracteres: "Mmm dd aaaa hh:mm:ss".
    if (f.size() != 20) {
        return false;
    }

    // Los separadores tienen que estar en su lugar exacto.
    if (f[3] != ' ' || f[6] != ' ' || f[11] != ' ' || f[14] != ':' || f[17] != ':') {
        return false;
    }

    // Donde van numeros no puede haber letras.
    if (!sonDigitos(f, 4, 2) || !sonDigitos(f, 7, 4) || !sonDigitos(f, 12, 2) ||
        !sonDigitos(f, 15, 2) || !sonDigitos(f, 18, 2)) {
        return false;
    }

    int mes = mesANumero(f.substr(0, 3));
    if (mes == -1) {
        return false;
    }

    int dia  = std::stoi(f.substr(4, 2));
    int anio = std::stoi(f.substr(7, 4));
    int hora = std::stoi(f.substr(12, 2));
    int min  = std::stoi(f.substr(15, 2));
    int seg  = std::stoi(f.substr(18, 2));

    // Cada parte tiene que caer en su rango valido.
    if (dia < 1 || dia > 31)   return false;
    if (hora < 0 || hora > 23) return false;
    if (min < 0 || min > 59)   return false;
    if (seg < 0 || seg > 59)   return false;

    // El ano va primero para que pese mas que el mes, el mes mas que el dia, y asi.
    clave = (long long)anio * 10000000000LL
          + (long long)mes  * 100000000LL
          + (long long)dia  * 1000000LL
          + (long long)hora * 10000LL
          + (long long)min  * 100LL
          + (long long)seg;
    return true;
}
