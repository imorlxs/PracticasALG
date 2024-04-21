#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <queue>

using namespace std;

#define LIM 999

struct Arista{
	int hacia;
	int peso;
};


void addArista(map<int, vector<Arista>>& grafo, int desde, int hacia, int peso){
	grafo[desde].push_back({hacia, peso});
	grafo[hacia].push_back({desde, peso});
}

vector<int> calcularminParadas(int nodoFin, map<int, vector<Arista>>& grafo){
	vector<int> minParadas(grafo.size(), LIM);
	queue<int> q;
	q.push(nodoFin);
	minParadas[nodoFin] = 0;
	
	while(!q.empty()){
		int actual = q.front();
		q.pop();
		
		for(Arista& arista : grafo[actual]){
			if(minParadas[arista.hacia] == LIM){
				q.push(arista.hacia);
				minParadas[arista.hacia] = minParadas[actual] + 1;
			}
		}
	}
	
	return minParadas;
}

int encontrarSiguienteParada(int nodoActual, int tanqueGas, const vector<int>& minParadas, map<int, vector<Arista>>& grafo, vector<bool>& visitado){
	int nextNodo = -1;
	int minParadas_to_Dest = LIM;
	
	for (const Arista& arista : grafo[nodoActual]){
		if(!visitado[arista.hacia] && arista.peso <= tanqueGas && minParadas[arista.hacia] < minParadas_to_Dest){
			nextNodo = arista.hacia;
			minParadas_to_Dest = minParadas[arista.hacia];
		}
	}
	
	return nextNodo;
}

vector<int> minParadasRepostar(int start, int end, int tanqueGas, map<int, vector<Arista>>& grafo){
	vector<int> paradas;
	vector<bool> visitadas(grafo.size(), false);
	vector<int> minParadas = calcularminParadas(end, grafo);
	
	int nodoActual = start;
	while(nodoActual != end) {
		visitadas[nodoActual] = true;
		int nextNodo = encontrarSiguienteParada(nodoActual, tanqueGas, minParadas, grafo, visitadas);
		if(nextNodo == -1){
			cout << "No se puede llegar al destino con el tanque actual" << endl;
			return{};
		}
		
		paradas.push_back(nextNodo);
		nodoActual = nextNodo;
	}
	
	return paradas;
}


int main() {
    map<int, vector<Arista>> graph;
    
    // Añadir aristas al grafo
    addArista(graph, 0, 1, 150);
    addArista(graph, 0, 2, 200);
    addArista(graph, 0, 3, 100);
    addArista(graph, 1, 2, 100);
    addArista(graph, 2, 3, 100);
    addArista(graph, 1, 5, 300);
    addArista(graph, 2, 7, 150);
    addArista(graph, 2, 4, 200);
    addArista(graph, 3, 4, 100);
    addArista(graph, 4, 7, 250);
    addArista(graph, 5, 6, 300);
    addArista(graph, 5, 7, 300);

    int startNode = 0;
    int endNode = 6;
    int tanqueGas = 300;

    vector<int> paradas = minParadasRepostar(startNode, endNode, tanqueGas, graph);

    cout << "Paradas de repostaje: ";
    for (int parada : paradas) {
        cout << parada << " ";
    }
    cout << endl;
    return 0;
}
