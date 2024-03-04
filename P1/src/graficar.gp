# Establecer el estilo de la gráfica
set style data lines
set xlabel "Número de elementos"
set ylabel "Tiempo (µs)"
set grid

# Definir las funciones f(x) para cada tipo de algoritmo de ordenamiento
f_BubbleSort(x) = a*x**2
f_MergeSort(x) = a*x*log10(x)
f_CountingSort(x) = a*x
f_InsertionSort(x) = a*x**2
f_QuickSort(x) = a*x*log10(x)
f_SelectionSort(x) = a*x**2
f_ShellSort(x) = a*x*log10(x)*log10(x)

# Obtener la lista de archivos .dat en la carpeta dat/
file_list = system("ls dat/*.dat 2>/dev/null")

# Iterar sobre cada archivo .dat en la carpeta dat/
do for [file in file_list] {
    # Obtener el nombre del archivo sin la extensión
    filename_no_extension = system("basename -s .dat ".file)

    # Configurar el título con el nombre del archivo sin la extensión
    set title filename_no_extension

    # Ajustar la función correspondiente a los datos del archivo
    if (filename_no_extension eq "BubbleSort") {
        fit f_BubbleSort(x) file via a
    } 
    if (filename_no_extension eq "MergeSort") {
        fit f_MergeSort(x) file via a
    } 
    if (filename_no_extension eq "CountingSort") {
        fit f_CountingSort(x) file via a
    }
    if (filename_no_extension eq "InsertionSort") {
        fit f_InsertionSort(x) file via a
    } 
    if (filename_no_extension eq "QuickSort") {
        fit f_QuickSort(x) file via a
    }
    if (filename_no_extension eq "SelectionSort") {
        fit f_SelectionSort(x) file via a
    }
    if (filename_no_extension eq "ShellSort") {
        fit f_ShellSort(x) file via a
    }

    # Nombre del archivo PNG de salida en la carpeta img/
    output_file = "img/grafica_" . filename_no_extension . ".png"

    # Configurar la salida a un archivo PNG
    set terminal pngcairo
    set output output_file

    # Plotear el archivo actual y la función ajustada
    if (filename_no_extension eq "BubbleSort") {
         plot file using 1:2 with points lw 2 title "Eficiencia práctica", f_BubbleSort(x) with lines lw 2 title " Tiempo teórico estimado"
    }
    if (filename_no_extension eq "MergeSort") {
        plot file using 1:2 with points lw 2 title "Eficiencia práctica", f_MergeSort(x) with lines lw 2 title "Tiempo teórico estimado"
    }
    if (filename_no_extension eq "CountingSort") {
        plot file using 1:2 with points lw 2 title "Eficiencia práctica", f_CountingSort(x) with lines lw 2 title "Tiempo teórico estimado"
    }
    if (filename_no_extension eq "InsertionSort") {
        plot file using 1:2 with points lw 2 title "Eficiencia práctica", f_InsertionSort(x) with lines lw 2 title "Tiempo teórico estimado"
    }
    if (filename_no_extension eq "QuickSort") {
        plot file using 1:2 with points lw 2 title "Eficiencia práctica", f_QuickSort(x) with lines lw 2 title "Tiempo teórico estimado"
    }
    if (filename_no_extension eq "SelectionSort") {
        plot file using 1:2 with points lw 2 title "Eficiencia práctica", f_SelectionSort(x) with lines lw 2 title "Tiempo teórico estimado"
    }
    if (filename_no_extension eq "ShellSort") {
        plot file using 1:2 with points lw 2 title "Eficiencia práctica", f_ShellSort(x) with lines lw 2 title "Tiempo teórico estimado"
    }

    # Restaurar la salida a la pantalla
    set output
}
