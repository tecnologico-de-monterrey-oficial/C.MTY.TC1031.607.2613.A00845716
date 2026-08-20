# Reflexión - Actividad 1.2 Recursión

**¿En qué casos la versión recursiva fue más lenta o usó más memoria que la iterativa? ¿A qué se debió?**

La recursión de las bacterias fue la más lenta, porque cada llamada genera otras
llamadas y además usa la pila para guardar cada una. La iterativa solo usa un ciclo
y una variable, por eso gasta menos memoria y es más rápida.

**Para la suma 1..n, sumFormula resuelve en un solo paso lo que a sumIterative y sumRecursive les toma n pasos. ¿Qué te dice esto sobre buscar una fórmula antes de escribir código?**

Que si existe una fórmula, conviene usarla, porque resuelve el problema de una vez sin
importar qué tan grande sea n. Pensar un poco antes de programar puede ahorrar muchos pasos.

**Si bacteriasRecursive tuviera que calcular n = 100,000 días, ¿qué problema esperarías encontrar y cómo lo resolverías?**

Esperaría un desbordamiento de pila (stack overflow) por tantas llamadas, y que tardara
demasiado. Lo resolvería usando la versión iterativa, que hace lo mismo con un solo ciclo.
