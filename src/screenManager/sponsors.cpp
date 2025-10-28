#include "../include/ScreenManager.h"
#include "../include/CustomException.h"
#include "../include/Loggable.h" 
#include <iostream>
#include <string>
#include <limits>
#include <vector>

void ScreenManager::manageSponsors() {
    int choice;
    do {
        clearScreen();
        std::cout << "===== 💰 Gerenciar Patrocinadores =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 4);

        std::vector<Loggable*> loggables;
        for (const auto& s : sponsors) {
            loggables.push_back(s.get());
        }

        try {
            switch (choice) {
                case 1: addSponsor(); break;
                case 2: listItems(loggables, "Patrocinadores"); break;
                case 3: updateSponsor(loggables); break;
                case 4: removeSponsor(loggables); break;
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

void ScreenManager::addSponsor() {
    clearScreen();
    std::cout << "--- Adicionar Novo Patrocinador ---\n";
    std::string name, industry;
    int year;

    Loggable::print("Nome: ");
    std::getline(std::cin >> std::ws, name);
    
    if (name.empty()) {
        throw ValidationException("Nome nao pode ser vazio.");
    }

    Loggable::print("Ano de Fundacao: ");
    year = getMenuOption(1850, 2024);

    Loggable::print("Ramo/Industria (ex: Bebidas, Tecnologia): ");
    std::getline(std::cin >> std::ws, industry);
    
    sponsors.push_back(std::make_unique<Sponsor>(name, year, industry));
    Loggable::print("\nPatrocinador adicionado com sucesso!\n");
}

void ScreenManager::updateSponsor(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "atualizar");
    if (index == -1) return;

    Sponsor* sponsor = sponsors[index].get();
    std::cout << "Editando: " << *sponsor << "\n";
    
    std::string newIndustry;
    Loggable::print("Nova Industria (deixe em branco para manter '");
    std::cout << sponsor->getIndustry();
    Loggable::print("'): ");
    std::getline(std::cin >> std::ws, newIndustry);
    
    if (!newIndustry.empty()) {
        sponsor->setIndustry(newIndustry);
    }
    
    Loggable::print("\nPatrocinador atualizado com sucesso!\n");
}

void ScreenManager::removeSponsor(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "remover");
    if (index == -1) return;

    Loggable::print("Tem certeza que deseja remover ");
    std::cout << *(sponsors[index]);
    Loggable::print("? (s/n): ");
    char confirm;
    std::cin >> confirm;
    if (confirm == 's' || confirm == 'S') {
        sponsors.erase(sponsors.begin() + index);    
        Loggable::print("Patrocinador removido com sucesso.\n");
    } else {    
        Loggable::print("Operacao cancelada.\n");
    }
}