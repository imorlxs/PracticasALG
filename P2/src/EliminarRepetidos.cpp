#include<iostream>
#include<set>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<fstream> 
using namespace std;

int genera_entero_aleatorio(int menor, int mayor){

    return (rand() % (mayor - menor + 1)) + menor;   
}

void InsertionSort(int *v, int n){
    for (int i = 1; i < n; ++i){ 
        int value = *(v + i); //Selección del valor actual
        int j = i - 1; //Selección de la posición de comparación

        //Bucle de comparaciones y desplazamientos

        while (j >= 0 && *(v + j) > value){ 
            *(v + (j + 1)) = *(v + j);
            j = j - 1;
        }
       *(v + (j + 1)) = value;
    }
}

void eliminaRepetidos(int* v, int &n){

    // Paso 1: Ordenar el arreglo
    InsertionSort(v, n);
    
    // Paso 2: Crear un arreglo temporal para almacenar los elementos únicos
    int* temp = new int[n];
    
    // Paso 3: Copiar los elementos únicos al arreglo temporal
    int j = 0; // Índice para el arreglo temporal
    for (int i = 0; i < n - 1; i++) {
        // Si el elemento actual es diferente del siguiente, lo copiamos a temp
        if (v[i] != v[i + 1]) {
            temp[j++] = v[i];
        }
    }
    // Asegurar de copiar el último elemento
    temp[j++] = v[n-1];
    
    // Paso 4: Copiar de vuelta al arreglo original los elementos de temp
    for (int i = 0; i < j; i++) {
        v[i] = temp[i];
    }
    
    // Actualizar n al nuevo tamaño
    n = j;
    
    // Liberar el arreglo temporal
    delete[] temp;
}

int main(int argc, char* argv[]) {

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    ofstream salida;

    if(argc != 3){
        cerr << "[-] Uso: " << argv[0] << " <fichero salida> <n de elementos>" << endl;  
        return -1;
    }

    salida.open(argv[1], std::ios::out | std::ios::app);
    if (!salida.is_open()) {
        cerr << "Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
        return 0;
    }

    // Crear un vector con elementos repetidos
    int arr[] = {3, 1, 2, 3, 2, 4, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Arreglo original: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Llamar a la función para eliminar elementos repetidos
    eliminaRepetidos(arr, n);

    cout << "Arreglo sin elementos repetidos: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}