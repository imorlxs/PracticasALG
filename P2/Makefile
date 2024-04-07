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
<<<<<<< HEAD
CASOS_MA = $$(seq 1000 5000 1000000)

=======
CASOS_MA = $$(seq 1000 10000 6000000)
>>>>>>> 91180245a873d147b1ec5aa83f27f09739cfc3db
#######################################################################

all: $(BIN) $(DAT) $(IMG) $(BINARIES)
	@echo "[+] Todo está compilado correctamente"

$(BIN)/%: $(SRC)/%.cpp
	@echo "[+] Compilando $@..., a partir de $<"
	@$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN) $(DAT) $(IMG):
	@mkdir $@

data:
	@chmod +x test.sh
	@./test.sh

graphic:
	@chmod +x graphic.gp
	@./graphic.gp

clean-all:
	@$(MAKE) clean
	@$(MAKE) clean-data
	@$(MAKE) clean-img

clean:
	@echo "[+] Borrando binarios..."
	rm -rf $(BIN)

clean-data:
	@echo "[+] Borrando datos..."	
	rm -rf $(DAT)

clean-img:
	@echo "[+] Borrando gráficas..."
	rm -rf $(IMG)

$(DAT)/%.dat: $(BIN)/% $(DAT)
	@echo $<
	@$< $@ $(SEED) $(CASOS_MA) > /dev/null
