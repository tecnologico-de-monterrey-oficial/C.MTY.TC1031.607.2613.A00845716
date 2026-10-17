// Diego Contreras
// A00845716

// Estructura de un registro del log y funciones para convertir y validar
// sus partes. Viene de registro.h de la Evidencia 1.
// Ahora cada campo se guarda por separado, porque la opción 4 cuenta
// por día, por IP y por evento.

#pragma once
#include <string>

struct Registro {
    std::string mes;          // "Sep"
    int dia = 0;
    int anio = 0;
    std::string hora;         // "14:37:38"
    std::string ip;           // "10.14.19.188"
    std::string descripcion;  // "Unauthorized Access Attempts"
    long long clave = 0;      // Sep 29 2024 14:37:38 se guarda como 20240929143738
    std::string linea;        // la línea original completa
};

// Un registro es menor que otro si su fecha es anterior.
// Así los algoritmos de ordenamiento pueden usar < directamente.
inline bool operator<(const Registro& a, const Registro& b) {
    return a.clave < b.clave;
}

std::string limpiarEspacios(const std::string& texto);
int mesANumero(const std::string& mes);
bool fechaAClave(const std::string& texto, long long& clave);
std::string claveATexto(long long clave);

// Toma un día "Dec 16 2025", lo valida y arma su clave 20251216 (AAAAMMDD).
// Regresa false si el día no sirve, y en ese caso no toca la clave.
bool diaAClave(const std::string& texto, long long& dia);

// El día de un registro en formato AAAAMMDD: 20251216143738 -> 20251216.
inline long long diaDeRegistro(const Registro& reg) {
    return reg.clave / 1000000;
}

// Separa una línea del log en sus campos y los guarda en reg.
// Si la línea no sirve regresa false y deja en motivo la razón:
// "linea vacia", "mes invalido", "fecha imposible", "hora invalida",
// "falta la IP" o "falta la descripcion".
bool parsearLinea(const std::string& linea, Registro& reg, std::string& motivo);
