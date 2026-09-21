#!/bin/bash
# Diego Contreras
# A00845716
# Compila y ejecuta el analizador de logs desde la carpeta Evidence1.
cd "$(dirname "$0")/.."
g++ -std=c++20 -O2 -Wall -Wextra -Iinclude src/*.cpp -o build/app && ./build/app
