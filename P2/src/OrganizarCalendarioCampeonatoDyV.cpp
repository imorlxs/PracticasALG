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

/* CABECERAS DE FUNCIONES*/

void generarCalendario(vector<vector<int>> &calendario, int primerEq, int ultimoEq);
void completarCalendario(vector<vector<int>> &calendario, int primerPartido, int ultimoPartido, int diaInf,
                         int diaFin, int inicioCampeonato);
void imprimirCalendario(const vector<vector<int>> &calendario);

/*************************/

int main(int argc, char **argv)
{

    long n; // nº de partidos
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    ofstream salida;

    // Realizamos comprobación sobre el argumento dado (nº de equipos a sortear)

    if (argc != 3)
    {
        cerr << "Error, se ha introducido un número de argumentos inválido" << endl;
        cerr << "Uso del programa: ./OrganizarCalendarioCampeonato <archivo de salida> <nº de equipos>" << endl;
        exit(-1);
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
        
        vector<vector<int>> calendario(n + 1, vector<int>(n, 0)); // Inicializar el calendario con ceros
        
        t0 = std::chrono::high_resolution_clock::now();

        // Generar el calendario
        generarCalendario(calendario, 1, n);

        tf = std::chrono::high_resolution_clock::now();

        unsigned long t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
        salida << atoi(argv[2]) << " " << t_ejecucion << endl;

        salida.close();

        //cout << "Calendario del campeonato:\n\n";
        //imprimirCalendario(calendario);

    }

    return 0;
}

void generarCalendario(vector<vector<int>> &calendario, int primero, int ultimo)
{
    int mitad;

    // Caso base --> solamente tenemos dos equipos en la liga para emparejar entre sí
    // Asignamos directamente los emparejamientos a fuerza bruta y se devuelve una matriz de 1x2
    if (ultimo - primero == 1)
    {
        calendario[primero][1] = ultimo;
        calendario[ultimo][1] = primero;
    }
    else
    {
        // Para aplicar técnicas de Divide y Vencerás, dividiremos el rango en dos cada vez, y generar el
        // calendario para cada mitad sucesivamente
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
