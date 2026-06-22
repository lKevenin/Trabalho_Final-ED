# Makefile simples para compilar o projeto com g++.
#
# Uso:
#   make          -> compila e gera o executável "departamentos"
#   make run      -> compila e executa
#   make clean    -> remove os arquivos gerados

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC      = src/main.cpp src/Arquivo.cpp src/Pesquisa.cpp src/Ordenacao.cpp
ALVO     = departamentos

all: $(ALVO)

$(ALVO): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(ALVO)

run: all
	./$(ALVO)

clean:
	rm -f $(ALVO)

.PHONY: all run clean
