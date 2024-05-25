//Problema 2

//Taylor Swift type problema

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

const int INF = numeric_limits<int>::max();
const int n = 4;  // Número de ciudades

// Implementación usando matrices globales por simplicidad
int T[n][n] = {{0, 2, 1, 3}, {7, 0, 4, 2}, {2, 2, 0, 1}, {3, 4, 8, 0}};
int E[n] = {1, 1, 1, 1};  // Tiempos de espera en cada ciudad
int dp[n][n];
int nextCity[n][n];

void printMatrix(const string& label, int matrix[n][n]) {
    cout << label << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << matrix[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

void floydWarshall() {
    // Inicialización de dp y nextCity
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = T[i][j];
            if (i != j && T[i][j] != INF) nextCity[i][j] = j;
            else nextCity[i][j] = -1;
        }
    }

    //printMatrix("Initial dp", dp);
    //printMatrix("Initial nextCity", nextCity);

    // Aplicar la recurrencia
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][k] != INF && dp[k][j] != INF && dp[i][j] > dp[i][k] + E[k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + E[k] + dp[k][j];
                    nextCity[i][j] = nextCity[i][k];
                }
            }
        }

        //cout << "After considering city " << k << ":\n";
        //printMatrix("dp", dp);
        //printMatrix("nextCity", nextCity);
    }
}

void printPath(int i, int j) {
    if (nextCity[i][j] == -1) {
        cout << "No path from " << i << " to " << j << "\n";
        return;
    }
    cout << "Path from " << i << " to " << j << ": " << i;
    while (i != j) {
        i = nextCity[i][j];
        cout << " -> " << i;
    }
    cout << "\n";
}

int main() {
    floydWarshall();
    //Mostrar el camino de 0 a 3
    printPath(0, 1);
    printPath(0,2);
    printPath(0,3);

    printPath(1, 0);
    printPath(1,2);
    printPath(1,3);

    printPath(2, 0);
    printPath(2,1);
    printPath(2,3);

    printPath(3, 0);
    printPath(3,1);
    printPath(3,2);

    printPath(0,0);
    return 0;
}
