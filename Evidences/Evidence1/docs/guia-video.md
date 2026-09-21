# Guía de orientación del código

Para preparar el video y la revisión. Por cada archivo: qué hace, qué tienes que
poder explicar sin verlo, y las preguntas probables con su respuesta corta.

El proyecto son 1,233 líneas repartidas en 5 módulos. El más importante para el
video es `busqueda.cpp`, que son solo 63 líneas.

---

## 1. registro.h y registro.cpp — los datos

**Qué hace.** Define qué es un registro del log y se encarga de leer y escribir
los archivos. Cada registro guarda dos cosas: la línea original completa tal como
venía, y una clave numérica con la fecha para poder comparar rápido.

**Lo que tienes que poder explicar sin ver.**

La clave es un `long long` con el formato `AAAAMMDDhhmmss`. Por ejemplo
`Oct 02 2024 23:04:24` se guarda como `20241002230424`. El año va primero porque
así pesa más que el mes, el mes más que el día, y así sucesivamente. Comparar dos
fechas se vuelve comparar dos números.

Se guarda la línea original completa porque los archivos de salida tienen que
tener exactamente el mismo formato que la entrada. Si reconstruyera la línea
campo por campo, sería fácil perder un cero de `Oct 02` o un espacio del mensaje.

`fechaAClave` valida todo: que el texto mida 20 caracteres, que los separadores
estén en su lugar, que donde van números no haya letras, que el mes exista, y que
el día caiga dentro de los días reales de ese mes, contando años bisiestos. Esa
misma función se usa dos veces: al leer el archivo y al validar lo que teclea el
usuario en la búsqueda.

**Preguntas probables**

| Pregunta | Respuesta corta |
|---|---|
| ¿Por qué la clave es un número y no comparas los textos? | Comparar textos compararía "Dec" contra "Jan" alfabéticamente y daría mal. El número respeta el orden real del tiempo. |
| ¿Por qué el año va primero? | Para que pese más. Si comparara solo mes y día, `Sep 08 2024` y `Sep 08 2025` quedarían juntos. |
| ¿Por qué guardas la línea original si ya tienes la clave? | Para que la salida salga idéntica a la entrada, sin reconstruirla. |
| ¿Cómo validas los años bisiestos? | `diasDelMes` regresa 29 para febrero si el año es divisible entre 4, excepto los divisibles entre 100 que no lo sean entre 400. Por eso 2024 sí y 1900 no. |
| ¿Qué pasa si una línea viene rota? | Se avisa con su número de línea y se salta. La lectura no se detiene. Se prueba con `data/prueba-malformada.txt`. |

---

## 2. ordenamientos.h — los algoritmos

**Qué hace.** Contiene los ocho algoritmos, todos como plantillas que ordenan de
menor a mayor comparando únicamente con `<`. Va todo en el `.h` porque las
plantillas necesitan estar completas donde se usan.

**Lo que tienes que poder explicar sin ver.**

Los siete primeros son los de la Act 1.5. El octavo es una variante de quick sort
que agregaste tú para comparar, no es de clase.

Bubble sort tiene una bandera: si una pasada completa termina sin intercambios,
ya está ordenado y se sale. Por eso tarda 0.29 ms en el archivo casi ordenado
contra 105 ms en el desordenado.

Merge sort crea el vector auxiliar **una sola vez** y lo pasa por referencia a
toda la recursión. Si lo creara en cada llamada, estaría reservando memoria miles
de veces.

Insertion y merge son estables, los demás no. Estable significa que dos registros
con la misma fecha y hora conservan el orden en que venían. Insertion lo logra
porque su `while` usa menor estricto, así que se detiene al topar con una fecha
igual en vez de pasarle por encima. Merge lo logra porque al empatar toma primero
el de la mitad izquierda.

**Preguntas probables**

| Pregunta | Respuesta corta |
|---|---|
| ¿Por qué son plantillas? | Para que el mismo código sirva con cualquier tipo que sepa compararse con `<`, igual que en la Act 1.5. |
| ¿Qué hace que un algoritmo sea estable? | Que solo mueva cuando hay un menor estricto. Al empatar no mueve, así conserva el orden original. |
| ¿Por qué importa la estabilidad aquí? | Los archivos traen 18 pares de registros con la misma fecha y hora. Un algoritmo inestable los puede invertir y hacer creer que un evento ocurrió antes que otro. |
| ¿Por qué quick sort se hace lento con datos casi ordenados? | Con pivote al final, el pivote es casi siempre el mayor del pedazo, así que la partición deja todo de un lado y nada del otro. En vez de partir a la mitad, reduce de uno en uno. Es su peor caso O(n²). |
| ¿Y por qué tu quick sort de clase no sufre eso? | Porque usa mediana de tres: escoge el valor de en medio entre el primero, el de en medio y el último. Así el pivote nunca es sistemáticamente un extremo. |
| ¿Por qué insertion salió más lento que bubble? | Porque cada registro trae un texto. Bubble mueve con `std::swap`, que solo intercambia apuntadores. Insertion mueve con asignación, que copia el texto completo. Con 11.6 millones de movimientos, ese costo se come su ventaja. |

