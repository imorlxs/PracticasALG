#TUERCAS Y TORNILLOS 

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/tyt.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_tyt.dat' using 1:2 with points title 'Eficiencia práctica'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/tyt_dyv.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_tyt_dyv.dat' using 1:2 with linespoints title 'Eficiencia Práctica'

set terminal pngcairo enhanced font 'Verdana,10'
set output 'img/tyt_conjunto.png'
set title 'Comparación del Número de Elementos vs Tiempo'
set xlabel 'Número de Elementos'
set ylabel 'Tiempo (µs)'
set grid
plot 'dat/test_tyt_dyv.dat' using 1:2 with linespoints title 'TuercasTornillos_DyV' \
     'dat/test_tyt.dat' using 1:2 with linespoints title 'TuercasTornillos'
