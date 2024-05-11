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

// Función para eliminar los elementos repetidos de un vector

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

// Función que combina los vectores en los que se divide el original

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

    // Caso base en el que si la posición de inicio es mayor que la posición del final
    if (inicio >= fin) return;

    // Calcula el punto en el cual se divide el vector en 2 mitades
    int medio = inicio + (fin - inicio) / 2;

    // Se llama a la función recursivamente para que elimine los repetidos en ambas mitades
    eliminaRepetidosDyV(v, inicio, medio, n);
    eliminaRepetidosDyV(v, medio+1, fin, n);

    // Combina las dos mitades
    combinar(v, inicio, medio, fin);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Aquí se contempla el caso en el que a la hora de juntar ambos vectores, pueda darse el caso
    // de que justo donde se divide sea un elemento que se repite en ambas mitades, por tanto 
    // eliminamos los elementos repetidos del vector combinados tal como se hizo en el método sin
    // usar divide y vencerás
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    
    int* temp = new int[n];
    
    int j = 0; 
    
    for (int i = 0; i < n-1; i++) {
        if (v[i] != v[i + 1]) {
            temp[j++] = v[i];
        }
    }
    
    temp[j++] = v[n-1];
    
    for (int i = 0; i < j; i++) {
        v[i] = temp[i];
    }
    
    n = j;
    
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
    
    srand(time(0)); //Semilla para los números aleatorios
    
    int vec[n];
    
    //De esta forma generamos el vector más fácilmente
    for (int i = 0; i < n; i++){
        vec[i] = genera_entero_aleatorio(menor, mayor-1);   //Pasamos a la función el rango del argumento
    }

    cout << "Vector original sin eliminar los repetidos" << endl;

    for (int i = 0; i < n; i++){
        cout << " " << vec[i];
    }
    
    t0 = std::chrono::high_resolution_clock::now();
    eliminaRepetidosDyV(vec, 0, n-1, n);
	tf = std::chrono::high_resolution_clock::now();
    
	unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    
	salida << atoi(argv[2]) << " " << tejecucion << endl; //Como n se modifica, pongo el argumento directamente pa evitar fallos
    
    salida.close();

    cout << "Vector original con los elementos eliminados y ordenados" << endl;

    for (int i = 0; i < n; i++){
        cout << " " << vec[i];
    }

    cout << endl;

}

