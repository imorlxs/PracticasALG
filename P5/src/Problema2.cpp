//Problema 2

//Taylor Swift type problema

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

//Datos del enunciado

const int n = 4;
const vector<vector<int> > T = {
	{0, 2, 1, 3}, 
	{7, 0, 4, 2}, 
	{2, 2, 0, 1}, 
	{3, 4, 8, 0}
}; 
const int t_escala = 1;  //Como los tiempos son = para todas ciudades, no hace falta vector

void floyd(vector<vector<int> > &t_minimos, vector<vector<int> > &ruta){
	//Inicialización de ruta
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j) 
            	ruta[i][j] = j;
            else 
            	ruta[i][j] = -1;
        }
    }

    //printMatrix("Initial t_minimos", t_minimos);
    //printMatrix("Initial ruta", ruta);

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (t_minimos[i][j] > t_minimos[i][k] + t_escala + t_minimos[k][j]){
                    t_minimos[i][j] = t_minimos[i][k] + t_escala + t_minimos[k][j];
                    ruta[i][j] = ruta[i][k];
                }
            }
        }

        //cout << "After considering city " << k << ":\n";
        //printMatrix("t_minimos", t_minimos);
        //printMatrix("ruta", ruta);
    }
}

void printPath(int i, int j, vector<vector<int> > &ruta) {
    if (ruta[i][j] == -1) {
        cout << "[-] ERROR:  no existe ruta de " << i << " a " << j << "\n";
        return;
    }
    cout << "[+] Camino más corto entre ciudad " << i << " y " << j << ": " << i;
    while (i != j) {
        i = ruta[i][j];
        cout << " -> " << i;
    }
    cout << "\n";
}

int main() {

	vector<vector<int>> t_minimos = T;
	vector<vector<int> > ruta(n, vector<int>(n));

    floyd(t_minimos, ruta);

    printPath(0, 1, ruta);
    printPath(0, 2, ruta);
    printPath(0,3, ruta);

    printPath(1, 0, ruta);
    printPath(1, 2, ruta);
    printPath(1, 3, ruta);

    printPath(2, 0, ruta);
    printPath(2, 1, ruta);
    printPath(2, 3, ruta);

    printPath(3, 0, ruta);
    printPath(3, 1, ruta);
    printPath(3, 2, ruta);
}
