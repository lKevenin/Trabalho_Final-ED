#include "Ordenacao.h"

#include <string>

// ===========================================================================
// Funções auxiliares
// ===========================================================================

// Constrói a lista "achatada" de palavras-chave a partir dos departamentos.
std::vector<PalavraChave> montarListaDePalavras(
    const std::vector<Departamento>& deps) {
    std::vector<PalavraChave> lista;
    for (const Departamento& dep : deps) {
        for (const std::string& chave : dep.palavras) {
            PalavraChave pc;
            pc.palavra = chave;
            pc.departamento = dep.nome;
            pc.codigo = dep.codigo;
            lista.push_back(pc);
        }
    }
    return lista;
}

// ===========================================================================
// 1) SHELL SORT  ->  ordena departamentos por NOME
// ===========================================================================
//
// Ideia geral:
//   O Shell Sort é uma melhoria do Insertion Sort. Em vez de comparar apenas
//   elementos vizinhos, ele compara elementos separados por uma distância
//   chamada "gap" (intervalo). A cada passada o gap diminui, até chegar a 1
//   (quando vira um Insertion Sort comum, porém com o vetor quase ordenado,
//   o que o torna muito rápido).
//
//   Começar com gaps grandes permite mover elementos muito distantes do seu
//   lugar para perto da posição correta com poucas trocas.
// ===========================================================================
void shellSort(std::vector<Departamento>& deps) {
    int n = static_cast<int>(deps.size());

    // Começamos com um gap grande (metade do tamanho) e o reduzimos pela
    // metade a cada iteração externa.
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Faz uma "inserção" considerando elementos distantes 'gap' posições.
        for (int i = gap; i < n; i++) {
            Departamento atual = deps[i];  // Elemento que vamos posicionar.
            int j = i;

            // Empurra para a direita os elementos maiores que 'atual',
            // andando de 'gap' em 'gap', até achar o lugar certo.
            while (j >= gap && deps[j - gap].nome > atual.nome) {
                deps[j] = deps[j - gap];
                j -= gap;
            }
            deps[j] = atual;
        }
    }
}

// ===========================================================================
// 2) HEAP SORT  ->  ordena departamentos por CÓDIGO
// ===========================================================================
//
// Ideia geral:
//   O Heap Sort usa uma estrutura lógica chamada "heap máximo" (max-heap),
//   onde todo pai é maior ou igual aos filhos. O vetor é tratado como uma
//   árvore binária: para um nó na posição i, os filhos estão em 2i+1 e 2i+2.
//
//   Passos:
//     1. Transformamos o vetor em um max-heap (o maior elemento vai para a
//        raiz, posição 0).
//     2. Trocamos a raiz (maior) com o último elemento e "encolhemos" o heap.
//     3. Reorganizamos (heapify) e repetimos. Ao final, o vetor fica ordenado.
// ===========================================================================

// Reorganiza o sub-heap cuja raiz está em 'raiz', considerando que o heap tem
// tamanho 'tamanho'. Compara pelo campo "codigo".
static void heapify(std::vector<Departamento>& deps, int tamanho, int raiz) {
    int maior = raiz;          // Assume que a raiz é a maior.
    int esquerda = 2 * raiz + 1;
    int direita = 2 * raiz + 2;

    // Se o filho da esquerda existe e é maior que a raiz atual...
    if (esquerda < tamanho && deps[esquerda].codigo > deps[maior].codigo) {
        maior = esquerda;
    }
    // Se o filho da direita existe e é maior que o maior até agora...
    if (direita < tamanho && deps[direita].codigo > deps[maior].codigo) {
        maior = direita;
    }

    // Se o maior não for a própria raiz, trocamos e continuamos descendo.
    if (maior != raiz) {
        std::swap(deps[raiz], deps[maior]);
        heapify(deps, tamanho, maior);
    }
}

void heapSort(std::vector<Departamento>& deps) {
    int n = static_cast<int>(deps.size());

    // Passo 1: constrói o max-heap.
    // Começamos do último nó que tem filhos (n/2 - 1) e subimos até a raiz.
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(deps, n, i);
    }

    // Passo 2: extrai os elementos um a um do heap.
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual (maior valor) para o final do vetor.
        std::swap(deps[0], deps[i]);

        // Reorganiza o heap reduzido (agora com tamanho 'i').
        heapify(deps, i, 0);
    }
}

// ===========================================================================
// 3) MERGE SORT  ->  ordena a lista de palavras-chave (ordem alfabética)
// ===========================================================================
//
// Ideia geral:
//   O Merge Sort segue a estratégia "dividir para conquistar":
//     1. Divide o vetor ao meio repetidamente, até sobrarem pedaços de
//        tamanho 1 (que já estão "ordenados").
//     2. Junta (merge) os pedaços de volta, sempre intercalando de forma
//        ordenada, até reconstruir o vetor inteiro já ordenado.
//
//   É um algoritmo estável e com desempenho garantido O(n log n).
// ===========================================================================

// Junta (intercala) duas metades já ordenadas:
//   [inicio .. meio]  e  [meio+1 .. fim]
static void intercalar(std::vector<PalavraChave>& v, int inicio, int meio,
                       int fim) {
    // Cria cópias temporárias das duas metades.
    std::vector<PalavraChave> esquerda(v.begin() + inicio,
                                       v.begin() + meio + 1);
    std::vector<PalavraChave> direita(v.begin() + meio + 1,
                                      v.begin() + fim + 1);

    int i = 0;       // índice na metade esquerda
    int j = 0;       // índice na metade direita
    int k = inicio;  // índice de escrita no vetor original

    // Enquanto houver elementos nas duas metades, copia sempre o menor.
    while (i < static_cast<int>(esquerda.size()) &&
           j < static_cast<int>(direita.size())) {
        if (esquerda[i].palavra <= direita[j].palavra) {
            v[k++] = esquerda[i++];
        } else {
            v[k++] = direita[j++];
        }
    }

    // Copia o que sobrou (apenas uma das metades ainda terá elementos).
    while (i < static_cast<int>(esquerda.size())) {
        v[k++] = esquerda[i++];
    }
    while (j < static_cast<int>(direita.size())) {
        v[k++] = direita[j++];
    }
}

// Função recursiva que divide o vetor e depois manda intercalar.
static void mergeSortRec(std::vector<PalavraChave>& v, int inicio, int fim) {
    if (inicio >= fim) {
        return;  // Pedaço de 0 ou 1 elemento já está ordenado.
    }

    int meio = inicio + (fim - inicio) / 2;

    mergeSortRec(v, inicio, meio);       // Ordena a metade esquerda.
    mergeSortRec(v, meio + 1, fim);      // Ordena a metade direita.
    intercalar(v, inicio, meio, fim);    // Junta as duas metades ordenadas.
}

void mergeSort(std::vector<PalavraChave>& palavras) {
    if (palavras.empty()) {
        return;
    }
    mergeSortRec(palavras, 0, static_cast<int>(palavras.size()) - 1);
}
