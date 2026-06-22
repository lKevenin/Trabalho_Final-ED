// ===========================================================================
// Trabalho Final de Estrutura de Dados
// Sistema de Departamentos e Palavras-chave
//
// Funcionalidades:
//   - Importar registros de um arquivo texto.
//   - Pesquisar a qual departamento uma palavra-chave pertence.
//   - Pesquisar um departamento e ver seu código, nome e palavras-chave.
//   - Demonstrar os algoritmos Shell Sort, Heap Sort e Merge Sort.
//
// Compilação: veja o Makefile.
// ===========================================================================

#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Arquivo.h"
#include "Departamento.h"
#include "Ordenacao.h"
#include "Pesquisa.h"

// Caminho padrão do arquivo de dados (relativo à raiz do projeto).
const std::string ARQUIVO_PADRAO = "data/departamentos.txt";

// ---------------------------------------------------------------------------
// Funções de apoio à interface (entrada/saída no terminal)
// ---------------------------------------------------------------------------

// Imprime um departamento de forma organizada.
void imprimirDepartamento(const Departamento& dep) {
    std::cout << "  Codigo : " << dep.codigo << "\n";
    std::cout << "  Nome   : " << dep.nome << "\n";
    std::cout << "  Chaves : ";
    for (size_t i = 0; i < dep.palavras.size(); i++) {
        std::cout << dep.palavras[i];
        if (i + 1 < dep.palavras.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

// Lê uma linha inteira digitada pelo usuário (aceita nomes com espaços).
std::string lerTexto(const std::string& mensagem) {
    std::cout << mensagem;
    std::string entrada;
    std::getline(std::cin, entrada);
    return entrada;
}

// Mostra o menu e devolve a opção escolhida (como inteiro).
int lerOpcaoMenu() {
    std::cout << "\n==================== MENU ====================\n";
    std::cout << " 1 - Importar arquivo\n";
    std::cout << " 2 - Pesquisar palavra-chave\n";
    std::cout << " 3 - Pesquisar departamento\n";
    std::cout << " 4 - Executar Shell Sort (departamentos por nome)\n";
    std::cout << " 5 - Executar Heap Sort  (departamentos por codigo)\n";
    std::cout << " 6 - Executar Merge Sort (palavras-chave em ordem)\n";
    std::cout << " 0 - Sair\n";
    std::cout << "=============================================\n";
    std::cout << "Escolha uma opcao: ";

    int opcao;
    if (!(std::cin >> opcao)) {
        // Se o usuário digitou algo que não é número, limpamos o erro
        // e devolvemos uma opção inválida para o menu repetir.
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    // Descarta o restante da linha (o '\n') para o próximo getline funcionar.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcao;
}

// ---------------------------------------------------------------------------
// Ações do menu (cada uma trata uma opção)
// ---------------------------------------------------------------------------

void acaoImportar(std::vector<Departamento>& deps) {
    std::string caminho =
        lerTexto("Caminho do arquivo [Enter = " + ARQUIVO_PADRAO + "]: ");

    if (caminho.empty()) {
        caminho = ARQUIVO_PADRAO;
    }

    if (importarArquivo(caminho, deps)) {
        std::cout << ">> Arquivo importado com sucesso! "
                  << deps.size() << " departamento(s) carregado(s).\n";
    } else {
        std::cout << ">> ERRO: nao foi possivel abrir o arquivo \""
                  << caminho << "\".\n";
    }
}

void acaoPesquisarPalavra(const std::vector<Departamento>& deps) {
    if (deps.empty()) {
        std::cout << ">> Importe um arquivo primeiro (opcao 1).\n";
        return;
    }

    std::string palavra = lerTexto("Digite a palavra-chave: ");
    const Departamento* dep = pesquisarPalavraChave(deps, palavra);

    if (dep != nullptr) {
        std::cout << ">> A palavra \"" << palavra
                  << "\" pertence ao departamento:\n";
        imprimirDepartamento(*dep);
    } else {
        std::cout << ">> Palavra-chave nao encontrada.\n";
    }
}

void acaoPesquisarDepartamento(const std::vector<Departamento>& deps) {
    if (deps.empty()) {
        std::cout << ">> Importe um arquivo primeiro (opcao 1).\n";
        return;
    }

    std::string nome = lerTexto("Digite o nome do departamento: ");
    const Departamento* dep = pesquisarDepartamento(deps, nome);

    if (dep != nullptr) {
        std::cout << ">> Departamento encontrado:\n";
        imprimirDepartamento(*dep);
    } else {
        std::cout << ">> Departamento nao encontrado.\n";
    }
}

void acaoShellSort(std::vector<Departamento> deps) {
    // Recebemos uma CÓPIA (passagem por valor) de propósito: assim a ordenação
    // demonstrada aqui não altera a ordem original carregada na memória.
    if (deps.empty()) {
        std::cout << ">> Importe um arquivo primeiro (opcao 1).\n";
        return;
    }

    shellSort(deps);

    std::cout << ">> Departamentos ordenados por NOME (Shell Sort):\n";
    for (const Departamento& dep : deps) {
        std::cout << "  " << dep.codigo << " - " << dep.nome << "\n";
    }
}

void acaoHeapSort(std::vector<Departamento> deps) {
    if (deps.empty()) {
        std::cout << ">> Importe um arquivo primeiro (opcao 1).\n";
        return;
    }

    heapSort(deps);

    std::cout << ">> Departamentos ordenados por CODIGO (Heap Sort):\n";
    for (const Departamento& dep : deps) {
        std::cout << "  " << dep.codigo << " - " << dep.nome << "\n";
    }
}

void acaoMergeSort(const std::vector<Departamento>& deps) {
    if (deps.empty()) {
        std::cout << ">> Importe um arquivo primeiro (opcao 1).\n";
        return;
    }

    // Monta a lista com todas as palavras-chave e ordena alfabeticamente.
    std::vector<PalavraChave> palavras = montarListaDePalavras(deps);
    mergeSort(palavras);

    std::cout << ">> Palavras-chave em ordem alfabetica (Merge Sort):\n";
    for (const PalavraChave& pc : palavras) {
        std::cout << "  " << pc.palavra << "  (" << pc.departamento << ")\n";
    }
}

// ---------------------------------------------------------------------------
// Programa principal
// ---------------------------------------------------------------------------

int main() {
    std::vector<Departamento> departamentos;  // Dados em memória.

    std::cout << "=== Sistema de Departamentos e Palavras-chave ===\n";

    int opcao;
    do {
        opcao = lerOpcaoMenu();

        switch (opcao) {
            case 1:
                acaoImportar(departamentos);
                break;
            case 2:
                acaoPesquisarPalavra(departamentos);
                break;
            case 3:
                acaoPesquisarDepartamento(departamentos);
                break;
            case 4:
                acaoShellSort(departamentos);
                break;
            case 5:
                acaoHeapSort(departamentos);
                break;
            case 6:
                acaoMergeSort(departamentos);
                break;
            case 0:
                std::cout << "Encerrando o programa. Ate logo!\n";
                break;
            default:
                std::cout << ">> Opcao invalida. Tente novamente.\n";
                break;
        }
    } while (opcao != 0);

    return 0;
}
