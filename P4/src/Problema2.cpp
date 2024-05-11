#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función para calcular la conveniencia total de la asignación de asientos obtenida
int calcularConveniencia(const vector<vector<int>>& matrizConveniencia, const vector<int>& ordenAsientos) {
    int convenienciaTotal = 0;
    int n = ordenAsientos.size();
    for (int i = 0; i < n; i++) {
        int vecinoIzqda = (i - 1 + n) % n;
        int vecinoDcha = (i + 1) % n;
        convenienciaTotal += matrizConveniencia[ordenAsientos[i]][ordenAsientos[vecinoIzqda]];
        convenienciaTotal += matrizConveniencia[ordenAsientos[i]][ordenAsientos[vecinoDcha]];
    }
    return convenienciaTotal;
}

// Función principal del algoritmo de backtracking que busca la asignación de asientos óptima
void backtrack(vector<vector<int>>& matrizConveniencia, vector<int>& ordenAsientos, int invitadoActual, int convenienciaMaxima, 
               int& mejorConveniencia, vector<int>& mejorAsignacionAsientos) {
    int n = matrizConveniencia.size();
    if (invitadoActual == n) {
        int convenienciaTotal = calcularConveniencia(matrizConveniencia, ordenAsientos);
        if (convenienciaTotal > mejorConveniencia) {
            mejorConveniencia = convenienciaTotal;
            mejorAsignacionAsientos = ordenAsientos;
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (find(ordenAsientos.begin(), ordenAsientos.end(), i) == ordenAsientos.end()) {
                ordenAsientos.push_back(i);
                backtrack(matrizConveniencia, ordenAsientos, invitadoActual + 1, convenienciaMaxima, 
                          mejorConveniencia, mejorAsignacionAsientos);
                ordenAsientos.pop_back();
            }
        }
    }
}

int main() {
    int n = 4;
    vector<vector<int>> matrizConveniencia = {
        {0, 10, 20, 30},
        {10, 0, 15, 25},
        {20, 15, 0, 30},
        {30, 25, 30, 0}
    };

    vector<int> ordenAsientos;
    int mejorConveniencia = 0;
    int primerInvitado = 0;
    int convenienciaMaxima = 0;
    vector<int> mejorAsignacionAsientos;

    backtrack(matrizConveniencia, ordenAsientos, primerInvitado, convenienciaMaxima, mejorConveniencia, mejorAsignacionAsientos);

    cout << "Conveniencia máxima entre los invitados: " << mejorConveniencia << endl;
    cout << "Asignación óptima de los invitados en los asientos de la mesa (en sentido antihorario): ";
    for (int i = 0; i < mejorAsignacionAsientos.size(); i++) {
        cout << mejorAsignacionAsientos[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}