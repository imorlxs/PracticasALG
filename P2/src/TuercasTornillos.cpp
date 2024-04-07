////////////////////////////////
//Pedro Velasco Santana, 2D   //
//Tuercas y Tornillos sin DyV //
////////////////////////////////

#include<iostream>
#include<set>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<fstream> 

using namespace std;

//Función que genera números aleatorios en un rango

int genera_entero_aleatorio(int menor, int mayor){

    return (rand() % (mayor - menor + 1)) + menor;   
}

void ordena_tuercas_tornillos(int *tuercas, int *tornillos, int n){

    int aux[n];	

    for(int i = 0; i < n; i++){ //Se recorren los tornillos
        for(int j = 0; j < n; j++){
            if(tornillos[i] == tuercas[j]){ //Cuando se encuentra una coincidencia
                aux[i] = tuercas[j]; //Se copia al vector auxiliar y se sale del bucle
                break;
            }
        }
    }

    for(int i = 0; i < n; i++) { //Se copia el resultado en el vector de tuercas
        tuercas[i] = aux[i];
    }
}

int main(int argc, char* argv[]){
    
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    ofstream salida;

    //Control de los argumentos

    if(argc != 5 || atoi(argv[3]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[4]) <= 0){
        cerr << "[-] Uso: " << argv[0] << " <fichero salida> <n de elementos> <valor min (> 0)> <valor max>" << endl;  
        return -1;
    }

    int n = atoi(argv[2]);
    int menor = atoi(argv[3]);
    int mayor = atoi(argv[4]);

    //Cambiar el rango en caso de error

    if(menor > mayor){
        int a = menor;
        menor = mayor;
        mayor = a;
    }

    if((mayor - menor) < n){ //Esto debido a que deben ser claves únicas    
        cerr << "[-] El rango de números debe ser mayor que la cantidad de elementos a almacenar";
        return -1;
    }

    salida.open(argv[1], std::ios::out | std::ios::app);
        if (!salida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }

    //PRIMERA PARTE: GENERACIÓN DE VECTORES

    //Creación de un conjunto de n elementos aleatorios en un rango menor - mayor

    set<int> secuencia_base;

    srand(time(0)); //Semilla para los números aleatorios

    while(secuencia_base.size() < n){
        int elemento = genera_entero_aleatorio(menor, mayor);
        secuencia_base.insert(elemento);
    }

    //Creación dos vectores estáticos ordenados aleatoriamente

    int tornillos[n];
    int tuercas[n];

    for(int i = 0; i < n; i++){ //Relleno de 0s los vectores para tener forma de comparación
        tornillos[i] = 0;
        tuercas[i] = 0;
    }

    //Relleno los dos vectores de forma aleatoria 

    for(const int& elem : secuencia_base){
        int pos;

        do{
            pos = genera_entero_aleatorio(0, n-1);
        }while(tornillos[pos] != 0);
        tornillos[pos] = elem;

        do{
            pos = genera_entero_aleatorio(0, n-1);
        }while(tuercas[pos] != 0);
        tuercas[pos] = elem;
    }

    secuencia_base.clear(); //Este conjunto ya no es necesario

    //SEGUNDA PARTE: ORDENACIÓN DE VECTORES Y TOMA DE PRUEBAS

    cout << "Vector de tuercas y tornillos sin ordenar (respectivamente): " << endl;

    for(int i = 0; i < n; ++i)
        cout << " " << tuercas[i];

    cout << endl;

    for(int i = 0; i < n; ++i)
        cout << " " << tornillos[i];
    
    t0 = std::chrono::high_resolution_clock::now();
    ordena_tuercas_tornillos(tuercas, tornillos, n);
    tf = std::chrono::high_resolution_clock::now();

    unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    salida << n << " " << tejecucion << endl;

    salida.close();

    cout << endl << "Vector de tuercas y tornillos ordenados (respectivamente): " << endl;

    for(int i = 0; i < n; ++i)
        cout << " " << tuercas[i];

    cout << endl;

    for(int i = 0; i < n; ++i)
        cout << " " << tornillos[i];

}