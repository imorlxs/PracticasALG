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
		cerr<<argv[0]<<" NombreFicheroSalida elemento1 elemento2 ... elementoN\n\n";
		return 0;
	}

	int *v;
  int elementos = argc - 2;
  v = new int[elementos];
	
  int n, i, argumento, candidato_mayoria;
    chrono::time_point<chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	ofstream fsalida;
	
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Pasamos por cada elemento de la entrada
	i = 0;
  for (argumento= 2; argumento<argc; argumento++) {
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
	  // Introducimos el elemento en el vector
    v[i] = n;
    i++;
  }	
  cerr << "Ejecutando Mayoría Absoluta" << endl;
  
  t0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
  candidato_mayoria = MayoriaAbsoluta(v, elementos); // Ejecutamos el algoritmo
  tf= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
  
  unsigned long tejecucion= chrono::duration_cast<chrono::microseconds>(tf - t0).count();
  
  cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< elementos <<endl;
  
  // Guardamos tam. de caso y t_ejecucion a fichero de salida
  fsalida<<n<<" "<<tejecucion<<"\n";
	
	// Cerramos fichero de salida
	fsalida.close();
  	
	delete [] v;
  if (candidato_mayoria == INT_MIN) {
    cout << "No hay candidato con mayoría absoluta." << endl;
  } else {
    cout << "El candidato " << candidato_mayoria << " tiene mayoría absoluta." << endl;
  }
	
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

  int candidato_mayoria = INT_MIN;

  for (auto it : frecuencia) {
    if (it.second > n / 2) {
      candidato_mayoria = it.first;
      break;
    }
  }
  return candidato_mayoria;
}


