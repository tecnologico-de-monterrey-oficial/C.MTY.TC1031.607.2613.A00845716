# Evidencia 2

**Autor:** Diego Contreras Alvarez
**Matrícula:** A00845716
**Curso:** Programación de Estructuras de Datos y Algoritmos Fundamentales (TC1031), grupo 607

## Nota sobre los nombres de archivos

Hay tres detalles de nombres que conviene aclarar desde el inicio:

- **log608 contra log607.** Las instrucciones hablan de archivos `log608`, pero los que nos entregaron se llaman `log607-1.txt` y `log607-2.txt`. Se usan con el nombre con el que llegaron.
- **La descripción viene al revés.** Las instrucciones dicen otra cosa, pero en los archivos reales `log607-1.txt` es el aleatorio y `log607-2.txt` es el casi ordenado. Lo comprobé revisando los archivos.
- **Archivo de salida.** La salida se llama `output608.out`, tal cual lo piden las instrucciones, porque es el nombre exacto que se va a buscar al calificar. Por eso este nombre no cambia a 607 como los de entrada.

## Estructura de carpetas

- `data/` contiene los archivos de entrada: log607-1.txt (aleatorio), log607-2.txt (casi ordenado) y prueba-malformada.txt (archivo pequeño con errores a propósito, para probar el manejo de líneas inválidas).
- `src/` contiene el código fuente (.cpp).
- `include/` contiene los archivos de cabecera (.h).
- `build/` guarda el ejecutable compilado y no se sube al repositorio.
- `out/` guarda las salidas que genera la app, entre ellas `output608.out`.
- `docs/` contiene los documentos de la entrega.
- `scripts/` contiene `run.sh`, que compila y ejecuta el programa en un paso.
