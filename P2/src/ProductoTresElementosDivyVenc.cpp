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
    if(argc < 2){
        cerr << "Error, introduzca un numero" << endl;
        return -1;
    }

    int N;
    vector<int> vec(3,0);
    
    N = stoi(argv[1]);

    auto start = chrono::high_resolution_clock::now();

    vec = encontrarTresConsecutivos(N);

    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

   
    ofstream file("tiempo_ejecucion.txt");
    if (file.is_open()) {
        file << duration.count() << endl;
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir los resultados." << endl;
    }

    return 0;
}

