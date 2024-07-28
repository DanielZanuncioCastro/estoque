#include <string>
#include <iostream>
#include "Estoque.hpp"

void Estoque::add_mercadoria(const std::string& mercadoria, unsigned int qtd) {
  if(produtoqtd.find(mercadoria) == produtoqtd.end())
    {
      produtoqtd[mercadoria] = qtd;
    }
  else
  {
    produtoqtd[mercadoria] += qtd;    
  }  
}

void Estoque::sub_mercadoria(const std::string& mercadoria, unsigned int qtd) {
  auto it = produtoqtd.find(mercadoria);
  if (it != produtoqtd.end()) {
    int qtdantigo = it->second;
    if (qtdantigo < qtd) {
      std::cout << mercadoria << "insuficiente" << std::endl;      
    }
    else 
    {
      produtoqtd[mercadoria] -= qtd;
    }
}
  else
  {
    std::cout << mercadoria << "inexistente" << std::endl;
  }
}

unsigned int Estoque::get_qtd(const std::string& mercadoria) const {
  auto it = produtoqtd.find(mercadoria);
  if(it != produtoqtd.end())
    {
      return (it->second);      
    }
  return 0;
}

void Estoque::imprime_estoque() const {
  for (auto it = produtoqtd.begin(); it != produtoqtd.end(); it++) {
    const std::string& mercadoria = it->first;
    unsigned int qtd = it->second; 
    std::cout << mercadoria << ", " << qtd << std::endl;
  }
}

Estoque& Estoque::operator += (const Estoque& rhs) {
  for(auto it : rhs.produtoqtd)
    {
      add_mercadoria(it.first, it.second);
    }
  return *this;
}

Estoque& Estoque::operator -= (const Estoque& rhs) {
  for(auto it : rhs.produtoqtd)
    {
      sub_mercadoria(it.first, it.second);
    }
  return *this;
}

bool operator<(Estoque& lhs, Estoque& rhs) {
    // Itera sobre todos os produtos em lhs
    for (const auto& item : lhs.produtoqtd) {
        const std::string& mercadoria = item.first;
        int qtd1 = item.second;

        // Verifica se o produto está presente em rhs
        auto it = rhs.produtoqtd.find(mercadoria);
        if (it == rhs.produtoqtd.end()) {
            // Produto de lhs não está presente em rhs
            return false;
        } else {
            int qtd2 = it->second;
            if (qtd1 >= qtd2) {
                // Quantidade em lhs não é menor do que em rhs
                return false;
            }
        }
    }
    // Se todos os itens em lhs forem encontrados em rhs com quantidade menor, então lhs < rhs
    return true;
}

bool operator>(Estoque& lhs, Estoque& rhs) {
    // Itera sobre todos os produtos em rhs
    for (const auto& item : rhs.produtoqtd) {
        const std::string& mercadoria = item.first;
        int qtd2 = item.second;

        // Verifica se o produto está presente em lhs
        auto it = lhs.produtoqtd.find(mercadoria);
        if (it == lhs.produtoqtd.end()) {
            // Produto de rhs não está presente em lhs
            return false;
        } else {
            int qtd1 = it->second;
            if (qtd1 <= qtd2) {
                // Quantidade em lhs não é maior do que em rhs
                return false;
            }
        }
    }
    // Se todos os itens em rhs forem encontrados em lhs com quantidade maior, então lhs > rhs
    return true;
}