#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <vector>

#include "Departamento.h"

// ---------------------------------------------------------------------------
// Responsabilidade: algoritmos de ordenação implementados MANUALMENTE.
// (Sem usar std::sort, conforme exigência do trabalho.)
//
// Cada algoritmo recebe uma tarefa coerente:
//   - Shell Sort  -> ordena os departamentos por NOME (ordem alfabética).
//   - Heap Sort   -> ordena os departamentos por CÓDIGO (ordem crescente).
//   - Merge Sort  -> ordena uma lista com TODAS as palavras-chave.
//
// Todas as funções ordenam "in place" (alteram o próprio vetor recebido).
// ---------------------------------------------------------------------------

// Monta uma lista única com todas as palavras-chave de todos os departamentos.
// Usada para demonstrar o Merge Sort sobre as palavras.
std::vector<PalavraChave> montarListaDePalavras(
    const std::vector<Departamento>& deps);

// Shell Sort: ordena departamentos por nome (A -> Z).
void shellSort(std::vector<Departamento>& deps);

// Heap Sort: ordena departamentos por código (001 -> 010).
void heapSort(std::vector<Departamento>& deps);

// Merge Sort: ordena as palavras-chave em ordem alfabética.
void mergeSort(std::vector<PalavraChave>& palavras);

#endif  // ORDENACAO_H
