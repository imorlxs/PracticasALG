#Organización del calendario de un campeonato

output_file_cc_dyv="../dat/test_cc_dyv.dat"
output_file_cc="../dat/test_cc.dat"

echo "" > $output_file_cc
echo "" > $output_file_cc_dyv

g++ -o ../bin/cc ../src/OrganizarCalendarioCampeonato.cpp
g++ -o ../bin/cc_dyv ../src/OrganizarCalendarioCampeonatoDyV.cpp

Bucle para las pruebas
for ((n = 2; n <= 1048576; n *= 2)); do

    echo " [+] Ejecutando prueba <cc> con n = $n"
    ../bin/cc $output_file_cc $n

    echo "[+] Ejecutando prueba <cc_dyv> con n = $n"
    ../bin/cc_dyv $output_file_cc_dyv $n
done

echo "[+] PRUEBA CALENDARIO CAMPEONATO FINALIZADA"
