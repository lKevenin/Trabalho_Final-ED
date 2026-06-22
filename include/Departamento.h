#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Estruturas de dados centrais do projeto
// ---------------------------------------------------------------------------
//
// A escolha de usar "struct" (em vez de "class") aqui é proposital, estes são
// tipos de dados simples, cujo objetivo é apenas AGRUPAR informações
// relacionadas. Não há regras de negócio complexas escondidas dentro deles,
// então deixar os campos públicos torna o código mais direto e legível.
// ---------------------------------------------------------------------------

// Quantidade fixa de palavras-chave por departamento (exigência do enunciado).
const int NUM_PALAVRAS = 5;

// Representa uma única linha do arquivo de entrada.
struct Departamento {
    std::string codigo;                 // Ex.: "001"
    std::string nome;                   // Ex.: "FINANCEIRO"
    std::vector<std::string> palavras;  // Exatamente 5 palavras-chave
};

// Estrutura auxiliar usada para "achatar" todas as palavras-chave em uma única
// lista. Cada palavra-chave guarda também o nome do departamento ao qual
// pertence. Isso é útil para ordenar TODAS as palavras alfabeticamente
// (usada no Merge Sort) e para pesquisas rápidas.
struct PalavraChave {
    std::string palavra;        // A palavra-chave em si
    std::string departamento;   // Nome do departamento dono da palavra
    std::string codigo;         // Código do departamento dono da palavra
};

#endif  // DEPARTAMENTO_H