---

## 3. busqueda.h y busqueda.cpp — la parte de 20 puntos

**Qué hace.** Encuentra todos los registros cuya fecha cae dentro de un rango,
usando dos búsquedas binarias de frontera en vez de una búsqueda binaria normal.

**Lo que tienes que poder explicar sin ver. Esta es la parte que el video califica.**

Una búsqueda binaria normal contesta "¿está este valor y dónde?". Aquí hacen falta
otras dos cosas que no contesta: qué pasa si la fecha no existe en el archivo, y
qué pasa si hay varios registros con esa misma fecha.

Por eso son dos búsquedas y ninguna se detiene al encontrar:

- **Límite inferior**: la primera posición cuya fecha es mayor o igual al inicio.
- **Límite superior**: la primera posición cuya fecha es estrictamente mayor al fin.

El resultado son las posiciones desde el límite inferior hasta una antes del
superior. Como es un pedazo continuo del vector ordenado, es imposible perder o
repetir un registro, y los duplicados de los extremos entran completos solos.

Los tres detalles que tienes que señalar en el código:

1. `alto` arranca en `size()`, no en `size() - 1`. Así puede regresar `size()`
   para decir "ninguna fecha alcanza". Con `size() - 1` el rango que cubre todo
   habría dado 6817 en vez de 6818.
2. **No hay `return` dentro del ciclo.** Aunque encuentre una fecha igual, sigue
   acotando hacia la izquierda por si hay otra igual antes. Esto es lo que evita
   perder duplicados.
3. Las dos funciones son idénticas salvo un signo: el límite inferior usa
   `<` y el superior usa `<=`. Ese igual de más es lo que hace que el superior se
   brinque todos los repetidos del final.

El costo es O(log n) para encontrar los dos límites, más O(k) para copiar los k
resultados.

**Preguntas probables**

| Pregunta | Respuesta corta |
|---|---|
| ¿Por qué dos binarias y no una? | Porque necesito las fronteras del rango, no una posición cualquiera. Y porque las fechas que teclea el usuario no tienen que existir en el archivo. |
| ¿Qué pasa si la fecha de inicio no existe? | El límite inferior regresa la posición donde *empezaría*, que es justo donde arranca el rango. |
| ¿Cómo garantizas que no se pierde ningún duplicado? | Ninguna de las dos se detiene al encontrar. El inferior sigue a la izquierda y el superior sigue a la derecha hasta la frontera. |
| ¿Qué complejidad tiene? | O(log n) para los límites más O(k) para copiar. |
| ¿Por qué `medio = bajo + (alto - bajo) / 2` y no `(bajo + alto) / 2`? | Para que la suma nunca se pase del límite del int. Con 6,818 da igual, pero es la forma correcta. |
| ¿Qué pasa si buscas sin haber ordenado? | El programa lo bloquea. La binaria sobre datos desordenados daría resultados falsos sin avisar. |
| ¿El rango incluye los extremos? | Sí, es inclusivo en los dos. Si el inicio o el fin cae en una fecha repetida, entran todos los registros de esa fecha. |

---

## 4. entrada.h y entrada.cpp — leer al usuario

**Qué hace.** Dos funciones que piden datos y no avanzan hasta que sean válidos:
una pide un número dentro de un rango, la otra pide un texto que no esté vacío.

**Lo que tienes que poder explicar sin ver.**

Todo se lee con `getline`, nunca con `cin >>`. Si mezclaras los dos, el `cin >>`
deja un salto de línea colgado y el siguiente `getline` lee vacío, o sea que el
programa se brinca la pregunta de la razón de la predicción.

Hay tres candados. Si `getline` falla es que se cerró la entrada con Ctrl + D, y
ahí el programa avisa y termina, porque si no se quedaría pidiendo el dato para
siempre. Se revisa que todos los caracteres sean dígitos, así se rechazan `abc`,
`2abc`, `1.5` y `-3`. Y se revisa que no haya más de 9 dígitos **antes** de
convertir, porque `stoi` lanza una excepción con un número que no cabe en un int
y eso cerraría el programa.

**Preguntas probables**

| Pregunta | Respuesta corta |
|---|---|
| ¿Por qué getline y no `cin >>`? | Para no mezclar formas de leer. `cin >>` deja el salto de línea pendiente y rompe el siguiente getline. |
| ¿Qué pasa si escriben un número gigante? | Se rechaza antes de convertirlo, por la revisión de 9 dígitos. Si no, `stoi` lanzaría una excepción y el programa se cerraría. |
| ¿Y si presionan Ctrl + D? | Sale con un mensaje. Sin esa revisión quedaría en un ciclo infinito imprimiendo el error. |

