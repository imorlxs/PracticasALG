#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

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

  auto res = costeOptimo(map);
  int oro = res.first;
  auto vector = res.second;
  cout << "La cantidad máxima de oro que se puede recolectar es: " << oro << endl;

  for (int i = 0; i < vector.size(); i++){
    for (int j = 0; j < vector[0].size(); j++)
      cout << vector[i][j] << " ";
    cout << endl;
    }

    return 0;
}

