# Diego Contreras
# A00845716

# Lee out/corridas.csv y dibuja la comparacion de tiempos de los 8 algoritmos
# en los dos archivos. El eje vertical va en escala logaritmica porque los
# tiempos van de 0.28 ms a 139 ms y en escala normal las barras chicas no se verian.

import csv
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.ticker import FixedLocator, FixedFormatter

SURFACE = "#fcfcfb"
TINTA   = "#0b0b0b"
TINTA2  = "#52514e"
REJILLA = "#dedcd6"
SERIE1  = "#2a78d6"   # log607-1, desordenado
SERIE2  = "#eb6834"   # log607-2, casi ordenado

ORDEN = ["Bubble sort", "Selection sort", "Insertion sort", "Merge sort",
         "Quick sort (mediana de tres)", "Swap sort", "Shell sort",
         "Quick sort (pivote al final, variante)"]

CORTOS = {"Bubble sort": "Bubble", "Selection sort": "Selection",
          "Insertion sort": "Insertion", "Merge sort": "Merge",
          "Quick sort (mediana de tres)": "Quick\n(mediana 3)",
          "Swap sort": "Swap", "Shell sort": "Shell",
          "Quick sort (pivote al final, variante)": "Quick\n(pivote final)"}

# Solo las 16 primeras corridas: una por algoritmo y archivo.
tiempos = {}
with open("out/corridas.csv", newline="", encoding="utf-8") as f:
    for fila in list(csv.DictReader(f))[:16]:
        tiempos[(fila["algoritmo"], fila["archivo"])] = float(fila["tiempo_ms"])

t1 = [tiempos[(a, "log607-1.txt")] for a in ORDEN]
t2 = [tiempos[(a, "log607-2.txt")] for a in ORDEN]

fig, ax = plt.subplots(figsize=(10, 5.4))
fig.patch.set_facecolor(SURFACE)
ax.set_facecolor(SURFACE)

x = range(len(ORDEN))
ancho = 0.38
hueco = 0.012   # separacion entre las dos barras del par
b1 = ax.bar([i - ancho/2 - hueco for i in x], t1, ancho,
            label="log607-1.txt (desordenado)", color=SERIE1, zorder=3)
b2 = ax.bar([i + ancho/2 + hueco for i in x], t2, ancho,
            label="log607-2.txt (casi ordenado)", color=SERIE2, zorder=3)

ax.set_yscale("log")
ax.set_ylim(0.15, 400)
ax.yaxis.set_major_locator(FixedLocator([0.3, 1, 3, 10, 30, 100, 300]))
ax.yaxis.set_major_formatter(FixedFormatter(["0.3", "1", "3", "10", "30", "100", "300"]))
ax.set_ylabel("Tiempo en milisegundos (escala logaritmica)", color=TINTA2, fontsize=10)

ax.set_xticks(list(x))
ax.set_xticklabels([CORTOS[a] for a in ORDEN], fontsize=9, color=TINTA)
ax.tick_params(axis="y", colors=TINTA2, labelsize=9, length=0)
ax.tick_params(axis="y", which="minor", length=0)   # sin marcas menores del log
ax.yaxis.set_minor_formatter(plt.NullFormatter())
ax.tick_params(axis="x", colors=TINTA, length=0)

# Rejilla discreta, solo horizontal, detras de las barras.
ax.grid(axis="y", color=REJILLA, linewidth=0.8, zorder=0)
ax.set_axisbelow(True)
for lado in ("top", "right", "left"):
    ax.spines[lado].set_visible(False)
ax.spines["bottom"].set_color(REJILLA)

# El valor va encima de cada barra: son 16 numeros y son el dato del reporte.
for barras in (b1, b2):
    for b in barras:
        ax.annotate(f"{b.get_height():.1f}" if b.get_height() >= 1 else f"{b.get_height():.2f}",
                    (b.get_x() + b.get_width()/2, b.get_height()),
                    textcoords="offset points", xytext=(0, 3),
                    ha="center", fontsize=7.5, color=TINTA2)

ax.set_title("Tiempo de ordenamiento de 6,818 registros por algoritmo y archivo",
             fontsize=13, color=TINTA, pad=14, loc="left")
ax.legend(frameon=False, fontsize=9, labelcolor=TINTA2, loc="upper right", ncols=2)

fig.tight_layout()
fig.savefig("docs/grafica-tiempos.png", dpi=200, facecolor=SURFACE)
print("guardada en docs/grafica-tiempos.png")
