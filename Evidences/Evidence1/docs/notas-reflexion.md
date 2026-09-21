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

## Fase 4, los ocho algoritmos comparados

Tiempos medidos en mi Mac, con `-O2`, sobre los mismos 6,818 registros:

| Algoritmo | log607-1 (ms) | log607-2 (ms) |
|---|---|---|
| Bubble sort | 101.155 | 0.278 |
| Selection sort | 21.641 | 23.005 |
| Insertion sort | 141.740 | 1.118 |
| Merge sort | 5.031 | 4.596 |
| Quick sort (mediana de tres) | 1.220 | 0.606 |
| Swap sort | 86.434 | 13.778 |
| Shell sort | 7.818 | 5.422 |
| Quick sort (pivote al final) | 1.193 | 38.057 |

**Aclaración sobre la opción 8.** Los siete primeros algoritmos son los vistos en
clase hasta la Act 1.5. El octavo, quick sort con pivote al final, no es un algoritmo
de clase: lo agregué yo como experimento para poder comparar las dos formas de elegir
pivote. La versión oficial de la actividad es la 5, con mediana de tres.

### Por qué selection sort tardó casi lo mismo en los dos archivos

Selection sort siempre recorre toda la parte que le falta para encontrar el mínimo,
sin importar si ya estaba en su lugar. Hace las mismas ~23 millones de comparaciones
en los dos archivos. Es el único que no se entera de que log607-2 ya venía casi
ordenado, porque no tiene ninguna forma de detectarlo: no hay bandera que revisar ni
condición que lo corte antes.

### Por qué quick sort se hace lento con datos casi ordenados

Depende de cómo se elija el pivote, y esto lo comprobé con las dos versiones.

Con pivote al final, en log607-2 el pivote resulta ser casi siempre el mayor del
pedazo, porque los datos ya vienen en orden. Entonces la partición deja todo de un
lado y nada del otro, y en vez de dividir el problema a la mitad cada vez, lo reduce
de uno en uno. Pasó de 1.193 ms en el desordenado a 38.057 ms en el casi ordenado,
32 veces más lento justo con los datos que uno pensaría que son más fáciles.

Con mediana de tres, que es la versión de la Act 1.5, eso no pasa: 1.220 ms y
0.606 ms. Escoger la mediana entre el primero, el de en medio y el último evita que
el pivote sea sistemáticamente el extremo. Esa es exactamente la razón por la que
existe esa mejora.

### Por qué insertion sort NO fue el más rápido, aunque debería

Este fue el resultado que menos esperaba y es el más interesante. Insertion sort
tardó 141.740 ms en log607-1, más que bubble sort. En los libros insertion siempre
le gana a bubble.

La causa no es el algoritmo, es lo que cuesta cada operación con mi tipo de dato.
Un Registro trae un std::string adentro. Bubble sort mueve datos con std::swap, que
para un string solo intercambia punteros y cuesta lo mismo sin importar qué tan largo
sea el texto. Insertion sort mueve datos con asignación (`v[j+1] = v[j]`), y eso
copia el texto completo carácter por carácter.

Lo comprobé ordenando las mismas fechas pero guardadas como simples long long, sin
el string:

| | bubble | insertion |
|---|---|---|
| Registro completo (con string) | 107.018 ms | 112.478 ms |
| solo la clave (long long) | 31.385 ms | 6.619 ms |

Con datos baratos de mover, insertion es 5 veces más rápido que bubble, que es el
resultado del libro. Con datos caros de mover, la ventaja se borra.

La conclusión es que contar operaciones no basta. La notación O grande supone que
todas las operaciones cuestan igual, y aquí no es cierto: una comparación es barata
(comparar dos números) pero un movimiento es caro (copiar un string).

**Recomendación**: cambiar las asignaciones por `std::move` en insertion sort lo
bajó de 141.740 ms a 25.652 ms, 5.5 veces más rápido, sin tocar la lógica. No lo
dejé en el proyecto porque el código tiene que ser el que vimos en clase, pero vale
la pena mencionarlo.

### De dónde salió esta medición, para el tema de uso de IA

La expectativa con la que empecé decía que insertion sort tardaría unos 17 ms en
log607-1 y bubble unos 54 ms, o sea que insertion ganaría por mucho. Al medirlo salió
al revés: 141.740 ms contra 101.155 ms.

