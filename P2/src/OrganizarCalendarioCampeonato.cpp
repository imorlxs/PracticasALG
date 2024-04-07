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
#include <fstream>
#include <chrono>
using namespace std;

/* CABECERAS DE FUNCIONES*/

void rotarEquipos(vector<int>& equipos);
vector<vector<pair<int,int>>> construirCalendario(int n);
void imprimirCalendario(const vector<vector<pair<int,int>>>& calendario);
bool esPotenciaDeDos(int n);

/*************************/


int main(int argc, char **argv)
{
    int n;  //nº de partidos
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    ofstream salida;
    
    // Realizamos comprobación sobre el argumento dado (nº de equipos a sortear)

    if (argc != 3)
    {
        cerr << "Error, se ha introducido un número de argumentos inválido" << endl;
        cerr << "Uso del programa: ./OrganizarCalendarioCampeonato <archivo de salida> <nº de equipos>" << endl;
        exit(-1);
    } 
    else if ( !esPotenciaDeDos( atoi(argv[2]) ) )
    {
        cerr << "Error, el número de participantes debe ser una potencia de dos" << endl;
        exit(-2);
    }
    else
    {
        n = atoi(argv[2]);

        salida.open(argv[1], std::ios::out | std::ios::app);
        if (!salida.is_open()){
            cerr << "[-] Error: No se pudo abrir fichero para escritura " << argv[2] << endl;
            return 0;
        }

        //cout << "[+] Se han introducido " << n << " equipos en la liga, se procede a realizar el sorteo..." << endl;

        t0 = std::chrono::high_resolution_clock::now();

        // Construcción e impresión por pantalla del calendario
        vector<vector<pair<int,int>>> calendario = construirCalendario(n);

        tf = std::chrono::high_resolution_clock::now();

        unsigned long t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
        salida << atoi(argv[2]) << " " << t_ejecucion << endl;

        salida.close();

        //cout << "Calendario del campeonato:\n\n";
        //imprimirCalendario(calendario);

    }

    return 0;

}


// Función para imprimir el calendario del torneo
void imprimirCalendario(const vector<vector<pair<int,int>>>& calendario){
    int dia = 1;
    for (const auto& partidos : calendario){
        cout << "Jornada " << dia << ": " << endl;
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


// Función que va a construir el calendario del torneo
// El calendario tendrá dos elementos (matriz) --> [día (jornada)][partidos]
vector<vector<pair<int,int>>> construirCalendario(int n){
    
    // Inicializamos el calendario
    vector<vector<pair<int,int>>> calendario(n-1, vector<pair<int,int>>(n/2));
    
    // Vector auxiliar que va a almacenar los equipos disponibles para sortear
    vector<int> disponibles(n);

    // Inicializamos los equipos disponibles
    for (int i = 0; i < n; i++)
        disponibles[i] = i+1;

    // Rellenamos el calendario con los partidos
    for (int dia = 0; dia < n-1; dia++){
        if (dia > 0) // No rotamos en el primer día
            rotarEquipos(disponibles);

        for (int partido = 0; partido < n/2; partido++){
            calendario[dia][partido] = make_pair(disponibles[partido], disponibles[n - partido - 1]);
        }       
    }

    return calendario;
}


// Comprobar si un número es potencia de 2
bool esPotenciaDeDos(int n){
    return n > 0 && (n & (n-1)) == 0;
}

