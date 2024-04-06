#!/bin/bash

#MAYORIA ABSOLUTA

#output_file_ma_dyv="../dat/test_ma_dyv.dat"
#output_file_ma="../dat/test_ma.dat"

#echo "" > $output_file_ma
#echo "" > $output_file_ma_dyv

#g++ -o ../bin/ma ../src/MayoriaAbsoluta.cpp
#g++ -o ../bin/ma_dyv ../src/MayoriaAbsolutaDyV.cpp

#Bucle para las pruebas
#for n in { }; do

#    echo "[+] Ejecutando prueba <ma> con ...
#    ../bin/ma

#    echo "[+] Ejecutando prueba <ma_dyv> ...
#    ../bin/ma_dyv
#done

#echo "[+] PRUEBA MAYORIA ABSOLUTA FINALIZADA"

#TUERCAS Y TORNILLOS

output_file_tyt_dyv="../dat/test_tyt_dyv.dat"
output_file_tyt="../dat/test_tyt.dat"

echo "" > $output_file_tyt
echo "" > $output_file_tyt_dyv

g++ -o ../bin/tyt ../src/TuercasTornillos.cpp
g++ -o ../bin/tyt_dyv ../src/TuercasTornillosDyV.cpp

#Bucle para las pruebas
for n in {10..100000..100}; do

    valor_min=1
    valor_max=$(($n + 50))

    echo "[+] Ejecutando prueba <tyt> con n = $n, min = $valor_min, max = $valor_max"
    ../bin/tyt $output_file_tyt $n $valor_min $valor_max

    echo "[+] Ejecutando prueba <tyt_dyv> con n = $n, min = $valor_min, max = $valor_max"
    ../bin/tyt_dyv $output_file_tyt_dyv $n $valor_min $valor_max
done

echo "[+] PRUEBA TUERCAS Y TORNILLOS FINALIZADA"

#Producto de tres elementos

output_file_te_dyv="../dat/test_te_dyv.dat"
output_file_te="../dat/test_te.dat"

echo "" > $output_file_te
echo "" > $output_file_te_dyv

g++ -o ../bin/te ../src/ProductoTresElementosBasico+Complejo.cpp
g++ -o ../bin/te_dyv ../src/ProductoTresElementosDivyVenc.cpp

#Bucle para las pruebas
for n in { }; do

    echo " [+] Ejecutando prueba <te> con n = $n, valor = $valor_unico"
    ../bin/te $output_file_te $n $valor_unico

    echo "[+] Ejecutando prueba <te_dyv> con n = $n, valor = $valor_unico"
    ../bin/te_dyv $output_file_te_dyv
done

echo "[+] PRUEBA TRES ELEMENTOS FINALIZADA"

#Eliminar elementos repetidos

output_file_er_dyv="../dat/test_er_dyv.dat"
output_file_er="../dat/test_er.dat"

echo "" > $output_file_er
echo "" > $output_file_er_dyv

g++ -o ../bin/er ../src/EliminarRepetidos.cpp
g++ -o ../bin/er_dyv ../src/EliminarRepetidosDyV.cpp

#Bucle para las pruebas
for n in {10..100..10}; do

    valor_min=0
    valor_max=$((n / 2))
    echo "[+] Ejecutando prueba <er> con n = $n, min = $valor_min, max = $valor_max"
    ../bin/er $output_file_er $n $valor_min $valor_max

#    echo "[+] Ejecutando prueba <er_dyv> ...
#    ../bin/er_dyv
done

echo "[+] PRUEBA ELEMENTOS REPETIDOS FINALIZADA"

#Organización del calendario de un campeonato

#output_file_cc_dyv="../dat/test_cc_dyv.dat"
#output_file_cc="../dat/test_cc.dat"

#echo "" > $output_file_cc
#echo "" > $output_file_cc_dyv

#g++ -o ../bin/cc ../src/OrganizarCalendarioCampeonato.cpp
#g++ -o ../bin/cc_dyv ../src/OrganizarCalendarioCampeonatoDyV.cpp

#Bucle para las pruebas
#for n in { }; do

#    echo " [+] Ejecutando prueba <cc> con ...
#    ../bin/cc

#    echo "[+] Ejecutando prueba <cc_dyv> ...
#    ../bin/cc_dyv
#done

#echo "[+] PRUEBA CALENDARIO CAMPEONATO FINALIZADA"
