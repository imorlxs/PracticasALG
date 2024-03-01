# Establecer el estilo de la gráfica
set style data lines
set xlabel "Número de elementos"
set ylabel "Tiempo (µs)"
set grid

# Obtener la lista de archivos .dat en la carpeta dat/
file_list = system("ls dat/*.dat")

# Función para obtener el nombre del archivo sin la extensión
get_filename_without_extension(filename) = system("basename -s .dat ".filename)

# Iterar sobre cada archivo .dat en la carpeta dat/
do for [file in file_list] {
    # Obtener el nombre del archivo sin la extensión
    filename_no_extension = get_filename_without_extension(file)

    # Configurar el título con el nombre del archivo sin la extensión
    set title filename_no_extension

    # Nombre del archivo PNG de salida en la carpeta img/
    output_file = "img/grafica_" . filename_no_extension . ".png"

    # Configurar la salida a un archivo PNG
    set terminal pngcairo
    set output output_file

    # Plotear el archivo actual
    plot with lines lw 2

    # Restaurar la salida a la pantalla
    set output
}

