#include "FTCoinQuoteDAO.hpp"
#include <iostream>
#include <optional>
using namespace std;

FTCoinQuoteDAO::FTCoinQuoteDAO(const string& host, const string& port, const string& user, const string& password, const string& database) {
    driver = sql::mariadb::get_driver_instance();

    sql::SQLString url = "jdbc:mariadb://" + host + ":" + port + "/" + database;
    sql::Properties properties({
        {"user", user},
        {"password", password}
    });

    conn.reset(driver->connect(url, properties));
}

FTCoinQuoteDAO::~FTCoinQuoteDAO() {
    conn->close();
}

bool FTCoinQuoteDAO::checkExistence(const string& date) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT 1 FROM Oraculo WHERE Data = ?"));
        pstmt->setString(1, date);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        return res->next();
    } catch (sql::SQLException& e) {
        cerr << "Error checking quote existence: " << e.what() << endl;
        throw;
    }
}

optional<double> FTCoinQuoteDAO::getPreviousQuote(const string& date) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT Cotacao FROM Oraculo WHERE Data < ? ORDER BY Data DESC LIMIT 1")
        );
        pstmt->setString(1, date);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        return res->next() ? optional<double>(res->getDouble("Cotacao")) : nullopt;
    } catch (sql::SQLException& e) {
        cerr << "Error fetching previous quote: " << e.what() << endl;
        throw;
    }
}

optional<double> FTCoinQuoteDAO::getNextQuote(const string& date) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT Cotacao FROM Oraculo WHERE Data > ? ORDER BY Data ASC LIMIT 1")
        );
        pstmt->setString(1, date);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        return res->next() ? optional<double>(res->getDouble("Cotacao")) : nullopt;
    } catch (sql::SQLException& e) {
        cerr << "Error fetching next quote: " << e.what() << endl;
        throw;
    }
}


void FTCoinQuoteDAO::saveQuote(const string& date, double quote) {
    if (quote < 0) throw invalid_argument("Quote must be non-negative");

    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("REPLACE INTO Oraculo (Data, Cotacao) VALUES (?, ?)"));
        pstmt->setString(1, date);
        pstmt->setDouble(2, quote);
        pstmt->execute();
    } catch (sql::SQLException& e) {
        cerr << "Error saving quote: " << e.what() << endl;
        throw;
    }
}

double FTCoinQuoteDAO::getQuoteByDate(const string& date) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT Cotacao FROM Oraculo WHERE Data = ?"));
        pstmt->setString(1, date);

        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return res->getDouble("Cotacao");
        } else {
            throw runtime_error("Quote not found for date: " + date);
        }
    } catch (sql::SQLException& e) {
        cerr << "Error retrieving quote: " << e.what() << endl;
        throw;
    }
}
