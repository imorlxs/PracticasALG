HOME        = .
SRC            = $(HOME)/src
BIN            = $(HOME)/bin
SEED    = 24041915
DAT     = $(HOME)/dat
IMG     = $(HOME)/img
SCRIPTS    = $(HOME)/scripts
CXX     = g++
CXXFLAGS = -std=c++11

# Aquí definimos SOURCES para incluir todos los archivos .cpp en el directorio SRC
SOURCES = $(wildcard $(SRC)/*.cpp)

# Con esta definición, ahora BINARIES generará los nombres de los ejecutables
BINARIES = $(SOURCES:$(SRC)/%.cpp=$(BIN)/%)

#######################################################################

all: $(BIN) $(BINARIES)
	@echo "[+] Todo está compilado correctamente"

$(BIN)/%: $(SRC)/%.cpp
	@echo "[+] Compilando $@..., primer requisito $<"
	@$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN) $(DAT) $(IMG):
	@mkdir -p $@

data:
	@chmod +x $(SCRIPTS)/test.sh
	@./$(SCRIPTS)/test.sh

clean:
	$(RM) -r $(BIN)

clean-data:
	@rm -rf $(DAT)

clean-img:
	@rm -rf $(IMG)
