#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

// Función para encontrar el camino más corto desde el nodo origen a todos los nodos sensores
pair<vector<int>, vector<int>> Dijkstra(const vector<vector<int>>& L, int origen, int n) {
    vector<int> D(n, INF); // Distancias al origen
    vector<int> P(n, -1); // Predecesores en la ruta
    set<int> C; // Conjunto de nodos por visitar

    // Inicialización
    for (int i = 1; i < n; ++i) {
        if (i != origen) {
            C.insert(i);
            D[i] = L[origen][i];
            P[i] = origen;
        }
    }
    D[origen] = 0;

    // Bucle principal
    while (!C.empty()) {
        // Encuentra el nodo v en C que minimiza D[v]
        int v = *min_element(C.begin(), C.end(), [&](int a, int b) { return D[a] < D[b]; });
        C.erase(v);

        // Relajación
        for (int i = 1; i < n; ++i) {
            if (C.find(i) != C.end() && L[v][i] != INF && D[i] > D[v] + L[v][i]) {
                D[i] = D[v] + L[v][i];
                P[i] = v;
            }
        }
    }

    return {D, P};
}

int main() {
    // Ejemplo de uso del algoritmo de Dijkstra
    // Número de nodos incluyendo el servidor central
    int n = 5;
    
    // Matriz de adyacencia con los costos de envío (tiempo de transmisión)
    vector<vector<int>> L = {
        {INF, 5, 10, INF, INF},
        {5, INF, 3, 8, INF},
        {10, 3, INF, 2, 6},
        {INF, 8, 2, INF, 7},
        {INF, INF, 6, 7, INF}
    };
    
    // El servidor central es el nodo 0
    int servidor_central = 0;

    auto [D, P] = Dijkstra(L, servidor_central, n);
    
    // Imprimir el coste del camino más corto y el camino elegido para cada nodo sensor
    for (int i = 1; i < n; ++i) {
        cout << "Coste más corto desde el nodo " << servidor_central << " al nodo " << i << " es " << D[i] << endl;
        cout << "Camino: ";
        int j = i;
        while (P[j] != -1) {
            cout << j << " <- ";
            j = P[j];
        }
        cout << servidor_central << endl;
    }

    return 0;
}
