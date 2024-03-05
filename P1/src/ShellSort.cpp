/*
 * @file ShellSort.cpp
 * @author Álvaro Maldonado Medina <mmalvaro04@correo.ugr.es>
 */

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void ShellSort(int *v, int tamanio);

int main(int argc, char **argv){

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

        cerr << "Ejecutando ShellSort para tam. caso: " << n << endl;

        t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
        ShellSort(v, n); // Ejecutamos el algoritmo para tamaÒo de caso tam
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

void ShellSort(int *v, int tam){

    //Bucle que crea un "hueco", o "paso" y divide la lista en varias sublistas
    for (int paso = tam/2; paso > 0; paso/=2){
        for (int i = paso; i < tam; i++){   // Bucle que va recorriendo el vector hacia delante desde el v[paso]
           int temp = v[i];
           int j;

           //bucle que compara el valor de "temp" con valores "n" pasos a la izquierda de la posición dada
           for (j = i; j >= paso && v[j-paso] > temp; j -= paso)
                v[j] = v[j-paso];

           //guardar el valor temporal en la misma o nueva posición de v
           v[j] = temp;
        }
    }
}
