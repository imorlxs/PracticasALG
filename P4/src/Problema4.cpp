#include <iostream>
#include <vector>
using namespace std;

bool laberinto_backtracking(int tam, int fila, int columna, vector<vector<bool>>& laberinto, vector<vector<bool>>& visitado, vector<pair<int, int>>& camino){

    // Caso base: si estamos en la casilla de salida
    if (fila == tam - 1 && columna == tam - 1) {
        camino.push_back({fila, columna});
        return true;
    }

    // Verificar si la casilla actual es transitble y no ha sido visitada
    if (fila >= 0 && fila < tam && columna >= 0 && columna < tam && laberinto[fila][columna] && !visitado[fila][columna]){

        // Marcar la casilla como visitada
        visitado[fila][columna] = true;
        camino.push_back({fila, columna});

        // Explorar las casillas adyacentes
        vector<pair<int, int>> direcciones = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto& direccion : direcciones) {
            int nueva_fila = fila + direccion.first;
            int nueva_columna = columna + direccion.second;
            if (laberinto_backtracking(tam, nueva_fila, nueva_columna, laberinto, visitado, camino)) {
                return true;
            }
        }

        // Desmarcar la casilla como visitada si no hay camino desde aquí
        visitado[fila][columna] = false;
        camino.pop_back();
    }

    return false;
}

// Función para resolver el laberinto
bool resolver_laberinto(vector<vector<bool>>& laberinto, vector<pair<int, int>>& camino){
    int tam = laberinto.size();
    vector<vector<bool>> visitado(tam, vector<bool>(tam, false));
    return laberinto_backtracking(tam, 0, 0, laberinto, visitado, camino);
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
    if (resolver_laberinto(laberinto, camino)) {
        cout << "Hay un camino desde la entrada hasta la salida." << endl;
        imprimirCamino(camino);
    } else {
        cout << "No hay un camino desde la entrada hasta la salida." << endl;
    }

    return 0;
}


//////////////////////////////////////// PSEUDOCÓDIGO /////////////////////////////////////////
/*
Función laberinto_backtracking(tam, fila, columna, laberinto, visitado, camino)
    Si fila == tam - 1 y columna == tam - 1 Entonces
        Agregar {fila, columna} a camino
        Devolver Verdadero
    Fin Si

    Si fila está dentro de 0 a tam - 1 y columna está dentro de 0 a tam - 1 y laberinto[fila][columna] es Verdadero y visitado[fila][columna] es Falso Entonces
        Marcar visitado[fila][columna] como Verdadero
        Agregar {fila, columna} a camino

        Direcciones = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}
        Para cada dirección en Direcciones Hacer
            nueva_fila = fila + dirección[0]
            nueva_columna = columna + dirección[1]
            Si laberinto_backtracking(tam, nueva_fila, nueva_columna, laberinto, visitado, camino) Entonces
                Devolver Verdadero
            Fin Si
        Fin Para

        Desmarcar visitado[fila][columna] como Falso
        Quitar el último elemento de camino
    Fin Si

    Devolver Falso
Fin Función
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////