Resultó que esa expectativa venía de medir una versión de insertion sort que usaba
`std::move`, no la versión de clase que copia. O sea que la comparación no era entre
dos algoritmos, era entre dos formas de mover los datos.

Esto cubre dos cosas a la vez. Es un resultado que no coincidió con la predicción y
que se explica con algo que la notación O grande no ve, porque O grande supone que
todas las operaciones cuestan lo mismo. Y es un caso real de una expectativa
equivocada que solo se detectó al medir y al aislar la variable, ordenando los
mismos datos sin el string.

### Qué algoritmos cambiaron el orden de los registros con fecha repetida

Comparé la salida de cada algoritmo contra la de bubble sort en log607-1:

| Algoritmo | Líneas distintas | ¿Estable? |
|---|---|---|
| Insertion sort | 0 | Sí |
| Merge sort | 0 | Sí |
| Quick sort (mediana de tres) | 4 | No |
| Shell sort | 6 | No |
| Selection sort | 8 | No |
| Quick sort (pivote al final) | 10 | No |
| Swap sort | 11 | No |

Verifiqué que todas las líneas que cambiaron de lugar son de las 18 fechas repetidas.
Ninguna otra se movió, y las ocho salidas tienen exactamente los mismos 6,818
registros.

Que un algoritmo sea estable significa que dos registros con la misma fecha y hora
conservan el orden en que venían en el archivo. Insertion y merge lo logran porque
solo mueven cuando hay un menor estricto: al topar con una fecha igual se detienen.
Los demás mueven a saltos y pueden brincar un registro por encima de otro con su
misma fecha.

Para un log de seguridad esto importa de verdad. Si dos eventos quedaron grabados en
el mismo segundo, el archivo conserva el orden real en que llegaron. Un algoritmo
inestable puede invertirlos y hacerte creer que el ataque pasó antes que la alerta.
Cuando el orden entre eventos del mismo segundo importa, hay que usar un algoritmo
estable o desempatar con otro campo.

## Fase 6, por qué la búsqueda usa dos binarias y no una

La búsqueda binaria que vimos en clase contesta "¿está este valor y en qué posición?".
Para un rango de fechas eso no sirve por dos razones.

La primera es que las fechas del rango no tienen que existir en el archivo. Si busco
desde `Jul 11 2025 00:00:00` y ese instante no está, una binaria normal contesta "no
encontrado", cuando lo que necesito saber es en qué posición *empezaría*.

La segunda es que los archivos traen 18 pares de registros con la misma fecha y hora.
Una binaria normal se detiene en cuanto encuentra una coincidencia, y con un par puede
caer en el segundo y comerse el primero. Lo probé: si el rango va de
`Oct 02 2024 23:04:24` a esa misma fecha, el resultado correcto es 2 registros, no 1.

La solución son dos búsquedas de frontera que nunca se detienen al encontrar:

- El límite inferior busca la primera posición cuya fecha es mayor o igual al inicio.
  Cuando encuentra una igual, no se detiene: sigue acotando hacia la izquierda por si
  hay otra igual antes.
- El límite superior busca la primera posición cuya fecha es estrictamente mayor al
  fin. La única diferencia en el código es un `<=` en lugar de `<`, y ese signo de más
  es lo que hace que se brinque todos los repetidos del final.

El resultado es el bloque continuo entre las dos posiciones. Como es un pedazo seguido
del vector ordenado, es imposible que se pierda o se repita un registro, y los
duplicados de los extremos entran completos sin escribir ningún caso especial. El
costo es O(log n) para encontrar los dos límites más O(k) para copiar los k resultados.

Dos detalles chicos que importan más de lo que parece:

- `alto` arranca en `size()`, no en `size() - 1`. Así la función puede regresar
  `size()` para decir "ninguna fecha alcanza", que es lo que pasa con un rango
  posterior al último registro. Con `size() - 1` el rango que cubre todo habría dado
  6817 en vez de 6818.
- El punto medio se calcula como `bajo + (alto - bajo) / 2` y no `(bajo + alto) / 2`,
  para que la suma nunca se pase del límite del int. Con 6,818 registros da lo mismo,
  pero es la forma correcta.

Comprobé los ocho rangos de la tabla de respuestas y los ocho dieron exacto, incluidos
el de duplicados en ambos extremos (2), el día con dos pares repetidos adentro (13) y
el rango que cubre todo (6818). En los ocho, las líneas de `out/range607.txt`
coinciden con el número que anunció la pantalla.
