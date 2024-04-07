#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono> // Para medir el tiempo de ejecución
#include <fstream> // Para escribir en un archivo
using namespace std;

vector<int> encontrarTresConsecutivos(int N){
    int low = 1;
    int high = cbrt(N) + 1;

    while(low <= high){
        int mid = low + (high - low) / 2;
    
        int producto = mid * (mid+1) * (mid+2);

        if (producto == N) {
            return {
                mid, mid+1, mid + 2
            };
        }else if (producto < N){
            low = mid + 1;
        }else {
            high = mid - 1;
        }
    }
    
    return{};
}

int main(int argc, char** argv){
    if(argc < 3){
        cerr << "Error, introduzca un numero y el nombre del archivo de salida" << endl;
        return -1;
    }
    
    int N;
    vector<int> vec(3,0);
    
    N = stoi(argv[1]);

    // Inicia el cronómetro
    auto start = chrono::high_resolution_clock::now();
    vec = encontrarTresConsecutivos(N);
    auto stop = chrono::high_resolution_clock::now();

    unsigned long duracion = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    // Abre el archivo en modo append para agregar los resultados sin borrar los anteriores
    ofstream file(argv[2], std::ios::app);
    if (file.is_open()) {
        file << N << " " << duracion << endl;
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir los resultados." << endl;
    }

    return 0;
}




