#include <iostream>
#include <vector>

using namespace std;

// Función usada para devolver el valor de conveniencia entre 2 invitados
int valorEmparejamiento(int invitado1, int invitado2, const vector<vector<int>>& matrizConveniencia) {
  return matrizConveniencia[invitado1][invitado2];
}

// Función usada para encontrar el candidato más conveniente para el invitado seleccionado
int encontrarMejorInvitado(int invitadoActual, const vector<vector<int>>& matrizConveniencia, vector<bool>& disponibles, int& mejorValorEmparejamiento) {
  int mayorValorEmparejamiento = -1;
  int mejorInvitado = -1;

  for (int i = 0; i < disponibles.size(); i++) {
    if (disponibles[i] && i != invitadoActual) {
      int valorEmparejamientoActual = valorEmparejamiento(invitadoActual, i, matrizConveniencia);
      if (valorEmparejamientoActual > mayorValorEmparejamiento) {
        mayorValorEmparejamiento = valorEmparejamientoActual;
        mejorInvitado = i;
      }
    }
  }

  // Actualizar el mejor valor de emparejamiento si es que encontramos uno 
  int valorActualTotalEmparejamiento = 0;
  for (int i = 0; i < disponibles.size(); i++) {
    if (disponibles[i]) {
      valorActualTotalEmparejamiento += valorEmparejamiento(invitadoActual, i, matrizConveniencia);
    }
  }

  if (valorActualTotalEmparejamiento > mejorValorEmparejamiento) {
    mejorValorEmparejamiento = valorActualTotalEmparejamiento;
  }

  return mejorInvitado;
}

// Función para verificar si la disposición de asientos es factible
bool esFactible(const vector<int>& sentados, const vector<vector<int>>& matrizConveniencia) {
  for (int i = 0; i < sentados.size(); i++) {
    int izquierda = sentados[(i + 1) % sentados.size()];
    int derecha = sentados[(i - 1 + sentados.size()) % sentados.size()];

    if (valorEmparejamiento(sentados[i], izquierda, matrizConveniencia) == 0 ||
        valorEmparejamiento(sentados[i], derecha, matrizConveniencia) == 0) {
      return false;
    }
  }

  return true;
}

// Algoritmo voraz principal para la asignación de los asientos
vector<int> asignacionGreedy(const vector<vector<int>>& matrizConveniencia) {
  int n = matrizConveniencia.size();
  vector<int> sentados;
  vector<bool> disponibles(n, true);
  int mejorValorEmparejamiento = -1;

  // Empezamos con un invitado aleatorio
  int invitadoActual = rand() % n;
  sentados.push_back(invitadoActual);
  disponibles[invitadoActual] = false;

  // Rellenamos los asientos restantes
  for (int i = 1; i < n; i++) {
    int invitadoMasAdecuado = encontrarMejorInvitado(sentados[i - 1], matrizConveniencia, disponibles, mejorValorEmparejamiento);
    sentados.push_back(invitadoMasAdecuado);
    disponibles[invitadoMasAdecuado] = false;
  }

  // Comprobar si la asignación es factible o no
  if (!esFactible(sentados, matrizConveniencia)) {
    cout << "Asignación no factible encontrada" << endl;
    return {};
  }

  return sentados;
}

int main() {
  // Datos de ejemplo del diseño
  vector<vector<int>> matrizConvenienciaEjemplo = {
    {0, 80, 60, 70},
    {80, 0, 90, 85},
    {60, 90, 0, 75},
    {70, 85, 75, 0},
  };

  // Calcular las asignaciones de la mesa de invitados con el algoritmo propuesto
  vector<int> mesa = asignacionGreedy(matrizConvenienciaEjemplo);


  cout << "Asignación de asientos en la mesa circular (sentido antihorario):";
  for (int asiento = 1; asiento <= mesa.size(); asiento++) {
    cout << asiento << " ";
  }
  cout << endl;


  return 0;
}
