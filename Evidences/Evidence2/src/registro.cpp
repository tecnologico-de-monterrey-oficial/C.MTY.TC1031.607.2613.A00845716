// Diego Contreras
// A00845716

// Convierte una fecha de texto en un numero comparable y separa una linea
// del log en sus campos. Viene de registro.cpp de la Evidencia 1.
// Leer y escribir archivos ya no vive aqui: ahora pasa por la Fila y la lista.

#include "registro.h"
#include <sstream>
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

// Revisa que el texto parezca una IP: solo digitos y puntos, con al menos
// un punto. Asi una palabra de la descripcion no se confunde con la IP.
static bool pareceIP(const std::string& texto) {
    if (texto.empty() || texto.find('.') == std::string::npos) {
        return false;
    }
    for (char c : texto) {
        if (!isdigit((unsigned char)c) && c != '.') {
            return false;
        }
    }
    return true;
}

// Separa una linea como "Sep 29 2024 14:37:38 10.14.19.188 SQL injection"
// en sus campos. Revisa las partes en orden y, en cuanto una falla, deja
// el motivo y regresa false. Si todo esta bien llena reg y regresa true.
bool parsearLinea(const std::string& linea, Registro& reg, std::string& motivo) {
    // 1. Una linea sin nada (o solo espacios) no tiene datos.
    if (limpiarEspacios(linea).empty()) {
        motivo = "linea vacia";
        return false;
    }

    // Separar las primeras cinco palabras. Lo que sobra es la descripcion,
    // que puede tener varias palabras.
    std::istringstream partes(linea);
    std::string mes, dia, anio, hora, ip, resto;
    partes >> mes >> dia >> anio >> hora >> ip;
    std::getline(partes, resto);
    std::string descripcion = limpiarEspacios(resto);

    // 2. El mes tiene que ser Jan a Dec.
    int numMes = mesANumero(mes);
    if (numMes == -1) {
        motivo = "mes invalido";
        return false;
    }

    // 3. El dia lleva 2 digitos, el anio 4, y ese dia tiene que existir
    //    en ese mes (por ejemplo, Feb 30 no existe).
    if (dia.size() != 2 || !sonDigitos(dia, 0, 2) ||
        anio.size() != 4 || !sonDigitos(anio, 0, 4)) {
        motivo = "fecha imposible";
        return false;
    }
    int numDia = std::stoi(dia);
    int numAnio = std::stoi(anio);
    if (numDia < 1 || numDia > diasDelMes(numMes, numAnio)) {
        motivo = "fecha imposible";
        return false;
    }

    // 4. La hora va como hh:mm:ss y cada parte en su rango.
    if (hora.size() != 8 || hora[2] != ':' || hora[5] != ':' ||
        !sonDigitos(hora, 0, 2) || !sonDigitos(hora, 3, 2) || !sonDigitos(hora, 6, 2)) {
        motivo = "hora invalida";
        return false;
    }
    int h = std::stoi(hora.substr(0, 2));
    int m = std::stoi(hora.substr(3, 2));
    int s = std::stoi(hora.substr(6, 2));
    if (h > 23 || m > 59 || s > 59) {
        motivo = "hora invalida";
        return false;
    }

    // 5. Despues de la hora va la IP.
    if (!pareceIP(ip)) {
        motivo = "falta la IP";
        return false;
    }

    // 6. Despues de la IP va la descripcion del evento.
    if (descripcion.empty()) {
        motivo = "falta la descripcion";
        return false;
    }

    // 7. Armar la clave con fechaAClave. Como ya se reviso todo, aqui no
    //    deberia fallar, pero se revisa por si acaso.
    long long clave = 0;
    if (!fechaAClave(mes + " " + dia + " " + anio + " " + hora, clave)) {
        motivo = "fecha imposible";
        return false;
    }

    reg.mes = mes;
    reg.dia = numDia;
    reg.anio = numAnio;
    reg.hora = hora;
    reg.ip = ip;
    reg.descripcion = descripcion;
    reg.clave = clave;
    reg.linea = linea;
    motivo = "";
    return true;
}
