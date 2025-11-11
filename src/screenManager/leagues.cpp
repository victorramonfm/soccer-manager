#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../include/CustomException.h"
#include "../include/League.h"
#include "../include/Loggable.h"
#include "../include/ScreenManager.h"
#include "../include/Team.h"

void League::addTeam(Team* team) {
    if (std::find(teams.begin(), teams.end(), team) != teams.end()) {
        throw ValidationException("O time ja faz parte desta liga.");
    }
    teams.push_back(team);
}

void League::display(std::ostream& os) const {
    os << "LIGA: " << name << " (Pais: " << country << ")";

    os << "\n    Times (" << teams.size() << "): ";
    if (teams.empty()) {
        os << "Nenhum";
    } else {
        bool first = true;
        for (const auto& team : teams) {
            if (!first)
                os << ", ";
            os << team->getName();
            first = false;
        }
    }
}

void League::removeTeam(Team* team) {
    auto it = std::remove(teams.begin(), teams.end(), team);

    if (it == teams.end()) {
        throw ValidationException("O time nao pertence a esta liga.");
    }

    teams.erase(it, teams.end());
}

void ScreenManager::manageLeagues() {
    int choice;
    do {
        clearScreen();
        std::cout << "===== 🏆 Gerenciar Ligas =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[5] Adicionar Time a Liga\n";
        std::cout << "[6] Remover Time da Liga\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 6);

        std::vector<Loggable*> loggables;
        for (const auto& l : leagues) {
            loggables.push_back(l.get());
        }

        try {
            switch (choice) {
                case 1:
                    addLeague();
                    break;
                case 2:
                    listItems(loggables, "Ligas");
                    break;
                case 3:
                    updateLeague(loggables);
                    break;
                case 4:
                    removeLeague(loggables);
                    break;
                case 5:
                    addTeamToLeague(loggables);
                    break;
                case 6:
                    removeTeamFromLeague(loggables);
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

void ScreenManager::addTeamToLeague(const std::vector<Loggable*>& leagueLoggables) {
    clearScreen();

    int leagueIndex = selectItem(leagueLoggables, "adicionar time (Liga)");
    if (leagueIndex == -1)
        return;
    League* league = leagues[leagueIndex].get();

    std::vector<Loggable*> teamLoggables;
    for (const auto& t : teams) {
        teamLoggables.push_back(t.get());
    }

    int teamIndex = selectItem(teamLoggables, "adicionar a liga (Time)");
    if (teamIndex == -1)
        return;
    Team* team = teams[teamIndex].get();

    league->addTeam(team);
    Loggable::print("\nTime ");
    std::cout << team->getName();
    Loggable::print(" adicionado a liga ");
    std::cout << league->getName();
    Loggable::print(" com sucesso!\n");
}

void ScreenManager::removeTeamFromLeague(const std::vector<Loggable*>& leagueLoggables) {
    clearScreen();

    int leagueIndex = selectItem(leagueLoggables, "remover time (Liga)");
    if (leagueIndex == -1)
        return;
    League* league = leagues[leagueIndex].get();

    std::vector<Loggable*> teamLoggables;
    for (const auto& t : league->getTeams()) {
        teamLoggables.push_back(t);
    }

    if (teamLoggables.empty()) {
        Loggable::print("\nA liga ");
        std::cout << league->getName();
        Loggable::print(" nao possui times vinculados.\n");
        return;
    }

    Loggable::print("\n-- Times vinculados a ");
    std::cout << league->getName();
    Loggable::print(" --\n");

    int teamIndex = selectItem(teamLoggables, "remover da liga (Time)");
    if (teamIndex == -1)
        return;
    Team* team = dynamic_cast<Team*>(teamLoggables[teamIndex]);

    league->removeTeam(team);
    Loggable::print("\nTime ");
    std::cout << team->getName();
    Loggable::print(" removido da liga ");
    std::cout << league->getName();
    Loggable::print(" com sucesso!\n");
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
    if (index == -1)
        return;

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
    if (index == -1)
        return;

    League* league = leagues[index].get();

    if (!league->getTeams().empty()) {
        throw ValidationException("A liga (" + league->getName() +
                                  ") nao pode ser removida, pois possui times vinculados. Remova "
                                  "todos os times primeiro.");
    }

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