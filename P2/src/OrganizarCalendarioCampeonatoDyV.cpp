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

vector<vector<pair<int,int>>> generarEmparejamientos(vector<int> equipos){

    vector<vector<pair<int,int>>> emparejamientosTotales;
    int n = equipos.size();

    // Caso base: sólo hay 2 equipos
    if (n == 2){
        vector<pair<int,int>> emparejamientos;
        emparejamientos.push_back(make_pair(equipos[0], equipos[1]));
        emparejamientosTotales.push_back(emparejamientos);
    }
    else {
        // Dividimos los equipos en dos grupos de igual tamaño, equiposA y equiposB
        vector<int> equiposA, equiposB;
        vector<vector<pair<int,int>>> emparejamientosA, emparejamientosB;

        for (int i = 0; i <= n/2; i++){
            equiposA.push_back(i);
        }
        for (int i = n/2; i <= n; i++){
            equiposB.push_back(i);
        }

        emparejamientosA = generarEmparejamientos(equiposA);
        emparejamientosB = generarEmparejamientos(equiposB);

        for (const auto& emparejamientoA : emparejamientosA){
            for (const auto& emparejamientoB : emparejamientosB){
                vector<pair<int,int>> emparejamientoTotal;

                // uso de std::merge(), con eficiencia O(n)
                merge(emparejamientoA.begin(), emparejamientoA.end(), emparejamientoB.begin(), emparejamientoB.end(),
                      back_inserter(emparejamientoTotal));
                
                // Agregamos el emparejamiento combinado a EmparejamientosTotales
                emparejamientosTotales.push_back(emparejamientoTotal);
            }
        }

    }

    return emparejamientosTotales;
}

// Comprobar si un número es potencia de 2 a partir de 2^1 = 2 en adelante
bool esPotenciaDeDosValida(int n){
    return n > 1 && (n & (n-1)) == 0;
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
    else if ( !esPotenciaDeDosValida( atoi(argv[1]) ) )
    {
        cerr << "Error, el número de participantes debe ser una potencia de dos" << endl;
        exit(-2);
    }
    else
    {
        n = atoi(argv[1]);
        vector<int> equipos(n);
        for (int i = 1; i <= n; i++){
            equipos[i] = i;
        }

        cout << "[+] Se han introducido " << n << " equipos en la liga, se procede a realizar el sorteo..." << endl;

        // Construcción e impresión por pantalla del calendario
        vector<vector<pair<int,int>>> emparejamientos = generarEmparejamientos(equipos);
        cout << "Calendario del torneo:" << endl;
        int dia = 1;
        for (const auto& partidos : emparejamientos){
            cout << "Jornada " << dia << ": " << endl;
            for (const auto& partido : partidos){
                cout << partido.first + 1 << " vs " << partido.second + 1 << endl;
            }
        }

    cout << "\n\n";
        
    }

    return 0;
}