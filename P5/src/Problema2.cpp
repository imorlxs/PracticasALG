//Problema 2

//Taylor Swift type problema

    #include <iostream>
    #include <vector>
    #include <limits>
    #include <iomanip>

    using namespace std;

    //Datos del enunciado

    const int n = 4;
    const vector<vector<int> > T = {
    	{0, 2, 1, 3}, 
    	{7, 0, 9, 2}, 
    	{2, 2, 0, 1}, 
    	{3, 4, 8, 0}
    }; 
    const int t_escala = 1;  //Como los tiempos son = para todas ciudades, no hace falta vector


    //Matriz para imprimir matrices

    void imprime_matriz(const string& label, vector<vector<int> > &matriz){
        cout << label << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(5) << matriz[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    //Adaptación del algoritmo de Floyd para el problema

    void floyd(vector<vector<int> > &t_minimos, vector<vector<int> > &ruta){
    	//Inicialización de ruta
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (i != j) 
                	ruta[i][j] = j;
                else 
                	ruta[i][j] = -1;
            }
        }

        imprime_matriz("[+] Matriz inicial: t_minimos", t_minimos);
        imprime_matriz("[+] Matriz inicial: ruta", ruta);

        //Se comprueban las rutas entre ciudades y se actualiza t_minimos y ruta

        for (int k = 0; k < n; k++){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (t_minimos[i][j] > (t_minimos[i][k] + t_escala + t_minimos[k][j])){ //Se verifica si con escala es menos costoso
                        t_minimos[i][j] = t_minimos[i][k] + t_escala + t_minimos[k][j]; //En caso afirmativo se actualiza
                        ruta[i][j] = ruta[i][k];
                    }
                }
            }

            //Se muestran las actualizaciones después de iterar en cada una de las ciudades
            cout << "[+] Después de considerar la ciudad: " << k << ":" << endl;
            imprime_matriz("t_minimos", t_minimos);
            imprime_matriz("ruta", ruta);
        }
    }

    //Función para imprimir un camino determinado y sus costos

    void imprime_camino(int i, int j, vector<vector<int> > &ruta, vector<vector<int> > &t_minimos){
        if (ruta[i][j] == -1) {
            cout << "[-] ERROR: no existe ruta de " << i << " a " << j << endl;
            return;
        }
        cout << "[+] Camino más corto entre ciudad " << i << " y " << j << ": " << i;

        int current = i; //Current es necesario para imprimir luego el coste
        while (current != j) {
            cout << " -> " << ruta[current][j];
            current = ruta[current][j];
        }
        cout << endl;
        cout << "	[*] Coste total del camino: " << t_minimos[i][j] << endl;
        cout << endl;
    }

int main(){

	vector<vector<int>> t_minimos = T; //Se inicializa a la matriz enunciado
	vector<vector<int> > ruta(n, vector<int>(n)); //Almacena la siguiente ciudad en el camino óptimo

    floyd(t_minimos, ruta);

    imprime_camino(0, 1, ruta, t_minimos);
    imprime_camino(0, 2, ruta, t_minimos);
    imprime_camino(0,3, ruta, t_minimos);

    imprime_camino(1, 0, ruta, t_minimos);
    imprime_camino(1, 2, ruta, t_minimos);
    imprime_camino(1, 3, ruta, t_minimos);

    imprime_camino(2, 0, ruta, t_minimos);
    imprime_camino(2, 1, ruta, t_minimos);
    imprime_camino(2, 3, ruta, t_minimos);

    imprime_camino(3, 0, ruta, t_minimos);
    imprime_camino(3, 1, ruta, t_minimos);
    imprime_camino(3, 2, ruta, t_minimos);
}