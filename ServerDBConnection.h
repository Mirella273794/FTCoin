/* ********************************************************************************
 * FT_Coin - ServerDBConnection.h
 * Descrição: Classe que gerencia a conexão com o servidor MariaDB.
 ******************************************************************************** */

#ifndef SERVERDBCONNECTION_H_
#define SERVERDBCONNECTION_H_

// Includes do MariaDB Connector/C++
#include <mysql/jdbc.h>
#include <string>

class ServerDBConnection {
private:
    sql::Driver* driver;
    sql::Connection* connection; // O objeto de conexão que os DAOs usarão

public:
    // O construtor estabelece a conexão
    ServerDBConnection(const std::string& url, const std::string& user, const std::string& password, const std::string& schema);
    
    // O destrutor fecha a conexão
    virtual ~ServerDBConnection();

    // Método para fornecer a conexão para outras partes do programa (DAOs)
    sql::Connection* getConnection();
};

#endif /* SERVERDBCONNECTION_H_ */