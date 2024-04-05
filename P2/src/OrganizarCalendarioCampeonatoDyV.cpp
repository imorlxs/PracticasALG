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
        std::cout << "Jornada " << dia++ << ": " << endl;
        for (const auto& partido : partidos){
            std::cout << partido.first << " vs " << partido.second << endl;
        }
    }

    std::cout << "\n\n";
}

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


vector<vector<pair<int,int>>> crearsubCalendario(const vector<int>& equipos){
    int n = equipos.size();
    if (n==1){
        return {};
    } else if  (n == 2){
        
    }
    else {
        int mitad = n/2;
        vector<int> equiposIzq(equipos.begin(), equipos.begin() + mitad);
        vector<int> equiposDer(equipos.begin() + mitad, equipos.end());

        // Crear subcalendarios para cada mitad
        vector<vector<pair<int,int>>> subCalendarioIzq = crearsubCalendario(equiposIzq);
        vector<vector<pair<int,int>>> subCalendarioDer = crearsubCalendario(equiposDer);

        vector<vector<pair<int,int>>> calendario;
        for (int i = 0; i < min(subCalendarioIzq.size(), subCalendarioDer.size()); i++){
            for (int j = 0; j < subCalendarioIzq[i].size(); j++){
                calendario[i].push_back(make_pair(subCalendarioIzq[i][j].first, subCalendarioDer[i][j].second));
            }
        }

        for (int i = min(subCalendarioIzq.size(), subCalendarioDer.size()); i < subCalendarioIzq.size(); i++){
            calendario.push_back(subCalendarioIzq[i]);
        }

        for (int i = min(subCalendarioIzq.size(), subCalendarioDer.size()); i < subCalendarioDer.size(); i++){
            calendario.push_back(subCalendarioDer[i]);
        }

        return calendario;
    }

}

vector<vector<pair<int,int>>> construirCalendario(int n){
    vector<int> equipos(n);
    for (int i = 0; i < n; i++){
        equipos[i] = i+1;
    }

    vector<vector<pair<int,int>>> calendario = crearsubCalendario(equipos);

    return calendario;
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
        vector<int> equipos(n);
        for (int i = 1; i <= n; i++){
            equipos[i] = i + 1;
        }

        std::cout << "[+] Se han introducido " << n << " equipos en la liga, se procede a realizar el sorteo..." << endl;

        // Construcción e impresión por pantalla del calendario
        vector<vector<pair<int,int>>> calendario = construirCalendario(n);
        std::cout << "Calendario del torneo:" << endl;
        imprimirCalendario(calendario);
        
    }

    return 0;
}