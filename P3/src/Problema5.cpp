#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para representar una arista
struct Calle {
    string name;
    int src, dest, weight;
};

// Estructura para representar un subconjunto para la unión y búsqueda
struct Subset {
    int parent, rank;
};

// Función para encontrar el conjunto al que pertenece un vértice (utiliza compresión de ruta)
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Función para unir dos conjuntos en uno solo (utiliza unión por rango)
void Union(vector<Subset>& subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Función para comparar dos aristas según su peso
bool compareCalles(Calle a, Calle b) {
    return a.weight < b.weight;
}

// Función principal de Kruskal para encontrar el MST
vector<Calle> kruskal(vector<Calle>& calles, int V) {
    // Ordenar las aristas por peso
    sort(calles.begin(), calles.end(), compareCalles);

    vector<Calle> result; // Almacenará las aristas del MST

    // Inicializar los subconjuntos
    vector<Subset> subsets(V);
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int e = 0; // Índice de la arista resultante

    // Iterar hasta que se hayan agregado V-1 aristas al MST
    int i = 0;
    while (e < V - 1 && i < calles.size()) {
        Calle next_calle = calles[i++];

        int x = find(subsets, next_calle.src);
        int y = find(subsets, next_calle.dest);

        // Si incluir esta arista no forma un ciclo, agregarla al MST
        if (x != y) {
            result.push_back(next_calle);
            Union(subsets, x, y);
            ++e;
        }
    }

    return result;
}

int main() {
    // Ejemplo de uso
    int V = 5; // Número de vértices

    // Plazas:
    // Azcárate = 0 
    // Maravillas = 1
    // Constitución = 2
    // Libertad = 3
    // Mayor = 4
    //
    // Lista de aristas: (src, dest, weight)
    vector<Calle> calles = {
        {"Serrano", 0, 3, 1100000},
        {"López Coste", 0, 4, 130000},
        {"No", 4, 3, 1300000},
        {"Portugalesa", 0, 2, 748456},
        {"Soriano", 0, 1, 450004},
        {"Jobenas", 1, 3, 555123},
        {"Bernabé", 2, 4, 554521},
        {"Anguila Coste", 2, 3, 1700000},
        {"Portugalesa de Arriba", 1, 2, 143552}

    };

    vector<Calle> MST = kruskal(calles, V);

    // Imprimir el MST
    cout << "Aristas del MST:" << endl;
    int suma = 0;
    for (const auto& calle : MST) {
        cout << calle.name << " " << calle.weight << endl;
        suma += calle.weight;
    }
  
    cout << "El coste de asfaltar todas las calles es de: " << suma << endl;
    return 0;
}

