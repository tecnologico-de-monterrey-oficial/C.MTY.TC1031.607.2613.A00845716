# Act1.5 - Algoritmos de Ordenamiento

**Diego Contreras — A00845716**

## Objetivo

Aplicación en C++ que genera vectores con datos aleatorios, los ordena con
distintos algoritmos de ordenamiento, mide cuánto tarda cada uno (en
**nanosegundos**) y hace una comparación de rendimiento. Los resultados de la
comparación se guardan en un archivo CSV y se pueden graficar con un script de
Python.

## Algoritmos implementados

Todos ordenan de **menor a mayor (ascendente)** y están hechos a mano (sin
`std::sort`):

1. Swap Sort
2. Bubble Sort (con optimización: termina antes si una pasada no hace cambios)
3. Selection Sort
4. Insertion Sort
5. Merge Sort (recursivo, con función de mezcla propia)
6. Quick Sort (pivote por mediana de tres, para evitar el peor caso)
7. Shell Sort — **algoritmo extra no visto en clase**

Están hechos como funciones *template*, así que sirven para los tres tipos de
dato sin repetir el código.

## Tipos de dato y tamaños

- Tipos: **int**, **double**, **string**
- Tamaños: **1,000**, **10,000** y **100,000** elementos

Los datos se generan al azar con la librería `<random>`. Los strings son
cadenas aleatorias de 5 a 10 caracteres alfanuméricos.

## Estructura de archivos

| Archivo               | Qué contiene                                             |
|-----------------------|----------------------------------------------------------|
| `main.cpp`            | Menú interactivo del programa                            |
| `sorting.h`           | Los 7 algoritmos de ordenamiento (templates)            |
| `data_generator.h`    | Generación de vectores aleatorios (int, double, string) |
| `benchmark.h`         | Medición de tiempos y análisis comparativo + CSV        |
| `test_correctitud.cpp`| Prueba interna que verifica que todo ordene bien        |
| `grafica.py`          | Script de Python que grafica el CSV                      |
| `requirements.txt`    | Dependencias de Python (pandas, matplotlib)             |
| `REFLEXION.md`        | Reflexión sobre el uso de Copilot                        |

## Cómo compilar

Se usa el estándar **C++17**:

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o sortapp
```

(Opcional) Compilar y correr la prueba de correctitud:

```bash
g++ -std=c++17 -O2 test_correctitud.cpp -o test_correctitud
./test_correctitud
```

## Cómo ejecutar

```bash
./sortapp
```

## Cómo usar el menú

Al abrir el programa aparece un menú:

```
1) Ordenar un vector (elegir tipo, tamano y algoritmo)
2) Analisis comparativo completo (genera CSV)
3) Salir
```

- **Opción 1:** eliges el tipo de dato, el tamaño (1,000 / 10,000 / 100,000) y
  el algoritmo. El programa:
  1. genera el vector,
  2. mide **solo** el ordenamiento,
  3. muestra el tiempo en nanosegundos,
  4. verifica que quedó ordenado,
  5. y después te deja ver el vector ordenado (completo, resumido o no verlo).

  La impresión del vector **no** cuenta dentro del tiempo medido.

- **Opción 2:** corre el análisis comparativo completo (los 7 algoritmos, con
  los 3 tipos de dato y los 3 tamaños) y guarda todo en el CSV.

Todas las entradas del menú están validadas: si escribes algo que no es una
opción válida, el programa te lo vuelve a pedir sin cerrarse.

## Análisis comparativo y CSV

Desde la **opción 2** del menú se genera el archivo:

```
resultados_tiempos.csv
```

que queda en la misma carpeta desde donde ejecutas el programa. Tiene esta
estructura (una fila por combinación algoritmo/tipo de dato → 21 filas + la
cabecera):

```
algoritmo,tipo_dato,tiempo1000,tiempo10000,tiempo100000
```

Todos los tiempos están en **nanosegundos**. Cada algoritmo recibe siempre una
**copia del mismo vector original** para que la comparación sea justa (nunca se
le pasa un vector que ya ordenó otro algoritmo).

## Cómo generar la gráfica (bonus)

Necesitas Python 3 con pandas y matplotlib:

```bash
pip install -r requirements.txt
```

Luego, con el CSV ya generado:

```bash
python3 grafica.py
```

Esto crea la imagen `grafica_tiempos.png` con una gráfica por cada tipo de dato,
comparando los tiempos de los algoritmos según el tamaño del vector. Se usa
**escala logarítmica** porque las diferencias entre los algoritmos O(n²) y los
O(n log n) son enormes y así se ven mejor.

## Nota importante sobre tiempos (algoritmos O(n²))

Swap Sort, Bubble Sort, Selection Sort e Insertion Sort son de complejidad
aproximada **O(n²)**, así que ordenar **100,000** elementos con ellos puede
tardar **varios minutos** (sobre todo con strings). Esto es normal y esperado;
la actividad pide medir ese tamaño y el programa lo hace de verdad. Por eso el
análisis comparativo muestra un aviso antes de empezar.
