#ifndef PESQUISA_H
#define PESQUISA_H

#include <string>
#include <vector>

#include "Departamento.h"

// ---------------------------------------------------------------------------
// Responsabilidade: pesquisas sobre os dados já carregados.
// ---------------------------------------------------------------------------

// Converte um texto para MAIÚSCULAS. Usado para que as pesquisas não
// diferenciem maiúsculas de minúsculas (ex.: "renda" encontra "RENDA").
std::string paraMaiusculas(const std::string& texto);

// Procura por uma palavra-chave dentro de todos os departamentos.
//
// Retorno:
//   ponteiro para o Departamento dono da palavra, ou
//   nullptr se a palavra não existir.
const Departamento* pesquisarPalavraChave(
    const std::vector<Departamento>& deps, const std::string& palavra);

// Procura por um departamento pelo NOME.
//
// Retorno:
//   ponteiro para o Departamento encontrado, ou
//   nullptr se nenhum departamento tiver aquele nome.
const Departamento* pesquisarDepartamento(
    const std::vector<Departamento>& deps, const std::string& nome);

#endif  // PESQUISA_H
