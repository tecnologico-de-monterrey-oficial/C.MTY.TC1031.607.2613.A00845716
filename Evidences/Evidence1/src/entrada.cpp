// Diego Contreras
// A00845716

// Lee lo que escribe el usuario y no avanza hasta que el dato sea valido.
// Todo se lee con getline para no mezclar formas de leer y perder saltos de linea.

#include "entrada.h"
#include "registro.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

// Lee una linea completa. Si la entrada se cerro (Ctrl + D) termina el programa,
// porque si no se quedaria pidiendo el dato para siempre.
static std::string leerLinea(const std::string& mensaje) {
    std::cout << mensaje;
    std::string linea;
    if (!std::getline(std::cin, linea)) {
        std::cout << "\nEntrada terminada, saliendo del programa." << std::endl;
        std::exit(0);
    }
    return limpiarEspacios(linea);
}

// Pide un numero entero entre min y max. Vuelve a preguntar hasta que sea valido.
int leerEntero(const std::string& mensaje, int min, int max) {
    while (true) {
        std::string texto = leerLinea(mensaje);

        if (texto.empty()) {
            std::cout << "Entrada inválida. Escribe un número entre " << min
                      << " y " << max << "." << std::endl;
            continue;
        }

        // Solo digitos. Asi se rechazan "abc", "2abc", "1.5" y "-3".
        bool soloDigitos = true;
        for (char c : texto) {
            if (!isdigit((unsigned char)c)) {
                soloDigitos = false;
                break;
            }
        }
        if (!soloDigitos) {
            std::cout << "Entrada inválida. Escribe un número entre " << min
                      << " y " << max << "." << std::endl;
            continue;
        }

        // Un numero de mas de 9 digitos no cabe en un int y haria que stoi truene.
        if (texto.size() > 9) {
            std::cout << "Ese número es demasiado grande. Escribe un número entre "
                      << min << " y " << max << "." << std::endl;
            continue;
        }

        int valor = std::stoi(texto);
        if (valor < min || valor > max) {
            std::cout << "Entrada inválida. Escribe un número entre " << min
                      << " y " << max << "." << std::endl;
            continue;
        }

        return valor;
    }
}

// Pide un texto y no lo acepta vacio. Regresa el texto sin espacios en los extremos.
std::string leerTextoNoVacio(const std::string& mensaje) {
    while (true) {
        std::string texto = leerLinea(mensaje);
        if (texto.empty()) {
            std::cout << "El texto no puede ir vacío, intenta de nuevo." << std::endl;
            continue;
        }
        return texto;
    }
}
