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

También se puede usar el script `scripts/run.sh`, que compila y ejecuta el programa en un solo paso. Funciona desde cualquier carpeta, porque se mueve solo a `Evidence1` antes de compilar.

El proyecto compila sin advertencias con `-Wall -Wextra`.

## Formato de los datos

Cada línea del log tiene el formato:

    Mmm dd aaaa hh:mm:ss IP mensaje

Por ejemplo `Oct 02 2024 23:04:24 10.14.47.219 Social engineering attacks`. El mensaje puede contener espacios.

Para ordenar y buscar, la fecha se convierte en un número con el formato AAAAMMDDhhmmss (en el ejemplo, 20241002230424), así comparar dos fechas es comparar dos números. El programa conserva la línea original completa para que los archivos de salida tengan exactamente el mismo formato que la entrada.

Las líneas vacías o con formato inválido se reportan en pantalla con su número de línea y se ignoran, sin detener la lectura del resto del archivo. El archivo `data/prueba-malformada.txt` sirve para comprobar ese comportamiento: tiene 6 líneas, de las cuales 2 son registros válidos y 4 se reportan.

Si el archivo no se puede abrir, el programa avisa con la ruta que intentó abrir y no se cierra de forma inesperada.

## Uso del programa

Al ejecutar el programa aparece un menú con cuatro opciones:

1. **Ordenar un archivo.** Permite elegir entre log607-1.txt (desordenado), log607-2.txt (casi ordenado) y prueba-malformada.txt, y carga sus registros. El tercero es un archivo pequeño con errores a propósito (una línea vacía, una fecha imposible, texto que no es un registro y un 30 de febrero) que sirve para mostrar el manejo de errores de lectura dentro de la propia aplicación. Para ese archivo no se guardan las copias identificadas, porque no es uno de los logs de la actividad.
2. **Buscar por rango de fechas.** Solo está disponible después de ordenar, porque la búsqueda binaria necesita datos ordenados.
3. **Ver historial de corridas.**
0. **Salir.**

Todas las opciones se eligen escribiendo el número y presionando Enter. Si se escribe algo que no es un número válido, que queda fuera del rango o que viene vacío, el programa explica qué se esperaba y vuelve a preguntar, sin cerrarse.

Cada vez que se carga un archivo, los datos quedan sin ordenar, así que la búsqueda vuelve a bloquearse hasta que se ordene de nuevo.

El programa solo termina con la opción 0 o presionando Ctrl + D, que cierra la entrada.

Los mensajes de la consola no llevan acentos a propósito, para que se muestren correctamente en cualquier terminal, incluida la de Windows. Los comentarios del código sí los llevan.

### Ejemplo de sesión

Ordenar log607-2.txt con insertion sort y después buscar los eventos del 16 de diciembre de 2025. Lo que escribe el usuario va después de cada dos puntos.

```
========================================
  Analizador de logs 607
========================================
1. Ordenar un archivo
2. Buscar por rango de fechas
3. Ver historial de corridas
0. Salir
Opcion: 1

Que archivo quieres usar?
1. log607-1.txt (desordenado)
2. log607-2.txt (casi ordenado)
0. Regresar al menu
Archivo: 2
Se cargaron 6818 registros de log607-2.txt (casi ordenado).

Que algoritmo quieres usar?
1. Bubble sort
2. Selection sort
3. Insertion sort
4. Merge sort
5. Quick sort (mediana de tres)
6. Swap sort
7. Shell sort
8. Quick sort (pivote al final, variante)
0. Regresar al menu
Algoritmo: 3

Vas a ordenar 6818 registros de log607-2.txt (casi ordenado) con Insertion sort.

Antes de ordenar, haz tu prediccion.
Que tan rapido crees que sera este algoritmo con este archivo?
1. Rapido (menos de 10 ms)
2. Medio (entre 10 y 60 ms)
3. Lento (mas de 60 ms)
Prediccion: 1
Por que? Menciona el tamano de los datos y que tan ordenado esta el archivo: el archivo ya viene casi ordenado, insertion deberia hacer pocos movimientos

----------------------------------------
Algoritmo:    Insertion sort
Archivo:      log607-2.txt (casi ordenado)
Registros:    6818
Tiempo:       1.065 ms
Complejidad:  mejor caso O(n), peor caso O(n^2)
Estable:      si
Prediccion:   rapido
Resultado:    rapido
Coincidio:    si
Verificacion: datos ordenados correctamente
Salida guardada en out/output607.txt
Copia guardada en out/output607_log2.txt
Corrida guardada en out/corridas.csv
----------------------------------------
```

