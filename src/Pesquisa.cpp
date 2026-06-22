#include "Pesquisa.h"

#include <cctype>

// ---------------------------------------------------------------------------
// Pesquisas
// ---------------------------------------------------------------------------

std::string paraMaiusculas(const std::string& texto) {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return resultado;
}

// Pesquisa de palavra-chave.
//
// Percorremos cada departamento e, dentro dele, cada uma das 5 palavras.
// Comparamos sempre em maiúsculas para a busca ser "case-insensitive".
//
// Como as palavras-chave não se repetem entre departamentos (garantia do
// enunciado), a primeira ocorrência encontrada já é a resposta correta.
const Departamento* pesquisarPalavraChave(
    const std::vector<Departamento>& deps, const std::string& palavra) {
    std::string alvo = paraMaiusculas(palavra);

    for (const Departamento& dep : deps) {
        for (const std::string& chave : dep.palavras) {
            if (paraMaiusculas(chave) == alvo) {
                return &dep;  // Devolve o endereço do departamento dono.
            }
        }
    }
    return nullptr;  // Não encontrou.
}

// Pesquisa de departamento pelo nome.
const Departamento* pesquisarDepartamento(
    const std::vector<Departamento>& deps, const std::string& nome) {
    std::string alvo = paraMaiusculas(nome);

    for (const Departamento& dep : deps) {
        if (paraMaiusculas(dep.nome) == alvo) {
            return &dep;
        }
    }
    return nullptr;
}
