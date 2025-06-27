#ifndef SERVERDBCONNECTION_H_
#define SERVERDBCONNECTION_H_

#include <mariadb/conncpp.hpp> 
#include <string>

class ServerDBConnection {
private:
    sql::Driver* driver;
    sql::Connection* connection; 

public:
    ServerDBConnection(); 
    virtual ~ServerDBConnection();
    // Método para fornecer a conexão para outras partes do programa (DAOs)
    sql::Connection* getConnection();
};

#endif /* SERVERDBCONNECTION_H_ */
