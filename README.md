# Sistema de Departamentos e Palavras-chave

Trabalho final da disciplina de **Estrutura de Dados** (C++).

O programa lê um arquivo texto com departamentos e suas palavras-chave, permite
pesquisar tanto por palavra-chave quanto por departamento, e demonstra três
algoritmos de ordenação clássicos implementados **manualmente** (sem
`std::sort`): **Shell Sort**, **Heap Sort** e **Merge Sort**.

---

## 1. Como compilar e executar

### Opção A — usando o Makefile (Linux / Git Bash / MinGW)

```bash
make        # compila e gera o executável "departamentos"
make run    # compila e já executa
make clean  # remove o executável
```

### Opção B — chamando o g++ diretamente

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o departamentos
./departamentos
```

### Opção C — Visual Studio

1. Crie um projeto de **Console (C++)**.
2. Adicione os arquivos das pastas `src/` e `include/` ao projeto.
3. Em *Propriedades > C/C++ > Geral > Diretórios de Inclusão Adicionais*,
   adicione a pasta `include`.
4. Compile e execute (Ctrl + F5).

> O programa espera encontrar o arquivo em `data/departamentos.txt`. Rode-o a
> partir da raiz do projeto, ou informe o caminho completo na opção 1 do menu.

---

## 2. Formato do arquivo de entrada

Cada linha representa um departamento, no formato:

```
<codigo> <nome> <palavra1> <palavra2> <palavra3> <palavra4> <palavra5>
```

Exemplo (`data/departamentos.txt`):

```
001 FINANCEIRO INVESTIMENTO RENDA GASTOS DESPESAS LUCRO
002 CONTABILIDADE BALANÇO BALANCETE RAZÃO ENTRADA SAÍDA
```

O arquivo `data/departamentos.txt` foi gerado a partir do documento oficial
fornecido pelo professor (`ARQUIVO PARA IMPORTAÇÃO NO PROGRAMA.docx`),
convertido para texto puro (`.txt`) e salvo em **UTF-8**.

> **Sobre acentos:** o arquivo está em UTF-8 e o programa lida com acentos
> normalmente (as buscas por `SALÁRIO`, `VIGILÂNCIA` etc. funcionam). As
> palavras só podem aparecer "tortas" na tela dependendo da configuração de
> codificação do terminal, isso é apenas exibição, não afeta a lógica.

---

## 3. Estrutura do projeto

```
Trabalho_Final-ED/
├── data/
│   └── departamentos.txt      # Arquivo de dados de exemplo
├── include/                   # Cabeçalhos (.h) — declarações
│   ├── Departamento.h         # Estruturas de dados (struct)
│   ├── Arquivo.h              # Importação do arquivo
│   ├── Pesquisa.h             # Pesquisas
│   └── Ordenacao.h            # Algoritmos de ordenação
├── src/                       # Implementações (.cpp)
│   ├── Arquivo.cpp
│   ├── Pesquisa.cpp
│   ├── Ordenacao.cpp
│   └── main.cpp               # Menu principal
├── Makefile
└── README.md
```

O código foi **separado por responsabilidade** (importação, pesquisa,
ordenação, interface). Isso deixa cada arquivo curto, fácil de ler e de
explicar — exatamente o que se espera de um trabalho bem organizado.

---

## 4. Principais estruturas de dados utilizadas

Definidas em `include/Departamento.h`:

### `struct Departamento`
Representa uma linha do arquivo:

```cpp
struct Departamento {
    std::string codigo;                 // "001"
    std::string nome;                   // "FINANCEIRO"
    std::vector<std::string> palavras;  // 5 palavras-chave
};
```

Usamos `std::vector<std::string>` para as palavras porque o vetor já cuida do
tamanho e do gerenciamento de memória automaticamente — bem mais seguro que um
array em C.

### `struct PalavraChave`
Estrutura auxiliar que "achata" todas as palavras numa lista única, guardando
de qual departamento cada palavra veio:

```cpp
struct PalavraChave {
    std::string palavra;        // "RENDA"
    std::string departamento;   // "FINANCEIRO"
    std::string codigo;         // "001"
};
```

Ela é usada para demonstrar o **Merge Sort** ordenando *todas* as palavras-chave
em ordem alfabética.

### Coleção principal
Todos os departamentos ficam em um `std::vector<Departamento>`, mantido na
`main()` e passado às funções por referência.

---

## 5. Funcionalidades (menu)

```
1 - Importar arquivo
2 - Pesquisar palavra-chave
3 - Pesquisar departamento
4 - Executar Shell Sort  (departamentos por nome)
5 - Executar Heap Sort   (departamentos por codigo)
6 - Executar Merge Sort  (palavras-chave em ordem alfabética)
0 - Sair
```

- **Pesquisas** são *case-insensitive* (não diferenciam maiúsculas/minúsculas):
  internamente tudo é comparado em MAIÚSCULAS.
- As ordenações das opções 4 e 5 trabalham sobre uma **cópia** dos dados, então
  a ordem original carregada na memória **não é alterada**, você pode rodar
  qualquer ordenação quantas vezes quiser sem "estragar" os dados.

---

## 6. Explicação detalhada dos algoritmos de ordenação

Todos estão em `src/Ordenacao.cpp`.

### 6.1 Shell Sort — ordena departamentos por **nome**

O Shell Sort é uma versão melhorada do **Insertion Sort**. No Insertion Sort
comum, só comparamos elementos vizinhos, o que faz um elemento muito fora do
lugar precisar de muitas trocas até chegar ao destino.

O Shell Sort resolve isso comparando elementos separados por uma distância
chamada **gap** (intervalo). Ele começa com um gap grande (metade do tamanho do
vetor) e vai reduzindo pela metade até o gap valer 1.

- Com gaps grandes, elementos distantes se aproximam rapidamente da posição
  certa, com poucas trocas.
- Quando o gap chega a 1, o algoritmo vira um Insertion Sort normal, mas agora
  o vetor já está "quase ordenado", então essa última passada é muito rápida.

**Complexidade:** depende da sequência de gaps; na prática fica em torno de
O(n^1.3) a O(n²) no pior caso. Não usa memória extra (ordenação "in place").

### 6.2 Heap Sort — ordena departamentos por **código**

O Heap Sort usa uma estrutura lógica chamada **heap máximo** (*max-heap*): uma
árvore binária em que todo nó-pai é **maior ou igual** aos seus filhos. O truque
é que essa árvore cabe dentro do próprio vetor:

- filho da esquerda do índice `i` → `2*i + 1`
- filho da direita do índice `i`  → `2*i + 2`

Funcionamento em duas fases:

1. **Construção do heap:** reorganizamos o vetor para que ele satisfaça a regra
   do max-heap. Assim o **maior elemento fica na raiz** (posição 0).
2. **Extração:** trocamos a raiz (o maior) com o último elemento, "encolhemos" o
   heap em uma posição e chamamos `heapify` para consertar a raiz. Repetindo
   isso, os maiores elementos vão sendo empurrados para o fim — e o vetor termina
   ordenado.

A função `heapify` é o coração do algoritmo: ela compara um nó com seus filhos,
troca com o maior filho se necessário e desce recursivamente para manter a
propriedade do heap.

**Complexidade:** O(n log n) garantido (melhor, médio e pior caso). Ordena
"in place", sem vetor auxiliar.

### 6.3 Merge Sort — ordena todas as **palavras-chave**

O Merge Sort segue a estratégia **dividir para conquistar**:

1. **Dividir:** corta o vetor ao meio repetidamente, até sobrarem pedaços de 1
   elemento (que, por definição, já estão ordenados).
2. **Conquistar / Intercalar (*merge*):** junta os pedaços de volta dois a dois,
   sempre comparando o primeiro elemento de cada metade e copiando o menor
   primeiro. O resultado de cada junção já sai ordenado.

A função `intercalar` cria duas cópias temporárias (metade esquerda e direita) e
as percorre em paralelo, reconstruindo o trecho original já ordenado.

**Complexidade:** O(n log n) garantido em todos os casos. É **estável** (mantém a
ordem relativa de elementos iguais), mas usa memória extra para as cópias
temporárias durante a intercalação.

### Resumo comparativo

| Algoritmo  | Complexidade média | Memória extra | Estável? | Aqui ordena            |
|------------|--------------------|---------------|----------|------------------------|
| Shell Sort | ~O(n^1.3)          | Não (in place)| Não      | Departamentos por nome |
| Heap Sort  | O(n log n)         | Não (in place)| Não      | Departamentos por código|
| Merge Sort | O(n log n)         | Sim           | Sim      | Palavras-chave (alfabética) |

---

## 7. Decisões de arquitetura (melhorias aplicadas)

Mantendo o escopo simples do trabalho, foram aplicadas algumas boas práticas:

1. **Separação em módulos** (`Arquivo`, `Pesquisa`, `Ordenacao`, `main`) em vez
   de um único arquivo gigante. Cada parte tem uma responsabilidade clara.
2. **Cabeçalhos (.h) com declarações + implementações (.cpp)**, facilita compilar e localizar código.
3. **Pesquisas retornando ponteiro (`const Departamento*`)**: devolver `nullptr`
   é uma forma simples e clara de indicar "não encontrado", sem exceções.
4. **Ordenações sobre cópias dos dados**: preservam a ordem original, permitindo
   demonstrar e comparar os algoritmos livremente.
5. **Validação na importação**: linhas vazias ou incompletas são ignoradas,
   evitando registros quebrados.

Essas escolhas melhoram a organização **sem** introduzir bibliotecas externas
nem recursos avançados desnecessários.
