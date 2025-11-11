#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../include/CustomException.h"
#include "../include/Loggable.h"
#include "../include/ScreenManager.h"

void ScreenManager::listItems(const std::vector<Loggable*>& items, const std::string& title) {
    clearScreen();
    std::cout << "--- Lista de " << title << " ---\n";
    if (items.empty()) {
        Loggable::print("Nenhum item cadastrado.\n");
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << *(items[i]) << "\n";
    }
}

int ScreenManager::selectItem(const std::vector<Loggable*>& items, const std::string& prompt) {
    listItems(items, "Itens");
    if (items.empty()) {
        Loggable::print("Nao ha itens para ");
        std::cout << prompt;
        Loggable::print(".\n");
        return -1;
    }
    Loggable::print("Digite o numero do item que deseja ");
    std::cout << prompt;
    Loggable::print(" (ou 0 para cancelar): ");
    int index = getMenuOption(0, items.size());

    if (index == 0) {
        Loggable::print("Operacao cancelada.\n");
        return -1;
    }
    return index - 1;
}

void ScreenManager::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ScreenManager::pause() {
    Loggable::print("\nPressione Enter para continuar...");
    std::cin.get();
}