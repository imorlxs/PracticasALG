#include<iostream>
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

void eliminaRepetidos(int* v, int n){

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
    
    // Liberar el arreglo temporal
    delete[] temp;
}


int main(int argc, char* argv[]) {
    
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    ofstream salida;

    
    if(argc != 5 || atoi(argv[2]) <= 0 || atoi(argv[3]) < 0){
        cerr << "[-] Uso: " << argv[0] << " <fichero salida> <n de elementos> <valor mínimo(>= 0)> <valor máximo>" << endl;  
        return -1;
    }
    
    int n = atoi(argv[2]); 
    int menor = atoi(argv[3]);
    int mayor = atoi(argv[4]);
    
    
    salida.open(argv[1], std::ios::out | std::ios::app);
    if (!salida.is_open()) {
        cerr << "[-] Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
        return 0;
    }
    
    // Crear un vector con elementos repetidos
    
    srand(time(0)); //Semilla para los números aleatorios
    
    int vec[n];
    
    //De esta forma generamos el vector más fácilmente
    for (int i = 0; i < n; i++){
        vec[i] = genera_entero_aleatorio(menor, mayor-1);   //Pasamos a la función el rango del argumento
    }
    
    t0 = std::chrono::high_resolution_clock::now();
    eliminaRepetidos(vec, n);
	tf = std::chrono::high_resolution_clock::now();
    
	unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    
	salida << atoi(argv[2]) << " " << tejecucion << endl; //Como n se modifica, pongo el argumento directamente pa evitar fallos
    
    salida.close();

    cout << endl;
}

