#include <iostream>
#include <vector>
#include <set>
using namespace std;

void eliminaRepetidos1(vector<int> &v){

    vector<bool> repetidos(v.size(), false);
    vector<int> nuevoV;

    for (int i = 0; i < v.size(); i++){
        for (int j = i+1; j < v.size(); j++){
            if (v[i] == v[j])
                repetidos[j] = true;
        }
    }

    for (int i = 0; i < v.size(); i++){
        if (!repetidos[i])
            nuevoV.push_back(v[i]);
    }

    v = nuevoV;

}

void eliminaRepetidos2(vector<int> &v){

    set<int> nuevoV;

    for (int i = 0; i < v.size(); i++){
        nuevoV.insert(v[i]);
    }

    v.clear();

    for (int i : nuevoV){
        v.push_back(i);
    }

}

int main(int argc, char* argv){

    vector<int> vec = {1, 2, 2, 4, 5, 9, 4, 2, 4, 6, 6, 3, 9, 0};

    cout << "Vector original: ";
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;

    // Llamada a la función eliminarRepetidos
    // eliminaRepetidos1(vec);
    eliminaRepetidos2(vec);

    cout << "Vector sin elementos repetidos: ";
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}