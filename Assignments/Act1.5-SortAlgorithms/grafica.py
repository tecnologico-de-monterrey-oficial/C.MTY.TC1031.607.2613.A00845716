# Diego Contreras
# A00845716

# Este script lee el archivo resultados_tiempos.csv que genera el
# programa de C++ y dibuja graficas para comparar los tiempos de los
# algoritmos de ordenamiento. Los tiempos vienen en NANOSEGUNDOS.
#
# Uso:
#   python3 grafica.py
#
# Necesita: pandas y matplotlib (ver requirements.txt)

import os
import pandas as pd
import matplotlib.pyplot as plt

ARCHIVO_CSV = "resultados_tiempos.csv"
ARCHIVO_IMAGEN = "grafica_tiempos.png"

# Los tamanos de vector que se probaron, en el mismo orden que el CSV.
TAMANOS = [1000, 10000, 100000]
COLUMNAS_TIEMPO = ["tiempo1000", "tiempo10000", "tiempo100000"]


def main():
    # 1. Revisar que exista el CSV.
    if not os.path.exists(ARCHIVO_CSV):
        print(f"No se encontro '{ARCHIVO_CSV}'.")
        print("Primero corre el programa de C++ y usa la opcion")
        print("'Analisis comparativo completo' para generarlo.")
        return

    # 2. Leer el CSV con pandas.
    datos = pd.read_csv(ARCHIVO_CSV)
    print("Datos leidos del CSV:")
    print(datos)

    # 3. Hacer una grafica por cada tipo de dato (int, double, string).
    #    Cada linea es un algoritmo; el eje X es el tamano del vector y
    #    el eje Y es el tiempo en nanosegundos (en escala logaritmica,
    #    porque las diferencias entre algoritmos son enormes).
    tipos = datos["tipo_dato"].unique()
    numTipos = len(tipos)

    fig, ejes = plt.subplots(1, numTipos, figsize=(6 * numTipos, 6))
    # Si solo hay un tipo, "ejes" no es lista; lo volvemos lista.
    if numTipos == 1:
        ejes = [ejes]

    for indice, tipo in enumerate(tipos):
        eje = ejes[indice]
        subconjunto = datos[datos["tipo_dato"] == tipo]

        for _, fila in subconjunto.iterrows():
            tiempos = [fila[col] for col in COLUMNAS_TIEMPO]
            eje.plot(TAMANOS, tiempos, marker="o", label=fila["algoritmo"])

        eje.set_title(f"Tipo de dato: {tipo}")
        eje.set_xlabel("Tamano del vector (numero de elementos)")
        eje.set_ylabel("Tiempo (nanosegundos, escala log)")
        eje.set_xscale("log")
        eje.set_yscale("log")
        eje.grid(True, which="both", linestyle="--", alpha=0.5)
        eje.legend(title="Algoritmo")

    fig.suptitle("Comparacion de tiempos de algoritmos de ordenamiento")
    fig.tight_layout()

    # 4. Guardar la imagen.
    fig.savefig(ARCHIVO_IMAGEN, dpi=120)
    print(f"\nGrafica guardada como '{ARCHIVO_IMAGEN}'.")


if __name__ == "__main__":
    main()
