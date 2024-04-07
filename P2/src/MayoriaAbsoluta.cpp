/**
 * @brief Ejercicio de la mayoría absoluta. Práctica 2 Algorítmica. Curso 23/24
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 */

#include <climits> // Para usar INT_MIN
#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <unordered_map>
using namespace std;

int MayoriaAbsoluta(int *v, int n);


int main(int argc, char *argv[]) {
	
	if (argc <= 2) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	int *v;
	int n, i, argumento, candidato_mayoria;
    	chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
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
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		cerr << "Ejecutando MayoriaAbsoluta para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		candidato_mayoria = MayoriaAbsoluta(v, n); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		if (candidato_mayoria == INT_MIN) {
    cout << "No hay candidato con mayoría absoluta." << endl;
  } else {
    cout << "El candidato " << candidato_mayoria << " tiene mayoría absoluta." << endl;
  }
		// Liberamos memoria del vector
		delete [] v;
	}

	// Cerramos fichero de salida
	fsalida.close();
  	
  
	
  return 0;
}

int MayoriaAbsoluta(int *v, int n) {
  unordered_map<int, int> frecuencia;

  for (int i = 0; i < n; i++) {
    frecuencia[v[i]]++;

    if (frecuencia[v[i]] > (n/2)){
      return v[i];
    }
  }


  return INT_MIN;
}


