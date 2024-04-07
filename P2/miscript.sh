#!/bin/bash

#TUERCAS Y TORNILLOS

output_file_tyt_dyv="dat/test_tyt_dyv.dat"
output_file_tyt="dat/test_tyt.dat"

echo "" > $output_file_tyt
echo "" > $output_file_tyt_dyv

#Bucle para las pruebas
for n in {1..1000000..5000}; do

    valor_min=1
    valor_max=$(($n + 50))

    echo "[+] Ejecutando prueba <TuercasTornillos> con n = $n, min = $valor_min, max = $valor_max"
    bin/TuercasTornillos $output_file_tyt $n $valor_min $valor_max

    echo "[+] Ejecutando prueba <TuercasTornillosDyV> con n = $n, min = $valor_min, max = $valor_max"
    bin/TuercasTornillosDyV $output_file_tyt_dyv $n $valor_min $valor_max
done

echo "[+] PRUEBA TUERCAS Y TORNILLOS FINALIZADA"
