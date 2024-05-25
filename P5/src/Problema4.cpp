#include <iostream>
#include <vector>
#include <climits>

using namespace std;

pair<int, vector<int>> encontrarCaminoMenorDificultad(const vector<vector<int>>& coste) {
    int m = coste.size();
    int n = coste[0].size();

    // Creamos las tablas costmin y camino
    vector<vector<int>> costmin(m, vector<int>(n, INT_MAX));
    vector<vector<int>> camino(m, vector<int>(n, -1));

    // Inicialización de la última fila de la matriz de costes mínimos
    for (int j = 0; j < n; j++) {
        costmin[m-1][j] = coste[m-1][j];
    }

    // Llenar la tabla de costes mínimos de abajo hacia arriba
    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            // Verificar y actualizar costmin[i][j] considerando los movimientos permitidos (diagonales y arriba)
            if (j > 0 && costmin[i+1][j-1] + coste[i][j] < costmin[i][j]) {
                costmin[i][j] = costmin[i+1][j-1] + coste[i][j];
                camino[i][j] = j-1;
            }
            if (costmin[i+1][j] + coste[i][j] < costmin[i][j]) {
                costmin[i][j] = costmin[i+1][j] + coste[i][j];
                camino[i][j] = j;
            }
            if (j < n-1 && costmin[i+1][j+1] + coste[i][j] < costmin[i][j]) {
                costmin[i][j] = costmin[i+1][j+1] + coste[i][j];
                camino[i][j] = j+1;
            }
        }
    }

    // Encontrar el costo mínimo en la primera fila
    int min_coste = INT_MAX;
    int min_index = -1;
    for (int j = 0; j < n; j++) {
        if (costmin[0][j] < min_coste) {
            min_coste = costmin[0][j];
            min_index = j;
        }
    }

    // Reconstrucción del camino desde la cima hacia la base
    vector<int> camino_resultado;
    int current_j = min_index;
    for (int i = 0; i < m; i++) {
        camino_resultado.push_back(current_j);
        current_j = camino[i][current_j];
    }

    return {min_coste, camino_resultado};
}

int main() {
    vector<vector<int>> coste = {
        {2, 8, 9, 5, 8},
        {4, 4, 6, 2, 3},
        {5, 7, 5, 6, 1},
        {3, 2, 5, 4, 8}
    };

    auto resultado = encontrarCaminoMenorDificultad(coste);
    int min_coste = resultado.first;
    vector<int> camino = resultado.second;

    cout << "Costo mínimo: " << min_coste << endl;
    cout << "Camino: ";
    for (auto it = camino.rbegin(); it != camino.rend(); ++it){
        cout << *it << " "; 
    }
    cout << endl;

    return 0;
}
