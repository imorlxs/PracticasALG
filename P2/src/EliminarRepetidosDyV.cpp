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

void combinar(int *v, int inicio, int medio, int fin){

    int n1 = medio - inicio + 1; // Tamaño del primer subvector
    int n2 = fin - medio; // Tamaño del segundo subvector

    // Crear subvectores temporales
    int* left = new int[n1];
    int* right = new int[n2];

    // Copiar datos a los subvectores temporales
    for (int i = 0; i < n1; ++i) {
        left[i] = v[inicio + i];
    }
    for (int j = 0; j < n2; ++j) {
        right[j] = v[medio + 1 + j];
    }

    // Índices iniciales para los subvectores temporales
    int i = 0; // Para el subvector izquierdo
    int j = 0; // Para el subvector derecho
    int k = inicio; // Índice para el subvector combinado

    // Mezclar los subvectores temporales en el subvector original
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            v[k++] = left[i++];
        } else {
            v[k++] = right[j++];
        }
    }

    // Copiar los elementos restantes del subvector izquierdo (si los hay)
    while (i < n1) {
        v[k++] = left[i++];
    }

    // Copiar los elementos restantes del subvector derecho (si los hay)
    while (j < n2) {
        v[k++] = right[j++];
    }

    // Liberar la memoria de los subvectores temporales
    delete[] left;
    delete[] right;
}

void eliminaRepetidosDyV(int *v, int inicio, int fin, int &n){

    if (inicio >= fin) return;

    int medio = inicio + (fin - inicio) / 2;

    eliminaRepetidosDyV(v, inicio, medio, n);
    eliminaRepetidosDyV(v, medio+1, fin, n);

    combinar(v, inicio, medio, fin);

    
    // Paso 2: Crear un arreglo temporal para almacenar los elementos únicos
    int* temp = new int[n];
    
    // Paso 3: Copiar los elementos únicos al arreglo temporal
    int j = 0; // Índice para el arreglo temporal
    //temp[j++] = v[0];
    for (int i = 0; i < n-1; i++) {
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
    
    n = j;
    // Liberar el arreglo temporal
    delete[] temp;
    
}   
/*
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
    eliminaRepetidosDyV(vec, 0, n-1, n);
	tf = std::chrono::high_resolution_clock::now();
    
	unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    
	salida << atoi(argv[2]) << " " << tejecucion << endl; //Como n se modifica, pongo el argumento directamente pa evitar fallos
    
    salida.close();

    cout << endl;
}*/


int main() {

    int v[] = {3, 6, 5, 5, 3, 8, 9, 8, 3, 0, 1, 0, 2, 5, 6, 7};

    int n = sizeof(v) / sizeof(v[0]);

    cout << "Vector original: ";
    for (int i = 0; i < n; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;

    InsertionSort(v,n);

    eliminaRepetidosDyV(v, 0,n-1, n);

    cout << "Vector sin elementos repetidos: ";
    for (int i = 0; i < n; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    return 0;
}
