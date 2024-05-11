#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Nodo {
    int x, y; // Posición en el laberinto
    int coste; // Coste acumulado para llegar aquí
    vector<pair<int, int>> camino; // Camino tomado para llegar aquí
};

bool esValido(int x, int y, int n, const vector<vector<bool>>& laberinto, const vector<vector<bool>>& visitado) {
    return x >= 0 && x < n && y >= 0 && y < n && laberinto[x][y] && !visitado[x][y];
}

int main() {
    int n = 10;
    vector<vector<bool>> laberinto = {
    {true,  false, true,  true,  false, false, true,  true,  false, true},
    {true,  true,  true,  false, true,  true,  true,  false, true,  true},
    {false, true,  false, true,  true,  false, false, true,  true,  false},
    {true,  true,  true,  true,  false, true,  true,  true,  false, true},
    {true,  false, false, true,  true,  true,  false, true,  true,  true},
    {true,  true,  false, false, true,  false, true,  true,  false, true},
    {true,  false, true,  true,  true,  true,  true,  false, true,  true},
    {false, true,  true,  false, false, true,  false, true,  true,  true},
    {true,  true,  false, true,  true,  true,  true,  true,  false, false},
    {false, true,  true,  true,  false, true,  true,  true,  true,  true}
};


    vector<vector<bool>> visitado(n, vector<bool>(n, false));
    queue<Nodo> LVV; // Lista de nodos por explorar
    Nodo raiz = {0, 0, 0, {{0, 0}}};
    LVV.push(raiz);
    int C = INT_MAX;
    vector<pair<int, int>> Sol;

    while (!LVV.empty()) {
        Nodo X = LVV.front();
        LVV.pop();
        visitado[X.x][X.y] = true;

        if (X.coste < C) {
            int dx[4] = {1, 0, -1, 0}; // movimientos en x: abajo, derecha, arriba, izquierda
            int dy[4] = {0, 1, 0, -1}; // movimientos en y: abajo, derecha, arriba, izquierda
            for (int i = 0; i < 4; i++) {
                int nx = X.x + dx[i];
                int ny = X.y + dy[i];
                if (nx == n - 1 && ny == n - 1) { // si es la solución final
                    Sol = X.camino;
                    Sol.push_back({nx, ny});
                    C = X.coste + 1;
                    break;
                }
                if (esValido(nx, ny, n, laberinto, visitado)) {
                    Nodo Y = {nx, ny, X.coste + 1, X.camino};
                    Y.camino.push_back({nx, ny});
                    if (Y.coste < C) {
                        LVV.push(Y);
                    }
                }
            }
        }
    }

    if (!Sol.empty()) {
        cout << "Camino más corto encontrado: ";
        for (auto& p : Sol) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << "\nCoste: " << C << endl;
    } else {
        cout << "No se encontró solución." << endl;
    }

    return 0;
}