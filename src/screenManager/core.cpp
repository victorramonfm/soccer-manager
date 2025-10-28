#include "../include/ScreenManager.h"
#include "../include/CustomException.h"
#include "../include/Loggable.h" 
#include <iostream>
#include <string>
#include <limits>
#include <vector>

ScreenManager::ScreenManager() {
}

void ScreenManager::run() {
    int choice;
    do {
        showMainMenu();
        choice = getMenuOption(0, 7);

        switch (choice) {
            case 1: managePlayers(); break;
            case 2: manageCoaches(); break;
            case 3: manageTeams(); break;
            case 4: manageStadiums(); break;
            case 5: manageSponsors(); break;
            case 6: manageLeagues(); break;        
            case 0: Loggable::print("Saindo... Ate logo!\n"); break;
        }
    } while (choice != 0);
}

void ScreenManager::showMainMenu() {
    clearScreen();
    std::cout << "==============================\n";
    std::cout << "     ⚽ SOCCER MANAGER ⚽\n";
    std::cout << "==============================\n";
    std::cout << "[1] 👤 Gerenciar Jogadores\n";
    std::cout << "[2] 🎓 Gerenciar Técnicos\n";
    std::cout << "[3] ⚽ Gerenciar Times\n";
    std::cout << "[4] 🏟️ Gerenciar Estadios\n";
    std::cout << "[5] 💰 Gerenciar Patrocinadores\n";
    std::cout << "[6] 🏆 Gerenciar Ligas\n";
    std::cout << "[0] Sair\n";
    std::cout << "\nEscolha uma opcao: ";
}

int ScreenManager::getMenuOption(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');        
            Loggable::print("Opcao invalida. Por favor, digite um numero entre ");
        std::cout << min;
            Loggable::print(" e ");
        std::cout << max;
            Loggable::print(": ");
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}
