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

void backtrack(int i, int current_score, int &max_score, vector<bool> &used, const vector<vector<int>> &p, int n, vector<pair<int, int>> &current_pairs, vector<pair<int, int>> &best_pairs){
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
    int n = 4;
    vector<vector<int>> p(n, vector<int>(n));
    vector<bool> used(n, false);
    int max_score = 0;
    vector<pair<int, int>> best_pairs;
    vector<pair<int, int>> current_pairs;

    //Matriz de preferencia

    p[0][0] = 3 ; p[0][1] = 7 ; p[0][2] = 2 ; p[0][3] = 8 ; 
    p[1][0] = 4 ; p[1][1] = 6 ; p[1][2] = 9 ; p[1][3] = 5 ; 
    p[2][0] = 1 ; p[2][1] = 0 ; p[2][2] = 10 ; p[2][3] = 2 ; 
    p[3][0] = 7 ; p[3][1] = 3 ; p[3][2] = 6; p[3][3] = 4 ; 

    backtrack(0, 0, max_score, used, p, n, current_pairs, best_pairs);

    cout << "Máximo puntaje de emparejamientos: " << max_score << endl;
    cout << "Parejas que contribuyen al máximo puntaje:" << endl;
    for (auto &pair : best_pairs) {
        cout << "(" << pair.first << ", " << pair.second << ")";
    }
    cout << endl;
}



