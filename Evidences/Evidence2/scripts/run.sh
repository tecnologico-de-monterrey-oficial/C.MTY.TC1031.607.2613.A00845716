#!/bin/bash
# Diego Contreras
# A00845716
# Compila y ejecuta el analizador de logs desde la carpeta Evidence2.
# Deja fuera src/pruebas.cpp porque tiene su propio main y se compila aparte.
cd "$(dirname "$0")/.."
g++ -std=c++20 -O2 -Wall -Wextra -Iinclude $(ls src/*.cpp | grep -v pruebas.cpp) -o build/app && ./build/app
