//Problema 1

#include <iostream>
#include <vector>

using namespace std;

void intercambia_personalizado(int &max_score, int &current_score, vector<pair<int, int>> &best_pairs, vector<pair<int, int>> &current_pairs){
    if(current_score > max_score){
        max_score = current_score;
        best_pairs = current_pairs; //Actualiza las mejores parejas cuando encuentres un nuevo máximo
    }
}

void backtrack(int i, int current_score, int &max_score, vector<bool> &used, const vector<vector<int>> &p, int n, vector<pair<int, int>> &current_pairs, vector<pair<int, int>> &best_pairs) {
    if (i == n){
        intercambia_personalizado(max_score, current_score, best_pairs, current_pairs);
        return;
    }
    if (used[i]){
        backtrack(i + 1, current_score, max_score, used, p, n, current_pairs, best_pairs);
        return;
    }
    for (int j = 0; j < n; ++j){
        if (!used[j] && j != i){
            used[i] = used[j] = true;
            current_pairs.emplace_back(i, j); //Agrega el par actual a los emparejamientos
            int score_increment = p[i][j] * p[j][i];
            backtrack(i + 1, current_score + score_increment, max_score, used, p, n, current_pairs, best_pairs);
            current_pairs.pop_back(); //Elimina el par cuando retrocedes
            used[i] = used[j] = false;
        }
    }
}

int main(){
    int n;
    cout << "Ingrese el número de estudiantes (debe ser par): ";
    cin >> n;

    while(n % 2 != 0){
        cout << "El número de estudiantes debe ser par: " << endl;
        cin >> n;
    }

    vector<vector<int>> p(n, vector<int>(n));
    vector<bool> used(n, false);
    int max_score = 0;
    vector<pair<int, int>> best_pairs;
    vector<pair<int, int>> current_pairs;

    cout << "Ingrese la matriz de preferencias:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Pos [" << i << ']' << '[' << j << ']' << ": "; 
            cin >> p[i][j];
        }
    }

    backtrack(0, 0, max_score, used, p, n, current_pairs, best_pairs);

    cout << "Máximo puntaje de emparejamientos: " << max_score << endl;
    cout << "Parejas que contribuyen al máximo puntaje:" << endl;
    for (auto &pair : best_pairs) {
        cout << "(" << pair.first << ", " << pair.second << ")" << endl;
    }
    return 0;
}