Después, con la opción 2:

```
Opcion: 2

Hay 6818 registros ordenados.
Los datos van de Sep 08 2024 00:22:43 a Sep 07 2026 23:50:40.
Las fechas que escribas no tienen que existir en el archivo.
Fecha de inicio: Dec 16 2025 00:00:00
Fecha de fin:    Dec 16 2025 23:59:59

Registros encontrados: 13

Dec 16 2025 04:30:29 10.14.22.152 Application error
Dec 16 2025 05:01:57 10.14.246.43 Anomalous User Activity
Dec 16 2025 05:01:57 10.14.215.155 SQL injection
...
Resultado guardado en out/range607.txt
Copia guardada en out/range607_log2.txt
```

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

Además de `output607.txt` y `range607.txt`, que corresponden siempre a la operación más reciente, el programa guarda una copia identificada por archivo de entrada (`output607_log1.txt`, `output607_log2.txt`, `range607_log1.txt` y `range607_log2.txt`), de modo que queden disponibles los resultados de ambos archivos sin que uno sobrescriba al otro.

Cada corrida ordena una copia de los datos tal como vienen del archivo, de modo que el tiempo medido no depende de las corridas anteriores. Los datos originales nunca se modifican.

Antes de guardar, el programa comprueba que el vector quedó de menor a mayor. Si la comprobación falla, avisa y no marca los datos como ordenados, así la búsqueda no puede correr sobre un resultado malo.

## Búsqueda por rango de fechas

La búsqueda se hace sobre los datos ya ordenados y solo está disponible después de ordenar. Se piden una fecha de inicio y una de fin en el formato `Mmm dd aaaa hh:mm:ss`, por ejemplo `Oct 02 2024 23:04:24`. Las fechas no tienen que existir en el archivo.

El subrango se encuentra con dos búsquedas binarias. La primera localiza la posición inicial, que es la primera cuya fecha es mayor o igual a la fecha de inicio. La segunda localiza la posición final, que es la primera cuya fecha es estrictamente mayor a la fecha de fin. El resultado es el bloque continuo entre ambas posiciones. El costo es O(log n) para encontrar los límites más O(k) para copiar los k registros del rango.

**Política de límites y de fechas repetidas.** El rango es inclusivo en los dos extremos. Si la fecha de inicio o la de fin coincide con uno o más registros, todos ellos se incluyen. Ninguna de las dos búsquedas se detiene al encontrar una coincidencia, sino que sigue acotando hasta la frontera, de modo que con fechas repetidas no se pierde ni se duplica ningún registro. Esto es relevante porque los archivos contienen 18 pares de registros con la misma fecha y hora.

Si la fecha de inicio es posterior a la de fin, el programa lo reporta y vuelve a pedir ambas fechas, en lugar de intercambiarlas, para no asumir lo que el usuario quiso decir.

Los resultados se muestran en pantalla y se guardan en `out/range607.txt` con el mismo formato de la entrada. Cuando hay más de 20 resultados, en pantalla se muestran los primeros y los últimos diez, y el archivo siempre contiene la lista completa. Si el rango no tiene registros, el archivo se genera vacío.

## Nota sobre nombres de archivos

Las instrucciones mencionan en algunos puntos output608.txt, log608-1.txt y log608-2.txt. Se interpretan como errores de dedo y se usan output607.txt, range607.txt, log607-1.txt y log607-2.txt.

## Política de uso de IA

(Pendiente, se completa al final)

## Video

Video explicativo: [ver video](https://youtu.be/5iGMwLNZImI)

En el video se muestra la aplicación corriendo con insertion sort sobre los dos archivos de entrada, se explica la implementación de la búsqueda binaria por rango línea por línea, y se demuestra el manejo de fechas repetidas buscando un rango cuyos extremos caen en una fecha duplicada.

El video incluye marcas de tiempo en su descripción para poder ir directo a cada sección.