---

## 5. corridas.h y corridas.cpp — complejidades, predicción e historial

**Qué hace.** Guarda la tabla con la complejidad de cada algoritmo, pide la
predicción antes de ordenar, clasifica el tiempo medido y guarda cada corrida en
`out/corridas.csv`. También muestra el historial.

**Lo que tienes que poder explicar sin ver.**

Los umbrales son: rápido menos de 10 ms, medio entre 10 y 60, lento más de 60.
Se escogieron viendo los tiempos reales para que ninguno quedara pegado a un
límite y cambiara de categoría por pura variación.

El CSV se abre con `std::ios::app`, que agrega al final. Sin eso, cada corrida
borraría el historial.

Los campos de texto van entre comillas y las comillas internas se escriben dobles.
Eso es la regla del formato CSV y hace falta porque tanto la razón como el nombre
`Quick sort (pivote al final, variante)` traen comas.

**Preguntas probables**

| Pregunta | Respuesta corta |
|---|---|
| ¿De dónde salieron los umbrales? | De los tiempos observados, para que ningún resultado quedara justo en la frontera entre dos categorías. |
| ¿Cómo evitas que una coma en la razón rompa el CSV? | El campo va entre comillas dobles y las comillas internas se duplican. Es la regla estándar del formato. |
| ¿Por qué el historial sobrevive al cerrar el programa? | Porque vive en el archivo CSV, no en memoria, y se abre en modo agregar. |

---

## 6. main.cpp — el flujo

**Qué hace.** El menú y el orden de las cosas: cargar archivo, elegir algoritmo,
pedir la predicción, medir, verificar, escribir la salida y registrar la corrida.

**Lo que tienes que poder explicar sin ver. Esto es lo más fácil de que te pregunten.**

**Cada corrida ordena una copia fresca de los datos originales.** La copia se hace
antes de arrancar el cronómetro, porque copiar no es parte del algoritmo. Si
ordenara el vector original, la segunda corrida recibiría datos ya ordenados y los
tiempos no servirían para nada.

El cronómetro rodea únicamente la llamada al algoritmo. No incluye leer el
archivo, ni copiar, ni escribir la salida.

La predicción se pide **antes** de empezar a medir. Si se pidiera en medio, el
tiempo que tarda el usuario en escribir contaría como tiempo del algoritmo.

Después de ordenar se verifica que el vector quedó de menor a mayor. Si falla, no
se marcan los datos como ordenados y la búsqueda sigue bloqueada.

Al cargar un archivo nuevo se pone `hayOrdenado = false`. Sin eso podrías ordenar
un archivo, cargar el otro, y buscar sobre datos que ya no están ordenados.

**Preguntas probables**

| Pregunta | Respuesta corta |
|---|---|
| ¿Por qué copias el vector antes de cada corrida? | Para que cada algoritmo reciba los datos en el orden del archivo. Si no, el segundo recibiría datos ya ordenados. |
| ¿Por qué la copia se hace fuera de la medición? | Porque copiar 6,818 registros no es trabajo del algoritmo. |
| ¿Cómo sabes que el algoritmo ordenó bien? | `estaOrdenado` recorre el vector y confirma que no haya ningún elemento menor que el anterior. |
| ¿Por qué guardas copias con nombre por archivo? | Porque `output607.txt` se sobrescribe en cada corrida, y la entrega pide los resultados de los dos archivos. |

---

## Lo mínimo que no puedes fallar en el video

1. Por qué son **dos** búsquedas binarias y no una.
2. Que ninguna se detiene al encontrar, y que eso es lo que salva los duplicados.
3. La diferencia de `<` contra `<=` entre las dos funciones.
4. Que cada corrida ordena una copia fresca.
5. Por qué elegiste insertion sort: porque su trabajo depende de qué tan
   desordenados vienen los datos, y querías ver qué tanto se nota entre los dos
   archivos.

## Números que te conviene traer en la cabeza

| Dato | Valor |
|---|---|
| Registros por archivo | 6,818 |
| Pares de fechas repetidas | 18 |
| Periodo que cubren | Sep 08 2024 00:22:43 a Sep 07 2026 23:50:40 |
| Insertion en log607-1 | 126.185 ms |
| Insertion en log607-2 | 0.962 ms, unas 131 veces más rápido |
| Quick con pivote al final en log607-2 | 37.974 ms contra 0.966 ms en el desordenado |
| Búsqueda de `Oct 02 2024 23:04:24` a la misma fecha | 2 registros |
| Búsqueda de `Feb 14 2026 14:43:30` a `22:00:18` | 5 registros |
