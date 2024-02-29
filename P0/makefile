### makefile ########################################################
HOME		= .
SRC			= $(HOME)/src
BIN			= $(HOME)/bin

CPP_SOURCE	= $(wildcard $(SRC)/*.cpp)
BINARIES	= $(patsubst $(SRC)/%.cpp, $(BIN)/%, $(CPP_SOURCE))
FLAGS = -std=c+11
all: $(BIN) $(BINARIES)
	@echo "[+] let's fucking gooo, todo ha salido a pedir de Milhouse."

$(BIN):
	@mkdir -p $(BIN)

$(BIN)/%: $(SRC)/%.cpp
	@echo "compilando $@"
	@g++ $(FLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo "[-] limpiando..."
	@rm -rf $(BIN)
