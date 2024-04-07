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

bool MayoriaAbsoluta(int *v, int inicio, int ultimo);
bool BuscaCandidato(int *v, int inicio, int ultimo, int &candidato);

int main(int argc, char *argv[]) {
	
	if (argc <= 2) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	int *v;
	int n, i, argumento;
	bool candidato_mayoria;
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
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n/10 - 1
		for (i= 0; i<n; i++)
			v[i]= rand()%(n/10);
		
		cerr << "Ejecutando MayoriaAbsoluta para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		candidato_mayoria = MayoriaAbsoluta(v, 0, n-1); // Ejecutamos el algoritmo para tamaÒo de caso tam
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



bool MayoriaAbsoluta(int *v, int inicio, int ultimo) {
  // Comprueba si v[inicio..ultimo] contiene un elemento mayoritario
  int suma, i, candidato;
  suma = 0;
  if (BuscaCandidato(v,inicio,ultimo,candidato)){
    // Comprobar si el candidato es o no mayoritario
    for (int i = inicio; i <= ultimo; i++){
      if (v[i] == candidato)
        suma++;
    }
  }
  return (suma > ((ultimo-inicio+1)/2));

}

bool BuscaCandidato(int *v, int inicio, int ultimo, int &candidato){
  int i, j;
  candidato = v[inicio];
  // Casos base
  if (ultimo < inicio)
    return false;

  if (ultimo == inicio)
    return true;

  if (inicio+1 == ultimo){
    candidato = v[ultimo];
    return (v[inicio] == v[ultimo]);
  }

  // Caso general
  j = inicio;
  if ((ultimo-inicio+1)%2 == 0){
    for (int i = inicio+1; i <= ultimo; i+=2){
      if (v[i-1] == v[i]){
        v[j] = v[i]; j++; 
      }
    }
    return BuscaCandidato(v, inicio, j-1, candidato);
  }
  else{
    for (int i = inicio; i < ultimo; i+=2){
      if (v[i] == v[i+1]){
        v[j] = v[i]; j++;
      }
    }

    if (!BuscaCandidato(v, inicio, j-1, candidato))
      candidato=v[ultimo];

    return true;
  }
}
