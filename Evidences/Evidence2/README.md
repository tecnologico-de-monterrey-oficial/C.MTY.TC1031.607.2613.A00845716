# Evidencia 2

**Autor:** Diego Contreras Alvarez
**Matrícula:** A00845716
**Curso:** Programación de Estructuras de Datos y Algoritmos Fundamentales

## Nota sobre los nombres de archivos

Hay tres detalles de nombres que conviene aclarar desde el inicio:

- **log608 contra log607.** Las instrucciones hablan de archivos `log608`, pero los que nos entregaron se llaman `log607-1.txt` y `log607-2.txt`. Se usan con el nombre con el que llegaron.
- **La descripción viene al revés.** Las instrucciones dicen otra cosa, pero en los archivos reales `log607-1.txt` es el aleatorio y `log607-2.txt` es el casi ordenado. Lo comprobé revisando los archivos.
- **Archivo de salida.** La salida se llama `output608.out`, tal cual lo piden las instrucciones, porque es el nombre exacto que se va a buscar al calificar. Por eso este nombre no cambia a 607 como los de entrada.

## Con qué archivo se generó output608.out

El `out/output608.out` que se entrega se generó ordenando **`log607-1.txt`** con la opción 1 (Merge sort sobre la lista doble).

Se eligió ese archivo porque las instrucciones lo llaman el archivo principal, aunque describan los dos archivos al revés.

Importa decirlo porque las salidas de los dos logs no son idénticas. Los dos tienen los mismos 6818 registros, pero hay registros con exactamente la misma fecha y hora. Como el Merge sort es estable, esos empates quedan en el orden en que venían en cada archivo de entrada, y ese orden cambia de un archivo al otro. Hay 18 pares de registros con la misma fecha y hora; en 10 de esos pares el orden cambia entre la salida de un archivo y la del otro.

Para volver a generarlo:

    bash scripts/run.sh

El script compila y abre el programa. Ahí se escoge el archivo 1, luego la opción 1 (Ordenar) y al final la opción 5 (Salir).

## Estructura de carpetas

- `data/` contiene los archivos de entrada: log607-1.txt (aleatorio), log607-2.txt (casi ordenado) y prueba-malformada.txt (archivo pequeño con errores a propósito, para probar el manejo de líneas inválidas).
- `src/` contiene el código fuente (.cpp).
- `include/` contiene los archivos de cabecera (.h).
- `build/` guarda el ejecutable compilado y no se sube al repositorio.
- `out/` guarda las salidas que genera la app, entre ellas `output608.out`.
- `docs/` contiene los documentos de la entrega.
- `scripts/` contiene `run.sh`, que compila y ejecuta el programa en un paso.
