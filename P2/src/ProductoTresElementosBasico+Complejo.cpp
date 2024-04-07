#include <iostream>
#include <string>
#include <vector>
#include <chrono> // Para medir el tiempo de ejecución
#include <fstream> // Para escribir en un archivo
using namespace std;

vector<int> esProductoDeTresConsecutivos(int N){
    vector<int> vec(3,0);
    for(int i=0; ;i++){
        int producto = i * (i+1) * (i+2);

        if(producto == N){
            vec[0] = i;
            vec[1] = i+1;
            vec[2] = i+2;
            return vec;
        }
        else if(producto > N){
            break;
        }

    }
    return vec;
}

int main(int argc, char** argv){
    if(argc < 3){
        cerr << "Error, introduzca un numero y el nombre del archivo de salida" << endl;
        return -1;
    }
    
    chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    int N;
    vector<int> vec(3,0);
    
    N = stoi(argv[1]);

    // Inicia el cronómetro
    start = chrono::high_resolution_clock::now();
    vec = esProductoDeTresConsecutivos(N);
    stop = chrono::high_resolution_clock::now();

    unsigned long duracion = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    ofstream file(argv[2], std::ios::app);
    if (file.is_open()) {
        file << N << " " << duracion << endl;
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir los resultados." << endl;
    }

   

    return 0;
}
