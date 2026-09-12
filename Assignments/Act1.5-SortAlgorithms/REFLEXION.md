# Reflexión sobre el uso de Copilot

**Diego Contreras — A00845716**

## 1. ¿Qué algoritmos lograste implementar con mayor facilidad gracias al apoyo de Copilot?

La verdad los que salieron más rápido fueron Bubble Sort, Selection Sort e Insertion Sort. Como son de los primeros que uno ve y ya los había repasado en clase, apenas empezaba a escribir el nombre de la función y Copilot ya me completaba casi todo el bucle. Ahí prácticamente solo tuve que leer la sugerencia, ver que estuviera bien y seguirle. También el Swap Sort fue sencillo porque es muy parecido a esos. Sentí que en esos casos Copilot iba a mi ritmo y no me trababa.

## 2. ¿En qué casos Copilot te dio soluciones correctas de inmediato y en cuáles tuviste que corregir o ajustar la propuesta?

De un jalón me funcionaron los ordenamientos sencillos y también la parte de medir el tiempo con chrono, esa casi no la toqué. Donde sí batallé un poco más fue en Quick Sort y en Merge Sort. En el Quick Sort la primera versión que me sugirió agarraba siempre el último elemento como pivote, y eso se ponía bien lento cuando los datos ya venían ordenados. En el Merge Sort tuve que estar revisando los índices de las mitades porque en una de esas se salía del rango. Y otra cosa que ajusté fue lograr que todos sirvieran también para string y no nada más para números, ahí tuve que acomodarlos bien como templates.

## 3. ¿Consideras que Copilot te ayudó a ahorrar tiempo o más bien te obligó a pensar más sobre cómo funciona el algoritmo?

Yo diría que las dos cosas al mismo tiempo. Sí me ahorró harto tiempo en lo repetitivo, como armar el menú, generar los datos al azar y guardar el CSV, eso lo escribió rapidísimo. Pero para que de verdad quedara bien igual tuve que entender qué estaba pasando, sobre todo para decidir cómo elegir el pivote del Quick Sort y para asegurarme de que el tiempo que medía fuera solo el del ordenamiento y no el de generar o imprimir. O sea, me ayudó, pero no me quitó el tener que pensar.

## 4. Escribe un ejemplo concreto donde Copilot no resolvió el problema directamente y tuviste que razonar la solución.

El caso más claro fue con el Quick Sort cuando lo probé con 100,000 elementos que ya estaban ordenados. Con la versión que me había sugerido, que tomaba el último como pivote, el programa se ponía lentísimo y hasta sentía que se iba a trabar por lo profunda que se hacía la recursión. Copilot no me lo arregló solo, tuve que sentarme a pensar por qué pasaba. Ahí me di cuenta de que el problema era el pivote, y decidí cambiarlo para que tomara la mediana entre el primero, el de en medio y el último. Con ese cambio ya repartía mejor los datos y dejó de trabarse.

## 5. ¿Qué hubieras hecho diferente si no hubieras tenido acceso a Copilot para esta actividad?

Creo que hubiera avanzado más lento, sobre todo en la parte aburrida de escribir el menú, la generación de datos y el guardado del archivo, que es donde Copilot me ahorró tiempo. Seguramente hubiera tenido que revisar más mis apuntes y buscar ejemplos en internet para acordarme bien de cómo van Merge Sort y Quick Sort. Al final pienso que hubiera llegado a algo parecido, pero me hubiera tardado bastante más y con más prueba y error.
