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

void combinar(int* v, int inicio, int medio, int fin){
    int tamIzq = medio - inicio + 1;
    int tamDer = fin - medio;
    int* izq = new int[tamIzq];
    int* der = new int[tamDer];

    // Copiar datos a arreglos temporales
    for (int i = 0; i < tamIzq; i++){
        izq[i] = v[inicio + i];
    }
    for (int j = 0; j < tamDer; j++){
        der[j] = v[medio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    // Primer elemento siempre se añade
    if (tamIzq > 0){
        v[k++] = izq[i++];
    }

    // Fusionar arreglos izq y der, eliminando duplicados
    while (i < tamIzq && j < tamDer){
        if (izq[i] < der[j]) {
            if (v[k-1] != izq[i]){ // Verificar duplicados con el último elemento añadido
                v[k++] = izq[i];
            }
            i++;
        }else{
            if (v[k-1] != der[j]){ // Verificar duplicados con el último elemento añadido
                v[k++] = der[j];
            }
            if (izq[i] == der[j]){
                i++; // Si los elementos son iguales, avanzar izq para evitar duplicado
            }
            j++;
        }
    }

    // Copiar los elementos restantes de izq[], si hay alguno, verificando duplicados
    while (i < tamIzq){
        if (v[k-1] != izq[i]){
            v[k++] = izq[i];
        }
        i++;
    }

    // Copiar los elementos restantes de der[], si hay alguno, verificando duplicados
    while (j < tamDer){
        if (v[k-1] != der[j]){
            v[k++] = der[j];
        }
        j++;
    }

    // Ajustar el tamaño final del arreglo, si es necesario
    if (fin >= k){
        for (int idx = k; idx <= fin; idx++){
            v[idx] = 0; // Puedes elegir otro valor o mecanismo para marcar el final, dependiendo de tu caso de uso
        }
    }

    delete[] izq;
    delete[] der;
}

void eliminaRepetidosDyV(int *v, int inicio, int fin){
    if (inicio >= fin)
        return;

    int medio = (inicio + fin) / 2;

    InsertionSort(v, fin+1);

    eliminaRepetidosDyV(v, inicio, medio);
    eliminaRepetidosDyV(v, medio + 1, fin);

    combinar(v, inicio, medio, fin);
}

int main(int argc, char* argv[]){
    
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
    if (!salida.is_open()){
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
    eliminaRepetidosDyV(vec, 0, n-1);
	tf = std::chrono::high_resolution_clock::now();
    
	unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    
	salida << atoi(argv[2]) << " " << tejecucion << endl; //Como n se modifica, pongo el argumento directamente pa evitar fallos
    
    salida.close();

    cout << endl;
}

