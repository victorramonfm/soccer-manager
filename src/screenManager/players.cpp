#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../include/CustomException.h"
#include "../include/Loggable.h"
#include "../include/ScreenManager.h"

void ScreenManager::managePlayers() {
    int choice;

    do {
        clearScreen();
        std::cout << "===== 👤 Gerenciar Jogadores =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 4);

        std::vector<Loggable*> loggables;
        for (const auto& p : players) {
            loggables.push_back(p.get());
        }

        try {
            switch (choice) {
                case 1:
                    addPlayer();
                    break;
                case 2:
                    listItems(loggables, "Jogadores");
                    break;
                case 3:
                    updatePlayer(loggables);
                    break;
                case 4:
                    removePlayer(loggables);
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

void ScreenManager::addPlayer() {
    clearScreen();
    std::cout << "--- Adicionar Novo Jogador ---\n";
    std::string name, pos;
    int age, num;

    Loggable::print("Nome: ");
    std::getline(std::cin >> std::ws, name);

    if (name.empty()) {
        throw ValidationException("Nome nao pode ser vazio.");
    }

    Loggable::print("Idade: ");
    age = getMenuOption(1, 99);

    Loggable::print("Posicao (ex: Atacante): ");
    std::getline(std::cin >> std::ws, pos);

    Loggable::print("Numero da Camisa: ");
    num = getMenuOption(1, 99);

    players.push_back(std::make_unique<Player>(name, age, pos, num));
    Loggable::print("\nJogador adicionado com sucesso!\n");
}

void ScreenManager::updatePlayer(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "atualizar");
    if (index == -1)
        return;

    Player* player = players[index].get();
    std::cout << "Editando: " << *player << "\n";

    std::string newName;
    Loggable::print("Novo Nome (deixe em branco para manter '");
    std::cout << player->getName();
    Loggable::print("'): ");
    std::getline(std::cin >> std::ws, newName);

    if (!newName.empty()) {
        player->setName(newName);
    }

    Loggable::print("\nJogador atualizado com sucesso!\n");
}

void ScreenManager::removePlayer(const std::vector<Loggable*>& loggables) {
    int index = selectItem(loggables, "remover");
    if (index == -1)
        return;

    Player* player = players[index].get();

    if (isPlayerLinked(player)) {
        throw ValidationException(
            "O jogador (" + player->getName() +
            ") nao pode ser removido, pois esta vinculado a pelo menos um time.");
    }

    Loggable::print("Tem certeza que deseja remover ");
    std::cout << *(players[index]);
    Loggable::print("? (s/n): ");
    char confirm;
    std::cin >> confirm;
    if (confirm == 's' || confirm == 'S') {
        players.erase(players.begin() + index);
        Loggable::print("Jogador removido com sucesso.\n");
    } else {
        Loggable::print("Operacao cancelada.\n");
    }
}