#include "../include/ScreenManager.h"
#include "../include/CustomException.h"
#include "../include/Loggable.h" 
#include <iostream>
#include <string>
#include <limits>
#include <vector>

void ScreenManager::manageTeams() {
    int choice;
    do {
        clearScreen();
        std::cout << "===== ⚽ Gerenciar Times =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 4);

        std::vector<Loggable*> loggables;
        for (const auto& t : teams) {
            loggables.push_back(t.get());
        }

        try {
            switch (choice) {
                case 1: addTeam(); break;
                case 2: listItems(loggables, "Times"); break;
                case 3: updateTeam(loggables); break;
                case 4: removeTeam(loggables); break;
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

void ScreenManager::addTeam() {
    clearScreen();
    std::cout << "--- Adicionar Novo Time ---\n";
    std::string name, city;
    int year;

    Loggable::print("Nome: ");
    std::getline(std::cin >> std::ws, name);
    
    if (name.empty()) {
        throw ValidationException("Nome nao pode ser vazio.");
    }

    Loggable::print("Ano de Fundacao: ");
    year = getMenuOption(1850, 2024);

    Loggable::print("Cidade Sede: ");
    std::getline(std::cin >> std::ws, city);
    
    teams.push_back(std::make_unique<Team>(name, year, city));
    Loggable::print("\nTime adicionado com sucesso!\n");
}

void ScreenManager::updateTeam(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "atualizar");
    if (index == -1) return;

    Team* team = teams[index].get();
    std::cout << "Editando: " << *team << "\n";
    
    std::string newCity;
    Loggable::print("Nova Cidade (deixe em branco para manter '");
    std::cout << team->getCity();
    Loggable::print("'): ");
    std::getline(std::cin >> std::ws, newCity);
    
    if (!newCity.empty()) {
        team->setCity(newCity);
    }
    
    Loggable::print("\nTime atualizado com sucesso!\n");
}

void ScreenManager::removeTeam(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "remover");
    if (index == -1) return;

    Loggable::print("Tem certeza que deseja remover ");
    std::cout << *(teams[index]);
    Loggable::print("? (s/n): ");
    char confirm;
    std::cin >> confirm;
    if (confirm == 's' || confirm == 'S') {
        teams.erase(teams.begin() + index);    
        Loggable::print("Time removido com sucesso.\n");
    } else {    
        Loggable::print("Operacao cancelada.\n");
    }
}