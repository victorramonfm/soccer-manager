#include "../include/ScreenManager.h"
#include "../include/CustomException.h"
#include "../include/Loggable.h" 
#include <iostream>
#include <string>
#include <limits>
#include <vector>

void ScreenManager::manageLeagues() {
    int choice;
    do {
        clearScreen();
        std::cout << "===== 🏆 Gerenciar Ligas =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 4);

        std::vector<Loggable*> loggables;
        for (const auto& l : leagues) {
            loggables.push_back(l.get());
        }

        try {
            switch (choice) {
                case 1: addLeague(); break;
                case 2: listItems(loggables, "Ligas"); break;
                case 3: updateLeague(loggables); break;
                case 4: removeLeague(loggables); break;
                case 0: break;
            }
        } catch (const std::exception& e) {        
            Loggable::print("\n!!! ERRO: ");
            std::cout << e.what();
            Loggable::print(" !!!\n");
            pause();
        }
        if(choice != 0) pause();

    } while (choice != 0);
}

void ScreenManager::addLeague() {
    clearScreen();
    std::cout << "--- Adicionar Nova Liga ---\n";
    std::string name, country;

    Loggable::print("Nome: ");
    std::getline(std::cin >> std::ws, name);
    
    if (name.empty()) {
        throw ValidationException("Nome nao pode ser vazio.");
    }

    Loggable::print("Pais Sede: ");
    std::getline(std::cin >> std::ws, country);
    
    leagues.push_back(std::make_unique<League>(name, country));
    Loggable::print("\nLiga adicionada com sucesso!\n");
}

void ScreenManager::updateLeague(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "atualizar");
    if (index == -1) return;

    League* league = leagues[index].get();
    std::cout << "Editando: " << *league << "\n";
    
    std::string newCountry;
    Loggable::print("Novo Pais (deixe em branco para manter '");
    std::cout << league->getCountry();
    Loggable::print("'): ");
    std::getline(std::cin >> std::ws, newCountry);
    
    if (!newCountry.empty()) {
        league->setCountry(newCountry);
    }
    
    Loggable::print("\nLiga atualizada com sucesso!\n");
}

void ScreenManager::removeLeague(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "remover");
    if (index == -1) return;

    Loggable::print("Tem certeza que deseja remover ");
    std::cout << *(leagues[index]);
    Loggable::print("? (s/n): ");
    char confirm;
    std::cin >> confirm;
    if (confirm == 's' || confirm == 'S') {
        leagues.erase(leagues.begin() + index);    
        Loggable::print("Liga removida com sucesso.\n");
    } else {    
        Loggable::print("Operacao cancelada.\n");
    }
}