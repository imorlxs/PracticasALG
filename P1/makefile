HOME		= .
SRC			= $(HOME)/src
BIN			= $(HOME)/bin
SEED    = 24041915
DAT     = $(HOME)/dat
IMG     = $(HOME)/img
CPP_SOURCE	= $(wildcard $(SRC)/*.cpp)
BINARIES	= $(patsubst $(SRC)/%.cpp, $(BIN)/%, $(CPP_SOURCE))
DATAS = $(patsubst $(SRC)/%.cpp, $(DAT)/%.dat, $(CPP_SOURCE))
CXXFLAGS = -std=c++11
GNUPLOT_SCRIPT = $(SRC)/graficar.gp
CXX = g++
NUMBERS_N2 = $$(seq 100 1000 30000)
NUMBERS_NLOGN = $$(seq 1000 10000 900000)
N2ALGS = bin/BubbleSort bin/InsertionSort bin/SelectionSort
#######################################################################

all: $(BIN) $(BINARIES)
	@echo "[+] Todo está compilado correctamente"

data: $(DAT) $(DATAS)
	@echo "${GREEN}[+] Datos generados correctamente${RESET}"

graphic: $(IMG) clean-fit-log
	@echo "[+] Generando gráficas..."
	@gnuplot $(GNUPLOT_SCRIPT) 2> /dev/null

$(BIN) $(DAT) $(IMG):
	@mkdir -p $@

$(BIN)/%: $(SRC)/%.cpp
	@echo "[+] Compilando $@..., primer requisito $<"
	@$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean: clean-fit-log clean-img clean-data
	@echo "[-] Limpiando archivos...."
	@rm -rf $(BIN)

clean-fit-log:
	@rm -f $(HOME)/fit.log

clean-data:
	@rm -rf $(DAT)

clean-img:
	@rm -rf $(IMG)


$(DAT)/%.dat: $(BIN)/% $(DAT)
	@echo $<
	@$< $@ $(SEED) $(if $(findstring $<, $(N2ALGS)), $(NUMBERS_N2)[,$(NUMBERS_NLOGN)]) > /dev/null
	
	
