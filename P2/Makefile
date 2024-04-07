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

#######################################################################

all: $(BIN) $(DAT) $(IMG) $(BINARIES)
	@echo "[+] Todo está compilado correctamente"

$(BIN)/%: $(SRC)/%.cpp
	@echo "[+] Compilando $@..., a partir de $<"
	@$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN):
	@mkdir $@

$(DAT):
	@mkdir $@

$(IMG):
	@mkdir $@

data:
	@chmod +x test.sh
	@./test.sh

clean:
	$(RM) -r $(BIN)

clean-data:
	@rm -rf $(DAT)

clean-img:
	@rm -rf $(IMG)
