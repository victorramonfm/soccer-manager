#include "../include/configuration.h"
#include "../include/ScreenManager.h"

void Configuration::save() {
    std::ofstream file(CONFIG_FILE);

    if (file.is_open()) {
        file << "DisplayName:" << displayName << std::endl;
        file << "Theme:" << theme << std::endl;
        file.close();
    } else {
        std::cerr << "ERRO: Não foi possível abrir o arquivo para salvar as configurações.\n";
    }
}

void Configuration::load() {
    std::ifstream file(CONFIG_FILE);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.rfind("DisplayName:", 0) == 0) {
                displayName = line.substr(line.find(':') + 1);
            }
            else if (line.rfind("Theme:", 0) == 0) {
                theme = line.substr(line.find(':') + 1);
            }
        }
        file.close();
    } else {
        save();
    }
}

std::string Configuration::getDisplayHeader() const {
    std::string header = "==============================\n";
    header += "Usuário: " + displayName + "\n";
    header += "Tema: " + theme;
    return header;
}

void ScreenManager::manageConfigurations() {
    int choice;
    std::string tempString;

    do {
        clearScreen();
        
        Loggable::print("===== 🛠️ Gerenciar Configurações =====\n");
        Loggable::print("[1] Mudar Nome de Exibição (Atual: ");
        std::cout << userConfig.getDisplayName();
        Loggable::print(")\n");
        
        Loggable::print("[2] Mudar Tema (Atual: ");
        std::cout << userConfig.getTheme();
        Loggable::print(")\n");

        Loggable::print("[0] Voltar e Salvar\n");
        Loggable::print("\nEscolha uma opcao: ");

        choice = getMenuOption(0, 2);

        switch (choice) {
            case 1: {
                Loggable::print("\nNovo Nome de Exibição: ");
                std::getline(std::cin >> std::ws, tempString);
                if (!tempString.empty()) {
                    userConfig.setDisplayName(tempString);
                    Loggable::print("Nome de exibição atualizado! (Não será salvo até você sair do menu).\n");
                } else {
                    Loggable::print("Nome não pode ser vazio. Operação cancelada.\n");
                }
                pause();
                break;
            }
            case 2: {
                Loggable::print("\n[1] Claro\n[2] Escuro\nEscolha o Tema: ");
                int themeChoice = getMenuOption(1, 2);
                if (themeChoice == 1) {
                    userConfig.setTheme("claro");
                } else {
                    userConfig.setTheme("escuro");
                }
                Loggable::print("Tema atualizado!\n");
                pause();
                break;
            }
            case 0: {
                userConfig.save();
                Loggable::print("\nConfigurações salvas com sucesso! Voltando ao Menu Principal...\n");
                pause();
                break;
            }
        }
    } while (choice != 0);
}