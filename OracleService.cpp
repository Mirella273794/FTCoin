// Arquivo: OracleService.cpp (VERSÃO CORRIGIDA PARA C++11 e SIMULAÇÃO)
#include "OracleService.hpp"
#include <cstdlib> // para rand()
#include <ctime>   // para time()

OracleService::OracleService() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
}

double OracleService::generateRandomQuote() {
    // Gera um número aleatório para a cotação, por exemplo, entre 30000 e 70000
    return 30000.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (70000.0 - 30000.0)));
}

double OracleService::getOrCreateQuote(const std::string& date) {
    // Verifica se a cotação para esta data já existe no nosso mapa
    if (quoteHistory.find(date) == quoteHistory.end()) {
        // Se não existe, gera uma nova cotação, guarda no histórico e a retorna
        quoteHistory[date] = generateRandomQuote();
    }
    // Se já existe, apenas a retorna
    return quoteHistory[date];
}