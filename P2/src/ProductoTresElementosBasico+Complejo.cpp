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
    int N;
    vector<int> vec(3,0);

    if(argc < 2){
        cerr << "Error, introduce el numero del que quieres encontrar el producto." << endl;
        return -1;
    }

    N = stoi(argv[1]);

    
    auto start = chrono::high_resolution_clock::now();
    vec = esProductoDeTresConsecutivos(N);
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
