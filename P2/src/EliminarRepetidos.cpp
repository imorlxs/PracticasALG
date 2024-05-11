#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<fstream> 

using namespace std;

// Función que genera un número aleatorio entre dos números

int genera_entero_aleatorio(int menor, int mayor){

    return (rand() % (mayor - menor + 1)) + menor;   
}

// Función de ordenamiento (copiada de la P1)

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

// Función para eliminar los elementos repetidos de un vector

void eliminaRepetidos(int* v, int* n){

    // Paso 1: Ordenar el vector
    InsertionSort(v, *n);
    
    // Paso 2: Crear un vector temporal para almacenar los elementos que no estén repetidos
    int* tmp = new int[*n];

    // Bucle que mete en el vector temporal los valores que no están repetidos en el vector v
    int j = 0;      // Índice del vector temporal
    for (int i = 0; i < *n - 1; i++) {
        if (v[i] != v[i + 1]) {
            tmp[j++] = v[i];
        }
    }

    // Nos aseguramos de meter el último elemento
    tmp[j++] = v[*n-1];
    
    // Pasamos los valores del vector temporal al vector original
    for (int i = 0; i < j; i++) {
        v[i] = tmp[i];
    }
    
    *n = j; // Actualizar el tamaño del vector original
    
    delete[] tmp;   // Borramos la memoria del vector temporal que ya no utilizamos
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
    
    srand(time(0)); //Semilla para los números aleatorios
    
    int vec[n];
    
    //Rellena el vector de números aleatorios

    for (int i = 0; i < n; i++){
        vec[i] = genera_entero_aleatorio(menor, mayor-1); 
    }

    cout << "Vector original sin eliminar los repetidos" << endl;

    for (int i = 0; i < n; i++){
        cout << " " << vec[i];
    }

    t0 = std::chrono::high_resolution_clock::now();
    eliminaRepetidos(vec, &n);
	tf = std::chrono::high_resolution_clock::now();
    
	unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    
	salida << atoi(argv[2]) << " " << tejecucion << endl; //Como n se modifica, pongo el argumento directamente pa evitar fallos
    
    salida.close();

    cout << "Vector original con los elementos eliminados y ordenados" << endl;

    for (int i = 0; i < n; i++){
        cout << " " << vec[i];
    }
}
