#ifndef WALLET_H
#define WALLET_H

#include <string>

using namespace std;

class Wallet {
private:
    int id;
    string owner;
    string broker;
    static const string coin;
    
public:
    Wallet(int id, const string& owner, const string& broker);
    
    int getId() const;
    string getOwner() const;
    string getBroker() const;
    string getCoin() const;

    void setOwner(const string& newOwner);
    void setBroker(const string& newBroker);
};

#endif