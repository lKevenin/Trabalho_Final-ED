#include "Arquivo.h"

#include <fstream>
#include <sstream>

// ---------------------------------------------------------------------------
// Importação do arquivo texto
// ---------------------------------------------------------------------------
//
// Cada linha do arquivo tem o formato:
//
//   <codigo> <nome> <palavra1> <palavra2> <palavra3> <palavra4> <palavra5>
//
// Exemplo:
//   001 FINANCEIRO INVESTIMENTO RENDA GASTOS DESPESAS LUCRO
//
// A estratégia é simples: ler o arquivo linha a linha e, para cada linha,
// usar um std::istringstream para "quebrar" o texto em palavras separadas
// por espaço. Isso evita ter de controlar índices de caracteres manualmente.
// ---------------------------------------------------------------------------

bool importarArquivo(const std::string& caminho,
                     std::vector<Departamento>& destino) {
    std::ifstream arquivo(caminho);

    // Se o arquivo não abriu (caminho errado, sem permissão, etc.), avisamos
    // o chamador retornando false.
    if (!arquivo.is_open()) {
        return false;
    }

    destino.clear();  // Garante que não vamos misturar com dados antigos.

    std::string linha;
    while (std::getline(arquivo, linha)) {
        // Ignora linhas em branco para evitar registros inválidos.
        if (linha.empty()) {
            continue;
        }

        std::istringstream fluxo(linha);
        Departamento dep;

        // Lê o código e o nome (os dois primeiros "tokens" da linha).
        fluxo >> dep.codigo >> dep.nome;

        // Lê as palavras-chave restantes, uma a uma, até o fim da linha.
        std::string palavra;
        while (fluxo >> palavra) {
            dep.palavras.push_back(palavra);
        }

        // Validação simples: só aceitamos a linha se ela tiver código, nome
        // e exatamente o número esperado de palavras-chave.
        if (!dep.codigo.empty() && !dep.nome.empty() &&
            static_cast<int>(dep.palavras.size()) == NUM_PALAVRAS) {
            destino.push_back(dep);
        }
    }

    return true;
}
