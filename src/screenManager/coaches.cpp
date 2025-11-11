#include "../include/ScreenManager.h"
#include "../include/CustomException.h"
#include "../include/Loggable.h" 
#include <iostream>
#include <string>
#include <limits>
#include <vector>

void ScreenManager::manageCoaches() {
    int choice;
    do {
        clearScreen();
        std::cout << "===== 🎓 Gerenciar Técnicos =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 4);

        std::vector<Loggable*> loggables;
        for (const auto& c : coaches) {
            loggables.push_back(c.get());
        }

        try {
            switch (choice) {
                case 1: addCoach(); break;
                case 2: listItems(loggables, "Técnicos"); break;
                case 3: updateCoach(loggables); break;
                case 4: removeCoach(loggables); break;
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

void ScreenManager::addCoach() {
    clearScreen();
    std::cout << "--- Adicionar Novo Técnico ---\n";
    std::string name, license;
    int age;

    Loggable::print("Nome: ");
    std::getline(std::cin >> std::ws, name);
    
    if (name.empty()) {
        throw ValidationException("Nome nao pode ser vazio.");
    }

    Loggable::print("Idade: ");
    age = getMenuOption(18, 99);

    Loggable::print("Licenca (ex: Pro, A, B): ");
    std::getline(std::cin >> std::ws, license);
    
    if (license.empty()) {
        throw ValidationException("Licenca nao pode ser vazia.");
    }

    coaches.push_back(std::make_unique<Coach>(name, age, license));
    Loggable::print("\nTécnico adicionado com sucesso!\n");
}

void ScreenManager::updateCoach(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "atualizar");
    if (index == -1) return;

    Coach* coach = coaches[index].get();
    std::cout << "Editando: " << *coach << "\n";
    
    std::string newLicense;
    Loggable::print("Nova Licenca (deixe em branco para manter '");
    std::cout << coach->getLicense();
    Loggable::print("'): ");
    std::getline(std::cin >> std::ws, newLicense);
    
    if (!newLicense.empty()) {
        coach->setLicense(newLicense);
    }
    
    Loggable::print("\nTécnico atualizado com sucesso!\n");
}

void ScreenManager::removeCoach(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "remover");
    if (index == -1) return;

    Coach* coach = coaches[index].get();

    if (isCoachLinked(coach)) {
        throw ValidationException("O tecnico (" + coach->getName() + ") nao pode ser removido, pois esta vinculado a pelo menos um time.");
    }

    Loggable::print("Tem certeza que deseja remover ");
    std::cout << *(coaches[index]);
    Loggable::print("? (s/n): ");
    char confirm;
    std::cin >> confirm;
    if (confirm == 's' || confirm == 'S') {
        coaches.erase(coaches.begin() + index);    
        Loggable::print("Técnico removido com sucesso.\n");
    } else {    
        Loggable::print("Operacao cancelada.\n");
    }
}