#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

enum Movimientos {IZQUIERDA, ABAJO, DIAGONAL};
string enumtoString(Movimientos mov){
  switch (mov) {
        case IZQUIERDA: return "IZQUIERDA";
        case ABAJO: return "ABAJO";
        case DIAGONAL: return "DIAGONAL";
        default: return "UNKNOWN";
    }
}

int oro(int i, int j, vector<vector<char>> mapa){
  int filas = mapa.size();
  int columnas = mapa[0].size(); // Asumiendo que todas las filas tienen la misma longitud.
  if (i < 0 || i >= filas) {
      throw std::out_of_range("Índice de fila fuera de rango");
  }
  if (j < 0 || j >= columnas) {
      throw std::out_of_range("Índice de columna fuera de rango");
  }
  if (mapa[i][j] == 'O')
    return 1;
  else if (mapa[i][j] == 'M') {
    return -100;
  }
  else 
    return 0;
}

pair<int, vector<vector<int>>> costeOptimo(vector<vector<char>>& mapa){
  int f = mapa.size();
  int c = mapa[0].size();

  vector<vector<int>> resultado(f, vector<int>(c, 0));

  for (int i = f-2; i >= 0; i--){
    resultado[i][0] = resultado[i+1][0] + oro(i,0,mapa);
  }
  
  for (int j = 1; j < c; j++)
    resultado[f-1][j] = resultado[f-1][j-1] + oro(f-1,j,mapa);

  for (int i = f-2; i >= 0; i--){
    for (int j = 1; j < c; j++){
      resultado[i][j] = max({resultado[i+1][j], resultado[i][j-1], 
          resultado[i+1][j-1]}) + oro(i,j,mapa);
    }
  }
  return make_pair(resultado[0][c-1], resultado);
}

vector<Movimientos> recuperaPasos(vector<vector<int>>& matriz){
  vector<Movimientos> resultado;
  int i = 0;
  int j  = matriz[0].size() - 1;
  int max, index;
  int movs[3];
  while(i < matriz.size() - 1 || j > 0){
    movs[0] = (j > 0) ? matriz[i][j-1] : -1;
    movs[1] = (i < matriz.size() - 1) ? matriz[i+1][j] : -1;
    movs[2] = (i < matriz.size() - 1 && j > 0) ? matriz[i+1][j-1] : -1;

    max = INT_MIN;
    index = -1;

    for (int x = 0; x < 3; x++){
      if (movs[x] > max){
          max = movs[x];
          index = x;
        }
      }

      if (i < matriz.size() - 1 && j > 0 && index == 2){
          j--;
          i++;
          resultado.push_back(DIAGONAL);
        }

      if (index == 0){
        j--;
        resultado.push_back(IZQUIERDA);
      }

      if (index == 1){
        i++;
        resultado.push_back(ABAJO);
      }

    }
  return resultado;
}

int main(int argc, char* argv[]) {

  if (argc != 2){
    cerr << "Uso: Problema3 <mapa.txt>" << endl;
    exit(-1);
  }


  ifstream infile(argv[1]);
  if (!infile) {
      cerr << "No se pudo abrir el archivo " << argv[1]  << endl;
      exit(-1);
  }

  int f, c;
  infile >> f >> c;

  vector<vector<char>> map(f, vector<char>(c));
  char cell;

  for (int i = 0; i < f; ++i) {
      for (int j = 0; j < c; ++j) {
          infile >> cell;
          if (cell == '-' || cell == 'M' || cell == 'O') {
              map[i][j] = cell; // Casilla libre
          }
          else{
            cerr << "Formato del mapa inválido. '-' libre, 'M' muro, 'O' oro" << endl;
            exit(-1);
          }
      }
  }

  infile.close();

  for (int i = 0; i < map.size(); i++){
    for (int j = 0; j < map[0].size(); j++)
      cout << map[i][j] << " ";
    cout << endl;
    }

  auto res = costeOptimo(map);
  int oro = res.first;
  auto vector = res.second;
  if (oro >= 0){
    cout << "La cantidad máxima de oro que se puede recolectar es: " << oro << endl;

    auto pasos = recuperaPasos(vector);
    cout << "Los pasos a seguir son: " << endl;

    for (Movimientos paso : pasos){
      cout << enumtoString(paso) << " ";
    }
    cout << endl;
  } else{
      cerr << "EL JUGADOR NO PUEDE AVANZAR" << endl;
  }
    return 0;
}

