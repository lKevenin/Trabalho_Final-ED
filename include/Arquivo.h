#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>
#include <vector>

#include "Departamento.h"

// ---------------------------------------------------------------------------
// Responsabilidade: leitura/importação dos dados a partir do arquivo texto.
// ---------------------------------------------------------------------------

// Lê o arquivo informado e devolve a lista de departamentos.
//
// Parâmetros:
//   caminho  -> caminho do arquivo .txt
//   destino  -> vetor que receberá os departamentos lidos (é limpo antes)
//
// Retorno:
//   true  -> arquivo lido com sucesso
//   false -> não foi possível abrir o arquivo
bool importarArquivo(const std::string& caminho,
                     std::vector<Departamento>& destino);

#endif  // ARQUIVO_H
