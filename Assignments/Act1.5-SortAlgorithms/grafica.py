# Diego Contreras
# A00845716

# Lee resultados_tiempos.csv y grafica los tiempos de los algoritmos.
# Uso: python3 grafica.py

import os
import pandas as pd
import matplotlib.pyplot as plt

ARCHIVO_CSV = "resultados_tiempos.csv"
ARCHIVO_IMAGEN = "grafica_tiempos.png"

TAMANOS = [1000, 10000, 100000]
COLUMNAS_TIEMPO = ["tiempo1000", "tiempo10000", "tiempo100000"]


def main():
    if not os.path.exists(ARCHIVO_CSV):
        print(f"No se encontro '{ARCHIVO_CSV}'. Corre primero el programa de C++.")
        return

    datos = pd.read_csv(ARCHIVO_CSV)
    print(datos)

    # Una grafica por tipo de dato. Escala log porque las diferencias son enormes.
    tipos = datos["tipo_dato"].unique()
    numTipos = len(tipos)

    fig, ejes = plt.subplots(1, numTipos, figsize=(6 * numTipos, 6))
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
    fig.savefig(ARCHIVO_IMAGEN, dpi=120)
    print(f"\nGrafica guardada como '{ARCHIVO_IMAGEN}'.")


if __name__ == "__main__":
    main()
