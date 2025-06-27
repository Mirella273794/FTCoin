#include "ServerDBConnection.h"
#include <iostream>
#include <string>
#include <cctype> 

ServerDBConnection::ServerDBConnection() {

    const std::string url = "tcp://143.106.243.64:3306"; 
    const std::string user = "PooI_25_B05";             
    const std::string password = "blwltAO53Y";         
    
    const std::string schema = "PooI_25_B05";

    try {
        driver = sql::mariadb::get_driver_instance();
        
        connection = driver->connect(url, user, password);
        connection->setSchema(schema);

    } catch (sql::SQLException &e) {
        std::cerr << "ERRO FATAL: FATAL ERROR: Failed to connect to the database.." << std::endl;
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        exit(EXIT_FAILURE);
    }
}

ServerDBConnection::~ServerDBConnection() {
    if (connection) {
        delete connection;
    }
}

sql::Connection* ServerDBConnection::getConnection() {
    return connection;
}