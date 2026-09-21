// Diego Contreras
// A00845716

// Convierte una fecha de texto en un numero comparable y lee los archivos de log.

#include "registro.h"
#include <fstream>
#include <iostream>
#include <cctype>

// Los meses van en orden, así la posición en el arreglo más 1 es el número del mes.
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
std::string limpiarEspacios(const std::string& texto) {
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

// Regresa cuántos días tiene un mes, considerando años bisiestos.
static int diasDelMes(int mes, int anio) {
    if (mes == 2) {
        bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
        return bisiesto ? 29 : 28;
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    }
    return 31;
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
    if (dia < 1 || dia > diasDelMes(mes, anio)) return false;
    if (hora < 0 || hora > 23) return false;
    if (min < 0 || min > 59)   return false;
    if (seg < 0 || seg > 59)   return false;

    // El año va primero para que pese más que el mes, el mes más que el día, y así.
    clave = (long long)anio * 10000000000LL
          + (long long)mes  * 100000000LL
          + (long long)dia  * 1000000LL
          + (long long)hora * 10000LL
          + (long long)min  * 100LL
          + (long long)seg;
    return true;
}

// Hace lo contrario de fechaAClave: toma 20241002230424 y regresa
// "Oct 02 2024 23:04:24". Se usa para mostrarle al usuario el periodo
// que cubre el archivo antes de pedirle las fechas de la busqueda.
std::string claveATexto(long long clave) {
    int seg  = (int)( clave % 100);
    int min  = (int)((clave / 100) % 100);
    int hora = (int)((clave / 10000) % 100);
    int dia  = (int)((clave / 1000000) % 100);
    int mes  = (int)((clave / 100000000) % 100);
    int anio = (int)( clave / 10000000000LL);

    // Los numeros de un digito llevan un cero adelante, igual que en el log.
    auto dosDigitos = [](int n) {
        std::string s = std::to_string(n);
        return s.size() == 1 ? "0" + s : s;
    };

    return MESES[mes - 1] + " " + dosDigitos(dia) + " " + std::to_string(anio)
         + " " + dosDigitos(hora) + ":" + dosDigitos(min) + ":" + dosDigitos(seg);
}

// Toma una linea del log, saca la fecha de los primeros 20 caracteres y
// guarda la clave junto con la linea completa. Regresa false si la linea no sirve.
bool parsearLinea(const std::string& linea, Registro& reg) {
    // Tiene que haber fecha (20 caracteres) y algo despues: la IP y el mensaje.
    if (linea.size() <= 21) {
        return false;
    }

    long long clave = 0;
    if (!fechaAClave(linea.substr(0, 20), clave)) {
        return false;
    }

    // Despues de la fecha va un espacio y luego el resto de los datos.
    if (linea[20] != ' ' || limpiarEspacios(linea.substr(21)).empty()) {
        return false;
    }

    reg.clave = clave;
    reg.linea = linea;
    return true;
}

// Abre el archivo y guarda cada linea valida en el vector.
// Las lineas rotas se avisan con su numero y se saltan, sin detener la lectura.
bool leerArchivo(const std::string& ruta, std::vector<Registro>& datos) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo abrir el archivo \"" << ruta << "\"." << std::endl;
        std::cout << "Revisa que exista y que lo estes corriendo desde la carpeta Evidence1."
                  << std::endl;
        return false;
    }

    std::string linea;
    int numeroLinea = 0;
    int ignoradas = 0;

    while (std::getline(archivo, linea)) {
        numeroLinea++;

        // Si el archivo viene de Windows cada linea termina en \r y hay que quitarlo.
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }

        if (limpiarEspacios(linea).empty()) {
            std::cout << "Linea " << numeroLinea << " ignorada porque esta vacia." << std::endl;
            ignoradas++;
            continue;
        }

        Registro reg;
        if (!parsearLinea(linea, reg)) {
            std::cout << "Linea " << numeroLinea << " ignorada por formato invalido."
                      << std::endl;
            ignoradas++;
            continue;
        }

        datos.push_back(reg);
    }

    archivo.close();

    if (ignoradas > 0) {
        std::cout << "Se ignoraron " << ignoradas << " lineas de " << numeroLinea
                  << " en total." << std::endl;
    }
    return true;
}

// Escribe los registros en un archivo, una linea por registro.
// Guarda la linea original tal cual para que la salida tenga el mismo
// formato que la entrada, sin volver a armarla campo por campo.
bool escribirArchivo(const std::string& ruta, const std::vector<Registro>& datos) {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo crear el archivo \"" << ruta << "\"." << std::endl;
        std::cout << "Revisa que la carpeta exista." << std::endl;
        return false;
    }

    for (const Registro& reg : datos) {
        archivo << reg.linea << '\n';
    }

    archivo.close();
    return true;
}
