# Act 2.1 LinkedList

Diego Contreras Alvarez, A00845716


## Archivos

- `Node.h` tiene la estructura del nodo con su dato y el apuntador al siguiente.
- `LinkedList.h` tiene la clase con addFirst, addLast, insert, deleteData, deleteAt, getData, updateData, updateAt, findData, la sobrecarga del operador `[]` y la del operador `=`, además del destructor y el constructor de copia.
- `main.cpp` tiene la creación de la lista y el menú.
- `tests.pdf` tiene las evidencias de las pruebas de cada opción del menú.

## Cómo compilar y correr

```
g++ -std=c++17 main.cpp -o main
./main
```

## Uso de IA

Usé Claude (en el chat y en Claude Code) para tres cosas. La primera fue armar el main con el menú, porque es código largo y repetitivo y preferí dedicarle el tiempo a las funciones de la lista. La segunda fue corregir algunas de las funciones que ya habíamos hecho en clase para que coincidieran con la interfaz que pide la actividad. La tercera fue resolver errores generales al compilar. Las funciones de la lista las fui escribiendo y revisando una por una, pidiendo que me explicaran qué tenia que hacer cada bloque

### Prompts

Para que me explicara el código mientras avanzaba:

```
mira me vas a ir diciendo que es lo que tiene que hacer cada una, osea me vas a ir explicando que se espera de los bloques de codigo. Primero te enseñare lo que llevo
```

Para corregir lo que ya teníamos de clase:

```
En LinkedList.h haz solo estos cambios, nada más:

1. Debajo de #include "Node.h" agrega:
   #include <iostream>
   #include <stdexcept>
   using namespace std;

2. En la declaración de la clase renombra push_front a addFirst y push_back a addLast.

3. En la implementación renombra LinkedList<T>::push_front a LinkedList<T>::addFirst.

4. Dentro de insert cambia la llamada push_front(data) por addFirst(data).

No implementes addLast, no toques Node.h, no crees archivos nuevos, no reformatees ni cambies comentarios, y no hagas commit ni push. Cuando termines enséñame el diff.
```

Para armar el main (en Claude Code):

```
Crea main.cpp para la actividad de LinkedList. No modifiques Node.h. En LinkedList.h solo puedes hacer dos cosas: agregar las declaraciones que falten dentro de la clase y agregar un getter inline int getSize() { return size; }. No implementes ninguna otra función de la lista, eso lo voy a hacer yo.

```

Para ajustar el main cuando ya estaban todas las funciones (en Claude Code):

```

Para errores al compilar:

```
mira me sale este error, puedes checarlo y decirme que esta mal?
./LinkedList.h:182:21: error: redefinition of 'deleteAt'
./LinkedList.h:155:21: note: previous definition is here
```

## Reflexión

**¿Qué parte del código te propuso la IA que aceptaste tal cual y por qué era correcta?**

Acepté tal cual la forma de borrar en deleteData y deleteAt, que consiste en caminar hasta el nodo anterior al que se quiere borrar, hacer que ese nodo se salte al que sigue y luego liberar la memoria del borrado. Era correcta porque en una lista ligada solo puedes reconectar desde el nodo de atrás, y además la condición del `while` revisa primero que exista un siguiente antes de leer su dato, así que nunca lee un `nullptr` cuando el elemento no está. 

**¿Qué parte modificaste y cómo verificaste que tu cambio era mejor?**

Las funciones que hicimos en clase se llamaban `push_front` y `push_back`, y las cambié a `addFirst` y `addLast` para que coincidieran con la interfaz de la actividad, junto con los includes que le faltaban al header y que solo compilaba de suerte porque el main los incluía antes. También agregué un constructor de copia que no venía en la interfaz. Sin él, una línea como `LinkedList<int> copia = lista;` usa el constructor que pone C++ por defecto, que copia el apuntador `head` y deja las dos listas compartiendo los mismos nodos, y al destruirse las dos se borra el mismo nodo dos veces.

**¿Dónde se equivocó la IA (si ocurrió) y cómo lo detectaste?**

Hubo dos errores. Al pedirle a Claude Code que armara el main también le pedí agregar todas las declaraciones a la clase, y solo agregó algunas. Lo noté al revisar la clase antes de compilar, porque faltaban casi todas las funciones de la interfaz y el `getSize` que usaba el main, y las agregué a mano. 

**¿Qué harías diferente si no tuvieras Copilot/ChatGPT?**

Me habría tardado bastante más en el main, porque escribir el menú, el llenado aleatorio para los dos tipos y todos los try/catch a mano es mucho código repetido. Para las funciones de la lista me habría apoyado en lo que vimos en clase y en dibujar los nodos en papel para ver cómo se reconectan los apuntadores en cada caso, sobre todo en los borrados y en insert. 