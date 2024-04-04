/*****************************************************
 * Álvaro Maldonado Medina
 * Grupo: 2ºD, subgrupo de prácticas D1
 * @file OrganizarCalendarioCampeonatoDyV.cpp
 * ¿Usa Divide y Vencerás? -->  SÍ
*****************************************************/

/**
 * ENUNCIADO:
 * 
 * Se organiza un torneo con n participantes. Cada participante tiene que competir exactamente una vez con
 * todos los posibles oponentes. Además, cada participante tiene que jugar exactamente un partido cada día. Por
 * concreción, y sin perdida de generalidad, puede suponerse que las competiciones se celebran en días
 * sucesivos y que cada participante compite una vez por día. Podemos suponer que el número de participantes
 * es potencia de dos, lo que nos simplificará el problema (no es necesario que haya jornadas de descanso). Por
 * lo tanto n = 2^k participantes, con k entero positivo. Se pide construir un calendario que permita que el torneo
 * concluya en n-1 días
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

// Función para imprimir el calendario del torneo
void imprimirCalendario(const vector<vector<pair<int,int>>>& calendario){
    int dia = 1;
    for (const auto& partidos : calendario){
        cout << "Jornada " << dia++ << ": " << endl;
        for (const auto& partido : partidos){
            cout << partido.first << " vs " << partido.second << endl;
        }
    }

    cout << "\n\n";
}

// Método para rotar los equipos y evitar tanto repeticiones como valores inválidos
// Ejemplo: que '1' juegue con '1' o que haya '4' equipos y el '3' juegue con el '5'
void rotarEquipos(vector<int>& equipos){
    
    // Guardamos "bajo llave" el primer equipo, que no se moverá
    int equipoFijo = equipos[0];
    
    // Guardamos el segundo equipo para moverlo al final tras la rotación de todos los demás
    int equipoMoverFinal = equipos[1];

    // Rotación de los equipos
    for (int i = 1; i < equipos.size() - 1; i++)
        equipos[i] = equipos[i+1];
    
    //Colocamos el segundo equipo al final del todo
    equipos[equipos.size() - 1] = equipoMoverFinal;
    
    // Restauramos el equipo fijo
    equipos[0] = equipoFijo;
}

vector<vector<pair<int,int>>> construirCalendarioDyV(vector<int>& equipos, int inicio, int fin){
    // Casos base: sólo hay uno o dos equipos
    if (inicio == fin){
        return{};
    } else if (fin - inicio == 1){
        return {{make_pair(equipos[inicio], equipos[fin])}};
    } else {
        // Dividimos en dos mitades
        int mitad = (inicio + fin) / 2;
        vector<vector<pair<int,int>>> calendarioIzquierda = construirCalendarioDyV(equipos, inicio, mitad);
        vector<vector<pair<int,int>>> calendarioDerecha = construirCalendarioDyV(equipos, mitad + 1, fin);

        //Combinamos los partidos generados por cada mitad
        vector<vector<pair<int,int>>> calendarioActual;
        calendarioActual.reserve(calendarioActual.size() + calendarioDerecha.size());
        calendarioActual.insert(calendarioActual.end(), calendarioIzquierda.begin(), calendarioIzquierda.end());
        calendarioActual.insert(calendarioActual.end(), calendarioDerecha.begin(), calendarioDerecha.end());

        //Realizamos la rotación de equipos y añadimos los partidos adicionales
        for (int i = 1; i < fin - inicio; i++){
            rotarEquipos(equipos);
            for (int j = 0; j < calendarioIzquierda.size(); j++){
                calendarioActual[j].emplace_back(make_pair(equipos[j], equipos[fin - inicio]));
            }
        }

        return calendarioActual;
    }
}

// Comprobar si un número es potencia de 2
bool esPotenciaDeDos(int n){
    return n > 0 && (n & (n-1)) == 0;
}

int main(int argc, char **argv){

    int n;  //nº de partidos
    
    // Realizamos comprobación sobre el argumento dado (nº de equipos a sortear)

    if (argc != 2)
    {
        cerr << "Error, se ha introducido un número de argumentos inválido" << endl;
        cerr << "Uso del programa: ./OrganizarCalendarioCampeonato <nº de equipos>" << endl;
        exit(-1);
    } 
    else if ( !esPotenciaDeDos( atoi(argv[1]) ) )
    {
        cerr << "Error, el número de participantes debe ser una potencia de dos" << endl;
        exit(-2);
    }
    else
    {
        n = atoi(argv[1]);

        cout << "[+] Se han introducido " << n << " equipos en la liga, se procede a realizar el sorteo..." << endl;

        // Generamos vector auxiliar con los equipos a sortear aquí
        vector<int> equipos(n);
        for (int i = 0; i < n; i++){
            equipos[i] = i+1;
        }

        // Construcción e impresión por pantalla del calendario
        vector<vector<pair<int,int>>> calendario = construirCalendarioDyV(equipos, 0, n - 1);
        cout << "Calendario del torneo:" << endl;
        imprimirCalendario(calendario);

        /*// Imprime el calendario generado
        for (int i = 0; i < calendario.size(); i++) {
            cout << "Jornada " << i + 1 << ":" << endl;
            for (int j = 0; j < calendario[i].size(); j++) {
                cout << "  Equipo " << calendario[i][j].first << " vs Equipo " << calendario[i][j].second << endl;
            }
        }*/

    }

    return 0;


}