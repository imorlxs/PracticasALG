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
	@echo "[+] let's fucking gooo, todo ha salido a pedir de Milhouse."

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
	@echo "[-] Limpiando datos y gráficas preexistentes..."
	@rm -f $(DAT)/* $(IMG)/*
	
	@echo "[+] Ejecutando pruebas..."
	@for binary in $^; do \
        binary_name=$$(basename $$binary); \
        echo "[+] Ejecutando $$binary..."; \
        numbers=$$(seq 100 1000 30000); \
        ./$$binary $(DAT)/$$binary_name\.dat $(SEED) $$numbers > /dev/null; \
    done

	@echo "[+] Generando gráficas..."
	@gnuplot $(GNUPLOT_SCRIPT)

graphic: 
	@echo "[+] Generando gráficas..."
	@gnuplot $(GNUPLOT_SCRIPT)

