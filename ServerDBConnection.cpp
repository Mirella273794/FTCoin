/* ********************************************************************************
 * FT_Coin - ServerDBConnection.cpp (Versão com dados de acesso do projeto)
 ******************************************************************************** */

#include "ServerDBConnection.h"
#include <iostream>

// Implementação do Construtor com os dados de acesso fornecidos
ServerDBConnection::ServerDBConnection() {
    // Dados de acesso fornecidos para o grupo PooI_25_B05
    const std::string url = "tcp://143.106.243.64:3306"; // IP fornecido, usando a porta padrão 3306
    const std::string user = "PooI_25_B05";             // Nome do grupo como usuário
    const std::string password = "blwltAO53Y";         // Senha fornecida
    
    // O nome do banco de dados (schema) é geralmente o mesmo que o nome do grupo/usuário.
    // Se for diferente, ajuste aqui.
    const std::string schema = "PooI_25_B05";

    try {
        driver = sql::mysql::get_driver_instance();
        
        // Usa as constantes com seus dados para conectar
        connection = driver->connect(url, user, password);
        connection->setSchema(schema);

    } catch (sql::SQLException &e) {
        std::cerr << "ERRO FATAL: Falha ao conectar com o banco de dados." << std::endl;
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// O destrutor e o getConnection() continuam iguais
ServerDBConnection::~ServerDBConnection() {
    if (connection) {
        delete connection;
    }
}

sql::Connection* ServerDBConnection::getConnection() {
    return connection;
}