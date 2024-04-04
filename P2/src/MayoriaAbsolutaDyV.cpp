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
		cerr<<argv[0]<<" NombreFicheroSalida elemento1 elemento2 ... elementoN\n\n";
		return 0;
	}

	int *v;
  int elementos = argc - 2;
  v = new int[elementos];
	
  int n, elementosi, argumento;
  bool candidato_mayoria;
    chrono::time_point<chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	ofstream fsalida;
	
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Pasamos por cada elemento de la entrada
	elementosi = 0;
  for (argumento= 2; argumento<argc; argumento++) {
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
	  // Introducimos el elemento en el vector
    v[elementosi] = n;
    elementosi++;
  }	
  cerr << "Ejecutando Mayoría Absoluta" << endl;
  
  for(int j = 0; j < elementosi; j++)
    cout << v[j] << " ";
  cout << endl;
  t0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
  candidato_mayoria = MayoriaAbsoluta(v, 0, elementosi-1); // Ejecutamos el algoritmo
  tf= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que ultimoiza la ejecuciÛn del algoritmo
  
  unsigned long tejecucion= chrono::duration_cast<chrono::microseconds>(tf - t0).count();
  
  cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< elementos <<endl;
  
  // Guardamos tam. de caso y t_ejecucion a fichero de salida
  fsalida<<n<<" "<<tejecucion<<"\n";
	
	// Cerramos fichero de salida
	fsalida.close();
  
  for(int j = 0; j < elementos; j++)
    cout << v[j] << " ";
  cout << endl;
	delete [] v;
  if (!candidato_mayoria) {
    cout << "No hay candidato con mayoría absoluta." << endl;
  } else {
    cout << "Hay candidato con mayoría absoluta." << endl;
  }
	
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
