# Notas para la reflexión

Apuntes que se van juntando fase por fase. Materia prima para ReflexEvidencia1.pdf.

## Fase 3, bubble sort en los dos archivos

Bubble sort tardó 100.201 ms en log607-1 y 0.268 ms en log607-2. Es unas 370 veces
más rápido en el segundo archivo, aunque los dos tienen exactamente los mismos 6,818
registros y solo cambia el orden en que vienen.

La razón es la bandera que corta las pasadas. Bubble sort hace una pasada completa
comparando vecinos, y si esa pasada no intercambió nada, significa que ya está
ordenado y se detiene. En log607-1 los datos están muy revueltos, así que hacen
falta miles de pasadas. En log607-2 casi todo ya está en su lugar, así que después
de unas cuantas pasadas ya no hay nada que intercambiar y el algoritmo se sale.

Lo que esto enseña es que la complejidad O(n²) del peor caso no cuenta toda la
historia. El trabajo real de bubble sort depende de qué tan desordenados vienen los
datos, no nada más de cuántos son. Con datos casi ordenados se acerca a O(n).

También comprobé que el orden es estable. Los 18 pares de registros con la misma
fecha y hora conservan el orden en el que venían en el archivo, porque el algoritmo
solo intercambia cuando el de la derecha es estrictamente menor. Si la comparación
fuera con menor o igual, intercambiaría los duplicados sin necesidad y perdería esa
propiedad.
