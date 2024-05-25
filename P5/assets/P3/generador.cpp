/*
 * GENERADOR DE MAPAS ALEATORIOS
 * HECHO POR CHATGPT CON MI GRAN AYUDAI
 * NO FIARSE MUCHO DE ESTOS MAPAS
 */


#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <sys/stat.h> // Para mkdir en sistemas POSIX

const char WALL = 'M';
const char GOLD = 'O';
const char EMPTY = '-';
const int MIN_ROWS = 2; // Número mínimo de filas
const int MIN_COLS = 2; // Número mínimo de columnas
const int MAX_ROWS = 10; // Número máximo de filas
const int MAX_COLS = 15; // Número máximo de columnas

// Función para generar un mapa aleatorio
void generateMap(int mapNum, int rows, int cols, const std::string& folder) {
    std::vector<std::vector<char>> map(rows, std::vector<char>(cols, EMPTY));

    // Generar pocos muros (1-3)
    int numWalls = rand() % 3 + 1;
    for (int i = 0; i < numWalls; ++i) {
        int x = rand() % rows;
        int y = rand() % cols;
        map[x][y] = WALL;
    }

    // Añadir bolsas de oro aleatoriamente
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == EMPTY && rand() % 3 == 0) { // Añadir bolsa de oro con probabilidad de 1/3
                map[i][j] = GOLD;
            }
        }
    }

    // Asegurar que las casillas inferior izquierda y superior derecha estén vacías
    map[0][cols - 1] = EMPTY; // Superior derecha
    map[rows - 1][0] = EMPTY; // Inferior izquierda

    // Guardar el mapa en un archivo de texto
    std::ostringstream filename;
    filename << folder << "/map" << mapNum << ".txt";
    std::ofstream file(filename.str());
    if (file.is_open()) {
        file << rows << " " << cols << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file << map[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Mapa guardado: " << filename.str() << std::endl;
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << filename.str() << std::endl;
    }
}

// Función para crear la carpeta si no existe
bool createDirectory(const std::string& path) {
    #ifdef _WIN32
        return mkdir(path.c_str()) == 0;
    #else
        return mkdir(path.c_str(), 0777) == 0;
    #endif
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <numero_mapas> <carpeta>" << std::endl;
        return 1;
    }

    int numMaps = std::stoi(argv[1]);
    std::string folder = argv[2];

    srand(time(0)); // Semilla para la generación aleatoria

    if (!createDirectory(folder)) {
        std::cerr << "Error: No se pudo crear la carpeta " << folder << std::endl;
        return 1;
    }

    for (int i = 1; i <= numMaps; ++i) {
        // Generar un número aleatorio de filas y columnas (mínimo 2x2)
        int rows = rand() % (MAX_ROWS - MIN_ROWS + 1) + MIN_ROWS;
        int cols = rand() % (MAX_COLS - MIN_COLS + 1) + MIN_COLS;
        generateMap(i, rows, cols, folder);
    }

    std::cout << "Se han generado " << numMaps << " mapas en la carpeta '" << folder << "'" << std::endl;

    return 0;
}

