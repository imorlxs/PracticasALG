#TUERCAS Y TORNILLOS 

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/tyt.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_tyt.dat' using 1:2 with linespoints title 'TuercasTornillos'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/tyt_dyv.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_tyt_dyv.dat' using 1:2 with linespoints title 'TuercasTornillos_DyV'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/tyt_conjunto.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_tyt_dyv.dat' using 1:2 with linespoints title 'TuercasTornillos_DyV' \
     'dat/test_tyt.dat' using 1:2 with linespoints title 'TuercasTornillos'

#ELIMINA REPETIDOS

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/er.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_er.dat' using 1:2 with linespoints title 'EliminaRepetidos'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/er_dyv.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_er_dyv.dat' using 1:2 with linespoints title 'EliminaRepetidos_DyV'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/er_conjunto.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_er_dyv.dat' using 1:2 with linespoints title 'EliminaRepetidos' \
     'dat/test_er.dat' using 1:2 with linespoints title 'EliminaRepetidos_DyV'

#PRODUCTO TRES ELEMENTOS 

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/te.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_er.dat' using 1:2 with linespoints title 'ProductoTresElementos'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/te_dyv.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_te_dyv.dat' using 1:2 with linespoints title 'ProductoTresElementos_DyV'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/te_conjunto.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_te_dyv.dat' using 1:2 with linespoints title 'ProductoTresElementos_DyV' \
     'dat/test_te.dat' using 1:2 with linespoints title 'ProductoTresElementos'

#CAMPEONATO

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/cc.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_cc.dat' using 1:2 with linespoints title 'CalendarioCampeonato'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/cc_dyv.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_cc_dyv.dat' using 1:2 with linespoints title 'CalendarioCampeonato_DyV'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/cc_conjunto.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_cc_dyv.dat' using 1:2 with linespoints title 'CalendarioCampeonato_DyV' \
     'dat/test_cc.dat' using 1:2 with linespoints title 'CalendarioCampeonato'

#MAYORÍA ABSOLUTA

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/ma.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_cc.dat' using 1:2 with linespoints title 'MayoriaAbsoluta'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/ma_dyv.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_cc_dyv.dat' using 1:2 with linespoints title 'MayoriaAbsoluta_DyV'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/ma_conjunto.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_ma_dyv.dat' using 1:2 with linespoints title 'MayoriaAbsoluta_DyV' \
     'dat/test_ma.dat' using 1:2 with linespoints title 'MayoriaAbsoluta'