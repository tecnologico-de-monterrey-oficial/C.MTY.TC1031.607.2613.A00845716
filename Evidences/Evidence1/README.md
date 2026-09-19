# Evidencia 1: Ordenamiento y búsqueda en logs

**Autor:** Diego Contreras Alvarez
**Matrícula:** A00845716
**Curso:** Programación de Estructuras de Datos y Algoritmos Fundamentales (TC1031), grupo 607

## Descripción

Aplicación de consola en C++ que lee un log de eventos de seguridad, lo ordena por fecha y hora con el algoritmo que elija el usuario, mide el tiempo de ejecución y busca los registros dentro de un rango de fechas usando búsqueda binaria.

## Estructura de carpetas

- `data/` contiene los archivos de entrada log607-1.txt (desordenado) y log607-2.txt (casi ordenado).
- `src/` contiene el código fuente (.cpp).
- `include/` contiene los archivos de cabecera (.h) con las estructuras y los algoritmos.
- `build/` guarda el ejecutable compilado y no se sube al repositorio.
- `out/` guarda las salidas que genera la app: output607.txt, range607.txt y corridas.csv.
- `docs/` contiene EvidenciasPruebas.pdf y ReflexEvidencia1.pdf.
- `scripts/` queda disponible para scripts de compilación o ejecución.

## Compilación y ejecución

Desde la carpeta `Evidences/Evidence1`:

    g++ -std=c++20 -O2 -Iinclude src/*.cpp -o build/app
    ./build/app

## Formato de los datos

Cada línea del log tiene el formato:

    Mmm dd aaaa hh:mm:ss IP mensaje

Por ejemplo `Oct 02 2024 23:04:24 10.14.47.219 Social engineering attacks`. El mensaje puede contener espacios.

Para ordenar y buscar, la fecha se convierte en un número con el formato AAAAMMDDhhmmss (en el ejemplo, 20241002230424), así comparar dos fechas es comparar dos números. El programa conserva la línea original completa para que los archivos de salida tengan exactamente el mismo formato que la entrada.

Las líneas vacías o con formato inválido se reportan en pantalla con su número de línea y se ignoran, sin detener la lectura del resto del archivo. El archivo `data/prueba-malformada.txt` sirve para comprobar ese comportamiento: tiene 5 líneas, de las cuales 2 son registros válidos y 3 se reportan.

Si el archivo no se puede abrir, el programa avisa con la ruta que intentó abrir y no se cierra de forma inesperada.

## Uso del programa

Al ejecutar el programa aparece un menú con cuatro opciones:

1. **Ordenar un archivo.** Permite elegir entre log607-1.txt (desordenado) y log607-2.txt (casi ordenado) y carga sus registros.
2. **Buscar por rango de fechas.** Solo está disponible después de ordenar, porque la búsqueda binaria necesita datos ordenados.
3. **Ver historial de corridas.**
0. **Salir.**

Todas las opciones se eligen escribiendo el número y presionando Enter. Si se escribe algo que no es un número válido, que queda fuera del rango o que viene vacío, el programa explica qué se esperaba y vuelve a preguntar, sin cerrarse.

Cada vez que se carga un archivo, los datos quedan sin ordenar, así que la búsqueda vuelve a bloquearse hasta que se ordene de nuevo.

El programa solo termina con la opción 0 o presionando Ctrl + D, que cierra la entrada.

Los mensajes de la consola no llevan acentos a propósito, para que se muestren correctamente en cualquier terminal, incluida la de Windows. Los comentarios del código sí los llevan.

## Algoritmos disponibles

| # | Algoritmo | Mejor caso | Peor caso | Estable |
|---|---|---|---|---|
| 1 | Bubble sort (con bandera de salida temprana) | O(n) | O(n^2) | Sí |
| 2 | Selection sort | O(n^2) | O(n^2) | No |
| 3 | Insertion sort | O(n) | O(n^2) | Sí |
| 4 | Merge sort | O(n log n) | O(n log n) | Sí |
| 5 | Quick sort (pivote por mediana de tres) | O(n log n) | O(n^2) | No |
| 6 | Swap sort | O(n^2) | O(n^2) | No |
| 7 | Shell sort (saltos n/2, n/4, ..., 1) | O(n log n) | O(n^2) | No |
| 8 | Quick sort con pivote al final (variante) | O(n log n) | O(n^2) | No |

Los algoritmos 1 a 7 son los vistos en clase hasta la Actividad 1.5. El 8 no es un algoritmo de clase, es una variante que se agregó para comparar. Usa el último elemento como pivote, lo que con datos casi ordenados lo acerca a su peor caso, y así se puede ver el problema que resuelve la mediana de tres del algoritmo 5.

Merge sort usa un solo vector auxiliar que se crea al inicio y se reutiliza en toda la recursión, en lugar de crear vectores nuevos en cada llamada.

Todos los algoritmos son plantillas que ordenan de menor a mayor comparando únicamente con `<`, a través del operador `<` definido sobre la fecha del registro.

## Predicción y registro de corridas

Antes de cada ordenamiento el programa pide una predicción (rápido, medio o lento) y una razón. Después de ordenar, clasifica el tiempo medido con estos umbrales y dice si coincidió con la predicción:

- Rápido: menos de 10 ms
- Medio: entre 10 y 60 ms
- Lento: más de 60 ms

Los umbrales se eligieron a partir de los tiempos observados en el equipo de desarrollo, de modo que ningún resultado quede justo en el límite entre dos categorías. En otra computadora los tiempos pueden variar.

Cada corrida se agrega a `out/corridas.csv` con la fecha y hora, el algoritmo, el archivo, el número de registros, el tiempo, la complejidad, la predicción, el resultado, si coincidió y la razón. La opción 3 del menú muestra el historial en forma de tabla.

La razón se guarda entre comillas dobles y las comillas que traiga adentro se escriben dobles, que es la regla del formato CSV. Así una razón con comas no rompe el archivo y Excel lo abre bien.

## Archivos de salida

Después de cada ordenamiento el programa escribe `out/output607.txt` con los registros ordenados cronológicamente, en el mismo formato que el archivo de entrada. El archivo se sobrescribe en cada corrida, así que siempre contiene el resultado de la corrida más reciente.

Cada corrida ordena una copia de los datos tal como vienen del archivo, de modo que el tiempo medido no depende de las corridas anteriores. Los datos originales nunca se modifican.

Antes de guardar, el programa comprueba que el vector quedó de menor a mayor. Si la comprobación falla, avisa y no marca los datos como ordenados, así la búsqueda no puede correr sobre un resultado malo.

## Búsqueda por rango y manejo de duplicados

(Pendiente, Fase 6)

## Nota sobre nombres de archivos

Las instrucciones mencionan en algunos puntos output608.txt, log608-1.txt y log608-2.txt. Se interpretan como errores de dedo y se usan output607.txt, range607.txt, log607-1.txt y log607-2.txt.

## Política de uso de IA

(Pendiente, se completa al final)

## Video

(Pendiente, Fase 9)
