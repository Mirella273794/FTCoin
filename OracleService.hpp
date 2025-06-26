// Arquivo: OracleService.hpp (VERSÃO CORRIGIDA PARA C++11 e SIMULAÇÃO)
#ifndef ORACLE_SERVICE_H
#define ORACLE_SERVICE_H

#include <string>
#include <map> // Usaremos um mapa para simular o banco de dados

class OracleService {
private:
    // Um mapa para guardar as cotações: a chave é a data (string), o valor é a cotação (double)
    std::map<std::string, double> quoteHistory;

    // Gera uma cotação aleatória para simular o mercado
    double generateRandomQuote();

public:
    OracleService(); // Construtor não precisa mais de um DAO

    // Retorna a cotação para uma data. Se não existir, cria uma, guarda e retorna.
    double getOrCreateQuote(const std::string& date);
};

#endif