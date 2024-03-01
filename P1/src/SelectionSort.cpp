#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void SelectionSort(int *v, int tam); //SELECTION SORT SUPREMACY!!!! WTF IS A RECURSIVE ALGORITHM RAHHHHHHH!!!!!

int main(int argc, char *argv[]) {
	
	int *v;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	//cout<<"semilla: "<<semilla<<endl;
	srand(semilla);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		//cout << "argumento: " << argumento << endl; 
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		v= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		cerr << "Ejecutando Selection Sort para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		SelectionSort(v, n); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}


void SelectionSort(int *v, int tam){
	
	for(int i=0; i < tam-1; i++){  //Este primer bucle es el que va a ir haciendo el vector a ordenar cada vez mas pequenio.
		int posicionMinima = i;
		for (int j = i+1; j < tam ; j++){
			
			if(v[j] < v[posicionMinima])
			{
				posicionMinima = j;
			}
		}
		
		if(posicionMinima != i){ //Nos aseguramos de que haya un cambio que hacer
			int aux = v[i];
			v[i] = v[posicionMinima];
			v[posicionMinima] = aux;
		}
	}
	//Esto es para que comprobeis que funciona, despues lo quitais, q imprime el vector por pantalla y nada que ver con el fokin algoritmo.
	/*cout << "{";
	for(int i=0; i<tam; i++){
		cout << v[i] << " ";
	}
	cout << "}" << endl;
	*/
}
