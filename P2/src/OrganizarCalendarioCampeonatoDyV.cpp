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
#include <chrono>
#include <vector>
#include <fstream>
using namespace std;

// Cabeceras de funciones //

void generarCalendario(vector<vector<int>> &calendario, int primerEq, int ultimoEq);
void completarCalendario(vector<vector<int>> &calendario, int primerPartido, int ultimoPartido, int diaInf,
                         int diaFin, int inicioCampeonato);
void imprimirCalendario(const vector<vector<int>> &calendario);
bool esPotenciaDeDos(int n);

/*************************/


int main(int argc, char **argv)
{

    long n; // nº de equipos
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir tiempos de ejecución
    ofstream salida;  // Archivos de salida

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

        // Abrimos el archivo de salida
        salida.open(argv[1], std::ios::out | std::ios::app);
        if (!salida.is_open()){
            cerr << "[-] Error: No se pudo abrir fichero para escritura " << argv[2] << endl;
            return 0;
        }
        
        vector<vector<int>> calendario(n + 1, vector<int>(n, 0)); // Inicializar el calendario con ceros
        
        t0 = std::chrono::high_resolution_clock::now(); // Comenzamos a contar el tiempo

        // Generar el calendario
        generarCalendario(calendario, 1, n);

        tf = std::chrono::high_resolution_clock::now(); // Terminamos de medir el tiempo

        unsigned long t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
        salida << atoi(argv[2]) << " " << t_ejecucion << endl;

        salida.close();

    }

    return 0;
}

// Función para generar el calendario usando la técnica de Divide y Vencerás
void generarCalendario(vector<vector<int>> &calendario, int primero, int ultimo)
{
    int mitad;

    // Caso base --> solamente tenemos dos equipos en la liga para emparejar entre sí
    if (ultimo - primero == 1)
    {
        calendario[primero][1] = ultimo;
        calendario[ultimo][1] = primero;
    }
    else
    {
        // Dividir el rango en dos cada vez y generar el calendario para cada mitad sucesivamente
        mitad = (primero + ultimo) / 2;

        generarCalendario(calendario, primero, mitad);
        generarCalendario(calendario, mitad + 1, ultimo);

        // Completamos el calendario para cada mitad
        completarCalendario(calendario, primero, mitad, mitad - primero + 1, ultimo - primero, mitad + 1);
        completarCalendario(calendario, mitad + 1, ultimo, mitad - primero + 1, ultimo - primero, primero);
    }
}

void completarCalendario(vector<vector<int>>& calendario, int primerEq, int ultimoEq, int diaIni,
                         int diaFin, int inicio)
{
    // Asignamos los enfrentamientos consecutivos del primer participante
    for (int dia = diaIni; dia <= diaFin; dia++)
    {
        calendario[primerEq][dia] = inicio + dia - diaIni;
    }

    // Asignar enfrentamientos al resto de los participantes
    for (int i = primerEq + 1; i <= ultimoEq; i++)
    {
        calendario[i][diaIni] = calendario[i - 1][diaFin];
        for (int j = diaIni + 1; j <= diaFin; j++)
        {
            calendario[i][j] = calendario[i - 1][j - 1];
        }
    }
}


// Función para imprimir el calendario del torneo
void imprimirCalendario(const vector<vector<int>> &calendario)
{
    int n = calendario.size() - 1;

    for (int i = 1; i <= n; i++){
        cout << "Encuentros del equipo " << i << ":" << endl;
        for (int j = 1; j < n; j++){
            cout << "Día " << j << ": " << i << " vs " << calendario[i][j] << endl;
        }
        cout << endl;
    }

    cout << endl;

}

// Comprobar si un número es potencia de 2
bool esPotenciaDeDos(int n){
    return n > 0 && (n & (n-1)) == 0;
}

