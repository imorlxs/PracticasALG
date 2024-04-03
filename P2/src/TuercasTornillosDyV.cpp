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

int particionar(int *v, int pivote, int inicio, int fin){
    int i = inicio;
    int temp;

    // Primero, encuentra el pivote en arr[] y lo intercambia con el elemento en fin.
    for (int j = inicio; j < fin; j++) {
        if (v[j] == pivote) {
            temp = v[j];
            v[j] = v[fin];
            v[fin] = temp;
            break; // Salir del bucle una vez que el pivote está al final.
        }
    }

    // Ahora, procede con el particionado usual.
    pivote = v[fin]; // El pivote ahora está en la posición fin.
    int pIndex = inicio; // Posición del primer elemento mayor encontrado.

    for (int j = inicio; j < fin; j++) {
        if (v[j] < pivote) {
            // Intercambia si el elemento es menor que el pivote.
            temp = v[j];
            v[j] = v[pIndex];
            v[pIndex] = temp;
            pIndex++;
        }
    }

    // Coloca el pivote después del último elemento menor.
    temp = v[pIndex];
    v[pIndex] = v[fin];
    v[fin] = temp;

    return pIndex; // Retorna la posición del pivote.
}

int encuentraPivote(int* arr, int elemento, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == elemento) {
            return i; // Retorna el índice del elemento coincidente.
        }
    }
    return -1; // En caso de que no se encuentre, lo cual no debería ocurrir en este contexto.
}

void ordena_tuercas_tornillos_dyv(int *tuercas, int *tornillos, int inicio, int fin){

    if (inicio < fin) {
        // Usa el primer elemento de tuercas como pivote para particionar tornillos.
        int pivote = encuentraPivote(tornillos, tuercas[inicio], fin + 1); // Asegúrate de que el rango es correcto.
        int pIndex = particionar(tornillos, tuercas[inicio], inicio, fin);

        // Ahora usa el tornillo que coincide con el pivote original para particionar tuercas.
        particionar(tuercas, tornillos[pIndex], inicio, fin); // Aquí, tornillos[pIndex] es el valor correcto.

        // Recursivamente ordena las mitades izquierda y derecha.
        ordena_tuercas_tornillos_dyv(tuercas, tornillos, inicio, pIndex - 1);
        ordena_tuercas_tornillos_dyv(tuercas, tornillos, pIndex + 1, fin);
    }
}


int main(int argc, char* argv[]){
    
    //Control de los argumentos

    if(argc != 4 || atoi(argv[2]) <= 0 || atoi(argv[1]) <= 0 || atoi(argv[3]) <= 0){
        cerr << "[-] Uso: " << argv[0] << " <n de elementos> <valor min (> 0)> <valor max>" << endl;  
        return -1;
    }

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

    ordena_tuercas_tornillos_dyv(tuercas, tornillos, 0, n-1);

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

}


/*
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

    //Eficiencia teórica: O(n²) (bucle interior hace n iteraciones por cada una de bucle exterior, nxn)

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(tornillos[i] == tuercas[j]){
                aux[i] = tuercas[j];
                break;
            }
        }
    }

    for(int i = 0; i < n; i++) {
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


void sort(int *tuercas, int *tornillos, int inicio, int fin){
    //particionamos los tornillos usando de pivote la primera tuerca
    int pivote = particionar(tuercas[pivote], tornillos, inicio, fin);

    //devuelve el índice del tornillo que es igual a la tuerca
    //y lo usamos de pivote en las tuercas
    particionar(tornillos[pivote], tuercas, inicio, fin);

    //ahora los 2 arrays están divididos en 3 partes 
    //con los pivotes al medio en el mismo índice, se sigue recursivamente 
    sort(tuercas, tornillos, inicio, pivote);
    sort(tuercas, pernos, pivote, fin);
}

*/