#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

void CountingSort(int *v, int tam){

    int max = v[0];
    for (int i = 0; i < tam; i++){
        if (v[i] > max)
            max = v[i];
    }

    int *count = new int[max+1];
    int *out = new int[tam];

    for (int i = 0; i < max; i++){
        count[i] = 0;
    }

    for (int i = 0; i < tam; i++){
        count[v[i]]++;
    }

    for (int i = 1; i < max; i++){
        count[i] = count[i] + count[i-1];
    }

    for (int i = tam-1; i >= 0; i--){
        out[--count[v[i]]] = v[i];
    }

    for (int i = 0; i < tam; i++){
        v[i] = out[i];
    }
}

int main(int argc, char *argv[]) {
	
	int *v;
    int *vaux;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
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
	srand(semilla);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		v= new int[n];
        vaux= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		cerr << "Ejecutando CountingSort para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		CountingSort(v, n); // Ejecutamos el algoritmo para tamaÒo de caso n
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
        delete [] vaux;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}