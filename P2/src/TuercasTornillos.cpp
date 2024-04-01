////////////////////////////////
//Pedro Velasco Santana, 2D   //
//Tuercas y Tornillos sin DyV //
////////////////////////////////

#include<iostream>
#include<set>
#include<cstdlib>
#include<ctime>

using namespace std;

//Función que genera números aleatorios en un rango

int genera_entero_aleatorio(int menor, int mayor){

    return (rand() % (mayor - menor + 1)) + menor;   
}


int main(int argc, char* argv[]){
    
    //Control de los argumentos

    if(argc != 4 || atoi(argv[2]) < 0 || atoi(argv[1]) <= 0 || atoi(argv[3]) < 0)
        cerr << "[-] Uso: " << argv[0] << " <n de elementos> <valor min (> 0)> <valor max>" << endl;  

    int n = atoi(argv[1]);
    int menor = atoi(argv[2]);
    int mayor = atoi(argv[3]);

    if(menor > mayor){
        int a = menor;
        menor = mayor;
        mayor = a;
    }

    if((mayor - menor) < n){
        cerr << "[-] El rango de números debe ser mayor que la cantidad de elementos a almacenar";
        return -1;
    }

    //Creación de un conjunto de n elementos aleatorios en un rango menor - mayor
    //Proceso: creación set -> creación dos vectores estáticos ordenados aleatoriamente

    set<int> secuencia_base;

    srand(time(0)); 

    while(secuencia_base.size() < n){
        int elemento = genera_entero_aleatorio(menor, mayor);
        secuencia_base.insert(elemento);
    }

    int tornillos[n];
    int tuercas[n];

    for(int i = 0; i < n; i++){
        tornillos[i] = 0;
        tuercas[i] = 0;
    }

    //

    for(const int& elem : secuencia_base){
        int pos;

        do{
            pos = genera_entero_aleatorio(0, n);
        }while(tornillos[pos] != 0);
        tornillos[pos] = elem;

        do{
            pos = genera_entero_aleatorio(0, n);
        }while(tuercas[pos] != 0);
        tuercas[pos] = elem;
    }

    cout << "Tornillos" << endl;

    for(int i = 0; i < n; i++){
        cout << tornillos[i] << " ";
    }

    cout << endl << "Tuercas" << endl;

    for(int i = 0; i < n; i++){
        cout << tuercas[i] << " ";
    }

    return 0;
}