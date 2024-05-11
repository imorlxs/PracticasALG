#include <iostream>
#include <vector>
using namespace std;

bool laberintoBacktracking(int tam, int fila, int columna, vector<vector<bool>>& laberinto, 
                            vector<vector<bool>>& visitado, vector<pair<int, int>>& camino){

    // Caso base: si estamos en la casilla de meta, dejará de buscar caminos
    if (fila == tam - 1 && columna == tam - 1) {
        camino.push_back({fila, columna});
        return true;
    }

    // Verificar si la casilla actual es transitble y no ha sido visitada
    if (fila >= 0 && fila < tam && columna >= 0 && columna < tam 
        && laberinto[fila][columna] && !visitado[fila][columna]){

        // Marcar la casilla como visitada y añadirla a la posible solución
        visitado[fila][columna] = true;
        camino.push_back({fila, columna});

        // Explorar las casillas adyacentes: derecha, izquierda, arriba, abajo (en ese orden)
        vector<pair<int, int>> direcciones = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        for (auto& direccion : direcciones) {
            int nueva_fila = fila + direccion.first;
            int nueva_columna = columna + direccion.second;
            if (laberintoBacktracking(tam, nueva_fila, nueva_columna, laberinto, 
                visitado, camino)) {
                return true;
            }
        }

        // Desmarcar la casilla como visitada y eliminarla de la posible solución si no
        // hay camino desde aquí
        visitado[fila][columna] = false;
        camino.pop_back();
    }

    return false;
}

// Función para resolver el laberinto
bool resolverLaberinto(vector<vector<bool>>& laberinto, vector<pair<int, int>>& camino){
    int tam = laberinto.size();
    vector<vector<bool>> visitado(tam, vector<bool>(tam, false));
    return laberintoBacktracking(tam, 0, 0, laberinto, visitado, camino);
}

void imprimirCamino(const vector<pair<int, int>>& camino) {
    cout << "Camino tomado: ";
    for (const auto& paso : camino) {
        cout << "(" << paso.first << ", " << paso.second << ") ";
    }
    cout << endl;
}

int main() {
    // Ejemplo de uso:
    vector<vector<bool>> laberinto = {
        {true, false, true, false, false},
        {true, true, true, false, true},
        {false, false, true, true, true},
        {true, true, false, false, true},
        {false, true, true, true, true}
    };

    vector<pair<int, int>> camino;
    if (resolverLaberinto(laberinto, camino)) {
        cout << "Hay un camino desde la entrada hasta la salida." << endl;
        imprimirCamino(camino);
    } else {
        cout << "No hay un camino desde la entrada hasta la salida." << endl;
    }

    return 0;
}
