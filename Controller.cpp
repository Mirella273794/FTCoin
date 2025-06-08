#include "Controller.h"
#include "Menu.h"
#include "Utils.h"
#include "TextFromFile.h" 
#include <iostream>

using namespace std;

void Controller::start() {
    showMainMenu();
}

void Controller::showMainMenu() {
    Menu menu({"Carteiras", "Ajuda", "Sair"}, "Menu Principal");
    
    while (true) {
        int choice = menu.getChoice();
        switch (choice) {
            case 1: showWalletMenu(); break;
            case 2: showHelp(); break;
            case 3: return;
        }
    }
}

void Controller::showHelp() {
    TextFromFile helpText("help.txt");
    Utils::printMessage(helpText.getContent());
}

void Controller::showWalletMenu() {
    Menu menu({"Criar", "Editar", "Excluir", "Listar", "Voltar"}, "Menu Carteiras");
    
    while (true) {
        int choice = menu.getChoice();
        switch (choice) {
            case 1: createWallet(); break;
            case 2: editWallet(); break;
            case 3: deleteWallet(); break;
            case 4: listWallets(); break;
            case 5: return;
        }
    }
}

void Controller::createWallet() {
    string owner = Utils::getInput("Nome do titular: ");
    string broker = Utils::getInput("Corretora: ");

    if (owner.empty() || broker.empty()) {
        Utils::printMessage("Todos os campos devem ser preenchidos");
        return;
    }

    int id = wallets.size() + 1;
    wallets.push_back(new Wallet(id, owner, broker));

    Utils::printMessage("Carteira criada com ID: " + to_string(id));
}

void Controller::editWallet() {
    if (wallets.empty()) {
        Utils::printMessage("Nenhuma carteira cadastrada para editar.");
        return;
    }

    listWallets();
    int id = Utils::getIntInput("ID da carteira para editar: ");
    
    for (auto& wallet : wallets) {
        if (wallet->getId() == id) {
            string newOwner = Utils::getInput("Novo titular [" + wallet->getOwner() + "]: ");
            string newBroker = Utils::getInput("Nova corretora [" + wallet->getBroker() + "]: ");
            
            // Validação igual à criação
            if (newOwner.empty() || newBroker.empty()) {
                Utils::printMessage("Todos os campos devem ser preenchidos");
                return;
            }
            
            wallet->setOwner(newOwner);
            wallet->setBroker(newBroker);
            
            Utils::printMessage("Carteira atualizada com sucesso!");
            return;
        }
    }
    Utils::printMessage("Carteira não encontrada!");
}

void Controller::deleteWallet() {
    if (wallets.empty()) {
        Utils::printMessage("Nenhuma carteira cadastrada para excluir.");
        return;
    }

    listWallets();
    int id = Utils::getIntInput("ID da carteira para excluir: ");
    
    for (auto it = wallets.begin(); it != wallets.end(); ++it) {
        if ((*it)->getId() == id) {

            string confirm = Utils::getInput("⚠ Tem certeza que deseja excluir? (S/N): ");
            if (toupper(confirm[0]) != 'S') {
                Utils::printMessage("Operação cancelada.");
                return;
            }

            delete *it;
            wallets.erase(it);
            Utils::printMessage("Carteira excluída!");
            return;
        }
    }
    Utils::printMessage("Carteira não encontrada!");
}

void Controller::listWallets() {
    if (wallets.empty()) {
        Utils::printMessage("Nenhuma carteira cadastrada.");
        return;
    }
    
    for (const auto& wallet : wallets) {
        Utils::printMessage(
            "ID: " + to_string(wallet->getId()) +
            " | Titular: " + wallet->getOwner() +
            " | Corretora: " + wallet->getBroker()
        );
    }
}

Controller::~Controller() {
    for (auto wallet : wallets) {
        delete wallet;
    }
}