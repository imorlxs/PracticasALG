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

void ordena_tuercas_tornillos(int *tuercas, int *tornillos, int *aux, int n){
    
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
    
    //Control de los argumentos

    if(argc != 4 || atoi(argv[2]) < 0 || atoi(argv[1]) <= 0 || atoi(argv[3]) < 0)
        cerr << "[-] Uso: " << argv[0] << " <n de elementos> <valor min (> 0)> <valor max>" << endl;  

    int n = atoi(argv[1]);
    int menor = atoi(argv[2]);
    int mayor = atoi(argv[3]);

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
    int tuercas_ordenadas[n]; //Vector auxiliar que usaremos luego

    for(int i = 0; i < n; i++){ //Relleno de 0s los vectores para tener forma de comparación
        tornillos[i] = 0;
        tuercas[i] = 0;
    }

    //Relleno los dos vectores de forma aleatoria 

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

    secuencia_base.clear(); //Este conjunto ya no es

//---------------------------------------------------------------------------
    //Si tenemos que hacer 800 pruebas esto será despreciable   
    
    cout << "Tornillos" << endl;

    for(int i = 0; i < n; i++){
        cout << tornillos[i] << " ";
    }

    cout << endl << "Tuercas" << endl;

    for(int i = 0; i < n; i++){
        cout << tuercas[i] << " ";
    }
//---------------------------------------------------------------------------

    //SEGUNDA PARTE: ORDENACIÓN DE VECTORES

    ordena_tuercas_tornillos(tuercas, tornillos, tuercas_ordenadas, n);

//---------------------------------------------------------------------------
    //Si tenemos que hacer 800 pruebas esto será despreciable   

    cout << endl << "Tornillos" << endl;

    for(int i = 0; i < n; i++){
        cout << tornillos[i] << " ";
    }

    cout << endl << "Tuercas" << endl;

    for(int i = 0; i < n; i++){
        cout << tuercas[i] << " ";
    }
//---------------------------------------------------------------------------
}
