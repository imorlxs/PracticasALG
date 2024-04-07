HOME        = .
SRC            = $(HOME)/src
BIN            = $(HOME)/bin
SEED    = 24041915
DAT     = $(HOME)/dat
IMG     = $(HOME)/img

CXX     = g++
CXXFLAGS = -std=c++11

SOURCES = $(wildcard $(SRC)/*.cpp)

BINARIES = $(SOURCES:$(SRC)/%.cpp=$(BIN)/%)
CASOS_MA = $$(seq 1000 100000 2000000)
#######################################################################

all: $(BIN) $(DAT) $(IMG) $(BINARIES)
	@echo "[+] Todo está compilado correctamente"

$(BIN)/%: $(SRC)/%.cpp
	@echo "[+] Compilando $@..., a partir de $<"
	@$(CXX) $(CXXFLAGS) -o $@ $<
	
#data: all $(DAT) $(DATAS)
#	@echo "${GREEN}[+] Datos generados correctamente${RESET}"

$(BIN) $(DAT):
	@mkdir -p $@

PHONY: clean
clean: clean-data
	@echo "[-] Limpiando archivos...."
	@rm -rf $(BIN)

<<<<<<< HEAD
$(IMG):
	@mkdir $@

data:
	@chmod +x test.sh
	@./test.sh

clean-all:
	@$(MAKE) clean
	@$(MAKE) clean-data
	@$(MAKE) clean-img

clean:
	@echo "[+] Borrando binarios..."
	rm -rf $(BIN)
=======
>>>>>>> babc671aa92b0f1b92f0a4c680f5ad18c1c10d9a

clean-data:
	@echo "[+] Borrando datos..."	
	rm -rf $(DAT)

<<<<<<< HEAD
clean-img:
	@echo "[+] Borrando gráficas..."
	rm -rf $(IMG)
=======
$(DAT)/%.dat: $(BIN)/% $(DAT)
	@echo $<
	@$< $@ $(SEED) $(CASOS_MA) > /dev/null
>>>>>>> babc671aa92b0f1b92f0a4c680f5ad18c1c10d9a
