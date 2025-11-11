#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../include/CustomException.h"
#include "../include/Loggable.h"
#include "../include/ScreenManager.h"

void ScreenManager::manageStadiums() {
    int choice;

    do {
        clearScreen();
        std::cout << "===== 🏟️ Gerenciar Estádios =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 4);

        std::vector<Loggable*> loggables;
        for (const auto& s : stadiums) {
            loggables.push_back(s.get());
        }

        try {
            switch (choice) {
                case 1:
                    addStadium();
                    break;
                case 2:
                    listItems(loggables, "Estádios");
                    break;
                case 3:
                    updateStadium(loggables);
                    break;
                case 4:
                    removeStadium(loggables);
                    break;
                case 0:
                    break;
            }
        } catch (const std::exception& e) {
            Loggable::print("\n!!! ERRO: ");
            std::cout << e.what();
            Loggable::print(" !!!\n");
            pause();
        }
        if (choice != 0)
            pause();

    } while (choice != 0);
}

void ScreenManager::addStadium() {
    clearScreen();
    std::cout << "--- Adicionar Novo Estádio ---\n";
    std::string name, address;
    int capacity;

    Loggable::print("Nome: ");
    std::getline(std::cin >> std::ws, name);

    if (name.empty()) {
        throw ValidationException("Nome nao pode ser vazio.");
    }

    Loggable::print("Capacidade (ex: 50000): ");
    capacity = getMenuOption(1000, 200000);

    Loggable::print("Endereco: ");
    std::getline(std::cin >> std::ws, address);

    stadiums.push_back(std::make_unique<Stadium>(name, capacity, address));
    Loggable::print("\nEstádio adicionado com sucesso!\n");
}

void ScreenManager::updateStadium(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "atualizar");
    if (index == -1)
        return;

    Stadium* stadium = stadiums[index].get();
    std::cout << "Editando: " << *stadium << "\n";

    int newCapacity;
    Loggable::print("Nova Capacidade (0 para manter ");
    std::cout << stadium->getCapacity();
    Loggable::print("): ");
    newCapacity = getMenuOption(0, 200000);

    if (newCapacity != 0) {
        stadium->setCapacity(newCapacity);
    }

    Loggable::print("\nEstádio atualizado com sucesso!\n");
}

void ScreenManager::removeStadium(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "remover");
    if (index == -1)
        return;

    Stadium* stadium = stadiums[index].get();

    if (isStadiumLinked(stadium)) {
        throw ValidationException(
            "O estadio (" + stadium->getName() +
            ") nao pode ser removido, pois esta vinculado a pelo menos um time.");
    }

    Loggable::print("Tem certeza que deseja remover ");
    std::cout << *(stadiums[index]);
    Loggable::print("? (s/n): ");
    char confirm;
    std::cin >> confirm;
    if (confirm == 's' || confirm == 'S') {
        stadiums.erase(stadiums.begin() + index);
        Loggable::print("Estádio removido com sucesso.\n");
    } else {
        Loggable::print("Operacao cancelada.\n");
    }
}