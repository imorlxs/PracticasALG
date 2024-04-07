#!/bin/bash

#MAYORIA ABSOLUTA

output_file_ma_dyv="../dat/test_ma_dyv.dat"
output_file_ma="../dat/test_ma.dat"

echo "" > $output_file_ma
echo "" > $output_file_ma_dyv

#Bucle para las pruebas
for n in {100..10000..100}; do

    echo "[+] Ejecutando prueba <MayoriaAbsoluta> con ..."
    bin/MayoriaAbsoluta $output_file_ma $n

    echo "[+] Ejecutando prueba <MayoriaAbsolutaDyV> ..."
    bin/MayoriaAbsolutaDyV $output_file_ma_dyv $n
done

echo "[+] PRUEBA MAYORIA ABSOLUTA FINALIZADA"

#TUERCAS Y TORNILLOS

output_file_tyt_dyv="dat/test_tyt_dyv.dat"
output_file_tyt="dat/test_tyt.dat"

echo "" > $output_file_tyt
echo "" > $output_file_tyt_dyv

#Bucle para las pruebas
for n in {10..100..10}; do

    valor_min=1
    valor_max=$(($n + 50))

    echo "[+] Ejecutando prueba <TuercasTornillos> con n = $n, min = $valor_min, max = $valor_max"
    bin/TuercasTornillos $output_file_tyt $n $valor_min $valor_max

    echo "[+] Ejecutando prueba <TuercasTornillosDyV> con n = $n, min = $valor_min, max = $valor_max"
    bin/TuercasTornillosDyV $output_file_tyt_dyv $n $valor_min $valor_max
done

echo "[+] PRUEBA TUERCAS Y TORNILLOS FINALIZADA"

#Producto de tres elementos

output_file_te_dyv="dat/test_te_dyv.dat"
output_file_te="dat/test_te.dat"

# Asegurándose de que los archivos de salida están vacíos al principio
echo "" > $output_file_te
echo "" > $output_file_te_dyv

# Bucle para las pruebas, redirigiendo la salida estándar a los archivos de salida
for n in {10..100..10}; do
    echo " [+] Ejecutando prueba <ProductoTresElementosBasico+Complejo> con n = $n"
    bin/ProductoTresElementosBasico+Complejo $n $output_file_te >> $output_file_te

    echo " [+] Ejecutando prueba <ProductoTresElementosDivyVenc> con n = $n"
    bin/ProductoTresElementosDivyVenc $n $output_file_te_dyv >> $output_file_te_dyv
done

echo "[+] PRUEBA TRES ELEMENTOS FINALIZADA"

#Eliminar elementos repetidos

output_file_er_dyv="dat/test_er_dyv.dat"
output_file_er="dat/test_er.dat"

echo "" > $output_file_er
echo "" > $output_file_er_dyv

#Bucle para las pruebas
for n in {10..100..10}; do

    valor_min=0
    valor_max=$((n / 2))
    echo "[+] Ejecutando prueba <EliminarRepetidos> con n = $n, min = $valor_min, max = $valor_max"
    bin/EliminarRepetidos $output_file_er $n $valor_min $valor_max

    echo "[+] Ejecutando prueba <EliminarRepetidosDyV> con n = $n, min = $valor_min, max = $valor_max"
    bin/EliminarRepetidosDyV $output_file_er_dyv $n $valor_min $valor_max
done

echo "[+] PRUEBA ELEMENTOS REPETIDOS FINALIZADA"

#Organización del calendario de un campeonato

output_file_cc_dyv="dat/test_cc_dyv.dat"
output_file_cc="dat/test_cc.dat"

echo "" > $output_file_cc
echo "" > $output_file_cc_dyv

#Bucle para las pruebas

for ((n = 2; n <= 32768; n *= 2)); do

    echo " [+] Ejecutando prueba <OrganizarCalendarioCampeonato> con n = $n"
    bin/OrganizarCalendarioCampeonato $output_file_cc $n

    echo "[+] Ejecutando prueba <OrganizarCalendarioCampeonatoDyV> con n = $n"
    bin/OrganizarCalendarioCampeonatoDyV $output_file_cc_dyv $n
done

echo "[+] PRUEBA CALENDARIO CAMPEONATO FINALIZADA"
