#!/bin/bash

#Eliminar elementos repetidos

output_file_er_dyv="dat/test_er_dyv.dat"
output_file_er="dat/test_er.dat"

echo "" > $output_file_er
echo "" > $output_file_er_dyv


#Bucle para las pruebas
for n in {1..1000000..5000}; do

    valor_min=1
    valor_max=$((n / 2))

    echo "[+] Ejecutando prueba <EliminarRepetidos> con n = $n, min = $valor_min, max = $valor_max"
    bin/EliminarRepetidos $output_file_er $n $valor_min $valor_max

    echo "[+] Ejecutando prueba <EliminarRepetidosDyV> con n = $n, min = $valor_min, max = $valor_max"
    bin/EliminarRepetidosDyV $output_file_er_dyv $n $valor_min $valor_max
done

echo "[+] PRUEBA ELEMENTOS REPETIDOS FINALIZADA"