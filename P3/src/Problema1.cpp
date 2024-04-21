#include <iostream>
#include <vector>
#include <utility> // Para pair

using namespace std;

// Declaración anticipada de las funciones
bool EsSolucion(const vector<pair<int, int>>& S, int n);
bool EsFactible(const vector<pair<int, int>>& S, int x, int y);
pair<int, int> SeleccionarPar(const vector<bool>& Disponibles, const vector<vector<int>>& p);

// Función principal para emparejar estudiantes
pair<vector<pair<int, int>>, int> EmparejarEstudiantes(const vector<vector<int>>& p, int n) {
    vector<pair<int, int>> S; // Conjunto de pares seleccionados
    vector<bool> Disponibles(n, true); // Todos los estudiantes están inicialmente disponibles
    int VE = 0; // Valor del emparejamiento

    while (!Disponibles.empty() && !EsSolucion(S, n)) {
        auto [x, y] = SeleccionarPar(Disponibles, p);
        if (x != -1 && y != -1 && EsFactible(S, x, y)) {
            S.push_back({x, y});
            VE += p[x][y] * p[y][x];
            Disponibles[x] = false;
            Disponibles[y] = false;
        }
    }

    if (EsSolucion(S, n)) {
        return {S, VE}; // Devuelve el conjunto de pares y el valor total del emparejamiento
    } else {
        throw runtime_error("No hay solución");
    }
}

// Función para seleccionar la mejor pareja para el primer estudiante disponible
pair<int, int> SeleccionarPar(const vector<bool>& Disponibles, const vector<vector<int>>& p) {
    int maxValor = 0;
    pair<int, int> parSeleccionado = {-1, -1};
    int i = 0; // Asignar a 'i' el índice del primer estudiante disponible
    
    // Encontrar el primer estudiante disponible
    for (; i < Disponibles.size(); ++i) {
        if (Disponibles[i]) {
            break;
        }
    }
    
    // Si todos los estudiantes están emparejados, i será igual a Disponibles.size()
    if (i == Disponibles.size()) {
        return parSeleccionado; // Todos los estudiantes están emparejados
    }
    
    // Buscar la mejor pareja para el estudiante i
    for (int j = 0; j < Disponibles.size(); ++j) {
        if (i != j && Disponibles[j] && p[i][j] * p[j][i] > maxValor) {
            maxValor = p[i][j] * p[j][i];
            parSeleccionado = {i, j};
        }
    }
    return parSeleccionado;
}


// Función para comprobar si se ha encontrado una solución
bool EsSolucion(const vector<pair<int, int>>& S, int n) {
    return S.size() == n / 2;
}

// Función para comprobar si una pareja es factible
bool EsFactible(const vector<pair<int, int>>& S, int x, int y) {
    for (const auto& par : S) {
        if (par.first == x || par.second == x || par.first == y || par.second == y) {
            return false;
        }
    }
    return true;
}

// Ejemplo de uso de la función EmparejarEstudiantes
int main() {
    vector<vector<int>> p = {
        {2, 5, 3, 5},
        {7, 4, 8, 7},
        {2, 6, 0, 6},
        {4, 10, 9, 3}
    };
    int n = 4;

    try {
        auto [S, VE] = EmparejarEstudiantes(p, n);
        cout << "Parejas seleccionadas y su valor de emparejamiento:" << endl;
        for (const auto& par : S) {
            cout << "(" << par.first << ", " << par.second << ") ";
        }
        cout << "\nValor total del emparejamiento: " << VE << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
