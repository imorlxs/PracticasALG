////////////////////////////////
//Pedro Velasco Santana, 2D   //
//Tuercas y Tornillos sin DyV //
////////////////////////////////

#include<iostream>
#include<set>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(int argc, char* argv[]){
    
    //Control de los argumentos

    if(argc != 4 || atoi(argv[2]) < 0 || atoi(argv[1]) <= 0 || atoi(argv[3]) <= 0)
        cerr << "[-] Uso: " << argv[0] << " <n de elementos> <valor min (> 0)> <valor max>" << endl;  

    int n = atoi(argv[1]);
    int menor = atoi(argv[2]);
    int mayor = atoi(argv[3]);

    if((mayor - menor) < n){
        cerr << "[-] El rango de números debe ser mayor que la cantidad de elementos a almacenar";
        return -1;
    }

    if(menor > mayor){
        int a = menor;
        menor = mayor;
        mayor = a;
    }

    //Creación de un conjunto de n elementos aleatorios en un rango menor - mayor
    //Proceso: creación set -> creación dos vectores estáticos ordenados aleatoriamente

    set<int> secuencia_base;

    srand(time(0)); 

    while(secuencia_base.size() < n){
        int elemento = (rand() % (mayor - menor + 1)) + menor;
        secuencia_base.insert(elemento);
    }

    /*cout << "Conjunto base" << endl;

    for (int elem : secuencia_base) {
        cout << elem << " ";
    }*/

    return 0;
}