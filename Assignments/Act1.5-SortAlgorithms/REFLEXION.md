# Reflexión sobre el uso de Copilot

**Diego Contreras — A00845716**

> Nota: este documento es un borrador basado en el desarrollo de la actividad.
> Las respuestas describen una experiencia personal, así que revísalo y
> ajústalo con lo que realmente te pasó a ti antes de entregar. Los puntos
> marcados con *(personaliza)* son los más importantes de revisar.

## 1. ¿Qué algoritmos lograste implementar con mayor facilidad gracias al apoyo de Copilot?

Los algoritmos más sencillos y "clásicos" fueron los más fáciles de escribir
con ayuda de Copilot: **Bubble Sort**, **Selection Sort** e **Insertion Sort**.
Son patrones muy conocidos, así que la sugerencia salía casi completa y solo
había que revisarla. *(personaliza)*

## 2. ¿En qué casos Copilot te dio soluciones correctas de inmediato y en cuáles tuviste que corregir o ajustar la propuesta?

- **Correctas de inmediato:** los ordenamientos simples (bubble, selection,
  insertion) y la parte de medir el tiempo con `<chrono>`.
- **Tuve que corregir o ajustar:**
  - **Quick Sort**, porque una versión simple (tomando siempre el último
    elemento como pivote) se vuelve muy lenta y muy profunda cuando los datos ya
    vienen ordenados o al revés. Hubo que cambiar el pivote a la **mediana de
    tres** para que no fallara ni se hiciera lentísimo.
  - **Merge Sort**, para cuidar bien los índices de las mitades y no salirse del
    rango del vector.
  - Que todos los algoritmos funcionaran con **string** además de int y double,
    usándolos como *templates*. *(personaliza)*

## 3. ¿Consideras que Copilot te ayudó a ahorrar tiempo o más bien te obligó a pensar más sobre cómo funciona el algoritmo?

Las dos cosas. Me **ahorró tiempo** en lo repetitivo (escribir los bucles, el
menú, la parte del CSV). Pero para que todo quedara bien **sí tuve que entender**
cómo funciona cada algoritmo, sobre todo para decidir el pivote de Quick Sort y
para asegurarme de que la medición del tiempo no incluyera la generación de
datos ni la impresión. Copilot ayuda, pero no piensa por uno. *(personaliza)*

## 4. Escribe un ejemplo concreto donde Copilot no resolvió el problema directamente y tuviste que razonar la solución.

El caso más claro fue el **Quick Sort con 100,000 elementos ya ordenados**. La
primera versión sugerida usaba el último elemento como pivote y, con datos
ordenados, la recursión se hacía tan profunda que podía tronar o volverse
lentísima. Copilot no lo resolvió solo: tuve que darme cuenta del problema y
cambiar la estrategia a **elegir el pivote como la mediana entre el primero, el
de en medio y el último**, que reparte mejor los datos. *(personaliza)*

## 5. ¿Qué hubieras hecho diferente si no hubieras tenido acceso a Copilot para esta actividad?

Habría avanzado más lento, sobre todo en la parte repetitiva (el menú, la
generación de datos y el guardado del CSV), y probablemente habría consultado
más apuntes y ejemplos en internet para recordar los detalles de Merge Sort y
Quick Sort. Creo que el resultado final habría sido parecido, pero me habría
tomado más tiempo llegar a él. *(personaliza)*
