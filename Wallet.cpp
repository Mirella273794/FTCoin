#include "Wallet.h"

using namespace std;

const string Wallet::coin = "FTCoin";

Wallet::Wallet(int id, const string& owner, const string& broker)
    : id(id), owner(owner), broker(broker) {}

int Wallet::getId() const { return id; }
string Wallet::getOwner() const { return owner; }
string Wallet::getBroker() const { return broker; }
string Wallet::getCoin() const { return coin; }

void Wallet::setOwner(const string& newOwner) {
    owner = newOwner;
}

void Wallet::setBroker(const string& newBroker) {
    broker = newBroker;
}