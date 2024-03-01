HOME		= .
SRC			= $(HOME)/src
BIN			= $(HOME)/bin
SEED    = 24041915
DAT     = $(HOME)/dat
IMG     = $(HOME)/img
CPP_SOURCE	= $(wildcard $(SRC)/*.cpp)
BINARIES	= $(patsubst $(SRC)/%.cpp, $(BIN)/%, $(CPP_SOURCE))
CXXFLAGS = -std=c++11
GNUPLOT_SCRIPT = $(SRC)/graficar.gp
#######################################################################

all: $(BIN) $(BINARIES)
	@echo "[+] Todo está compilado correctamente"

$(BIN) $(DAT) $(IMG):
	@mkdir -p $@

$(BIN)/%: $(SRC)/%.cpp
	@echo "[+] Compilando $@..."
	@g++ $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo "[-] Limpiando archivos...."
	@rm -rf $(BIN) $(DAT) $(IMG)

test: $(BINARIES) | $(DAT) $(IMG)
	@echo "[+] Ejecutando pruebas..."
	@for binary in $^; do \
        binary_name=$$(basename $$binary); \
        if [ ! -e $(DAT)/$$binary_name.dat ]; then \
            echo "[+] Ejecutando $$binary..."; \
            if [ "$$binary_name" = "BubbleSort" ]; then \
                numbers=$$(seq 100 1000 30000); \
            elif [ "$$binary_name" = "QuickSort" ]; then \
                numbers=$$(seq 100 100000 3000000); \
            elif [ "$$binary_name" = "MergeSort" ]; then \
                numbers=$$(seq 100 100000 3000000); \
            else \
                echo "Algoritmo desconocido: $$binary_name"; \
                numbers=$$(seq 100 1000 30000); \
            fi; \
            ./$$binary $(DAT)/$$binary_name\.dat $(SEED) $$numbers > /dev/null; \
        else \
            echo "[+] Archivo .dat para $$binary_name ya existe. No se ejecutan pruebas."; \
        fi; \
    done
	@echo "[+] Generando gráficas..."
	@gnuplot $(GNUPLOT_SCRIPT) 2> /dev/null

help:
	@echo "Posibles opciones:"
	@echo "		${BOLD}clean${RESET}	\
	Borra todos los archivos creados por el makefile"
	@echo "		${BOLD}test${RESET}	\
	Genera los datos para cada función, y además crea las gráficas ajustando la eficiencia teórica con la empírica"
