HOME			= .
SRC            	= $(HOME)/src
BIN            	= $(HOME)/bin

CXX     = g++
CXXFLAGS = -std=c++17

SOURCES = $(wildcard $(SRC)/*.cpp)

BINARIES = $(SOURCES:$(SRC)/%.cpp=$(BIN)/%)
CASOS_MA = $$(seq 1000 5000 1000000)

#######################################################################

all: $(BIN) $(DAT) $(IMG) $(BINARIES)
	@echo "[+] Todo está compilado correctamente"

$(BIN)/%: $(SRC)/%.cpp
	@echo "[+] Compilando $@..., a partir de $<"
	@$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN):
	@mkdir $@

clean:
	@echo "[+] Borrando binarios..."
	rm -rf $(BIN)
