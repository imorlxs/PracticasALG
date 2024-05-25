# Variables
CXX = g++
CXXFLAGS = -g
SRC_DIR = src
BIN_DIR = bin

# Encuentra todos los archivos .cpp en la carpeta src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Sustituye el directorio src/ y la extensión .cpp por bin/ y nada para los binarios
PROGRAMS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)

# Regla predeterminada
all: $(PROGRAMS)
	@echo "[+] Todo compilado correctamente"

# Regla para crear la carpeta bin si no existe
$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	@echo "[+] Compilando $<"
	@$(CXX) $(CXXFLAGS) $< -o $@

# Regla para limpiar los binarios y la carpeta
clean:
	@echo "[+] Limpiando ejecutables..."
	rm -rf $(BIN_DIR)

# Impide que make interprete "clean" como un archivo a crear.
.PHONY: all clean
