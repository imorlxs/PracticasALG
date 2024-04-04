#!/bin/bash

#TUERCAS Y TORNILLOS

output_file_tyt_dyv="../dat/test_tyt_dyv.dat"
output_file_tyt="../dat/test_tyt.dat"

echo "" > $output_file_tyt
echo "" > $output_file_tyt_dyv

g++ -o ../bin/tyt ../src/TuercasTornillos.cpp
g++ -o ../bin/tyt_dyv ../src/TuercasTornillosDyV.cpp

# Bucle para las pruebas
for n in {10..100..10}; do

    valor_min=1
    valor_max=$(($n + 50)) # Asegurarse de que la diferencia sea mayor que n

    echo "Ejecutando prueba <tyt> con n = $n, min = $valor_min, max = $valor_max"
    ../bin/tyt $output_file_tyt $n $valor_min $valor_max

    echo "Ejecutando prueba <tyt_dyv> con n = $n, min = $valor_min, max = $valor_max"
    ../bin/tyt_dyv $output_file_tyt_dyv $n $valor_min $valor_max
done

echo "Pruebas finalizadas."
