/*****************************************************
 * Álvaro Maldonado Medina
 * Grupo: 2ºD, subgrupo de prácticas D1
 * @file OrganizarCalendarioCampeonato.cpp
 * ¿Usa Divide y Vencerás? --> NO
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
        cout << "Día " << dia++ << ": " << endl;
        for (const auto& partido : partidos){
            cout << "Partido " << partido.first << " vs " << partido.second << endl;
        }
    }

    cout << endl;
}


// Función que va a construir el calendario del torneo
vector<vector<pair<int,int>>> construirCalendario(int n){

    // Dado que se trata de un formato liguilla, hay n-1 oponentes disponibles puesto que no
    // pondremos a jugar a un equipo conta sí mismo, habiendo n/2 partidos a jugar.
    
    // Inicializamos el calendario
    vector<vector<pair<int,int>>> calendario(n-1, vector<pair<int,int>>(n/2));

    // Rellenamos el calendario con los partidos
    int equipoA, equipoB;
    for (int dia = 0; dia < n-1; dia++){
        equipoA = 1;
        equipoB = n - dia;
        for (int partido = 0; partido < n/2; partido++){
            calendario[dia][partido] = make_pair(equipoA++,equipoB++);
            if (equipoB > n-1)
                equipoB = 2;
        }
    }

    return calendario;
}

// Comprobar si un número es potencia de 2
bool esPotenciaDeDos(int n){
    return n > 0 && (n & (n-1)) == 0;
}


int main(int argc, char **argv)
{
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

        // Construcción del calendario
        vector<vector<pair<int,int>>> calendario = construirCalendario(n);
        cout << "Calendario del torneo:" << endl;
        imprimirCalendario(calendario);

    }

    return 0;

}
