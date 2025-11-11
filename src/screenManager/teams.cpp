#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../include/Coach.h"
#include "../include/CustomException.h"
#include "../include/Loggable.h"
#include "../include/Player.h"
#include "../include/ScreenManager.h"
#include "../include/Sponsor.h"
#include "../include/Stadium.h"
#include "../include/Team.h"

void Team::addPlayer(Player* player) {
    if (std::find(players.begin(), players.end(), player) != players.end()) {
        throw ValidationException("O jogador ja faz parte deste time.");
    }

    if (players.size() >= 36) {
        throw ValidationException("O time atingiu o limite maximo de 25 jogadores.");
    }
    players.push_back(player);
}

void Team::addSponsor(Sponsor* sponsor) {
    if (std::find(sponsors.begin(), sponsors.end(), sponsor) != sponsors.end()) {
        throw ValidationException("Este patrocinador ja patrocina o time.");
    }
    sponsors.push_back(sponsor);
}

void Team::setCoach(Coach* newCoach) {
    if (coach == newCoach) {
        throw ValidationException("Este tecnico ja esta definido para o time.");
    }
    coach = newCoach;
}

void Team::setStadium(Stadium* newStadium) {
    if (stadium == newStadium) {
        throw ValidationException("Este estadio ja esta definido como sede do time.");
    }
    stadium = newStadium;
}

void Team::removePlayer(Player* player) {
    auto it = std::remove(players.begin(), players.end(), player);
    if (it == players.end()) {
        throw ValidationException("O jogador nao pertence a este time.");
    }
    players.erase(it, players.end());
}

void Team::removeSponsor(Sponsor* sponsor) {
    auto it = std::remove(sponsors.begin(), sponsors.end(), sponsor);
    if (it == sponsors.end()) {
        throw ValidationException("O patrocinador nao patrocina este time.");
    }
    sponsors.erase(it, sponsors.end());
}

void Team::removeCoach() {
    if (coach == nullptr) {
        throw ValidationException("Este time ja nao possui um tecnico definido.");
    }
    coach = nullptr;
}

void Team::removeStadium() {
    if (stadium == nullptr) {
        throw ValidationException("Este time ja nao possui um estadio definido.");
    }
    stadium = nullptr;
}

void Team::displayDetails() const { display(std::cout); }

void Team::display(std::ostream& os) const {
    os << "TIME: " << name << " (Fundado: " << foundedYear << ", Cidade: " << city << ")";

    os << "\n    Tecnico: " << (coach ? coach->getName() : "N/A");
    os << "\n    Estadio: " << (stadium ? stadium->getName() : "N/A");

    os << "\n    Jogadores (" << players.size() << "): ";
    if (players.empty()) {
        os << "Nenhum";
    } else {
        bool first = true;
        for (const auto& player : players) {
            if (!first)
                os << ", ";
            os << player->getName();
            first = false;
        }
    }

    os << "\n    Patrocinadores (" << sponsors.size() << "): ";
    if (sponsors.empty()) {
        os << "Nenhum";
    } else {
        bool first = true;
        for (const auto& sponsor : sponsors) {
            if (!first)
                os << ", ";
            os << sponsor->getName();
            first = false;
        }
    }
}

bool ScreenManager::isPlayerLinked(const Player* player) const {
    for (const auto& teamPtr : teams) {
        const auto& playersList = teamPtr->getPlayers();
        if (std::find(playersList.begin(), playersList.end(), player) != playersList.end()) {
            return true;
        }
    }
    return false;
}

bool ScreenManager::isCoachLinked(const Coach* coach) const {
    for (const auto& teamPtr : teams) {
        if (teamPtr->getCoach() == coach) {
            return true;
        }
    }
    return false;
}

bool ScreenManager::isStadiumLinked(const Stadium* stadium) const {
    for (const auto& teamPtr : teams) {
        if (teamPtr->getStadium() == stadium) {
            return true;
        }
    }
    return false;
}

bool ScreenManager::isSponsorLinked(const Sponsor* sponsor) const {
    for (const auto& teamPtr : teams) {
        const auto& sponsorsList = teamPtr->getSponsors();
        if (std::find(sponsorsList.begin(), sponsorsList.end(), sponsor) != sponsorsList.end()) {
            return true;
        }
    }
    return false;
}

bool ScreenManager::isTeamLinked(const Team* team) const {
    for (const auto& leaguePtr : leagues) {
        const auto& teamsList = leaguePtr->getTeams();
        if (std::find(teamsList.begin(), teamsList.end(), team) != teamsList.end()) {
            return true;
        }
    }
    return false;
}

void ScreenManager::manageTeams() {
    int choice;
    do {
        clearScreen();
        std::cout << "===== ⚽ Gerenciar Times =====\n";
        std::cout << "[1] Adicionar\n";
        std::cout << "[2] Listar\n";
        std::cout << "[3] Atualizar\n";
        std::cout << "[4] Remover\n";
        std::cout << "[5] Adicionar Jogador\n";
        std::cout << "[6] Definir Tecnico\n";
        std::cout << "[7] Definir Estadio\n";
        std::cout << "[8] Adicionar Patrocinador\n";
        std::cout << "[9] Remover Jogador/Patrocinador\n";
        std::cout << "[0] Voltar\n";
        std::cout << "\nEscolha uma opcao: ";

        choice = getMenuOption(0, 9);

        std::vector<Loggable*> loggables;
        for (const auto& t : teams) {
            loggables.push_back(t.get());
        }

        try {
            switch (choice) {
                case 1:
                    addTeam();
                    break;
                case 2:
                    listItems(loggables, "Times");
                    break;
                case 3:
                    updateTeam(loggables);
                    break;
                case 4:
                    removeTeam(loggables);
                    break;
                case 5:
                    addPlayerToTeam(loggables);
                    break;
                case 6:
                    setCoachToTeam(loggables);
                    break;
                case 7:
                    setStadiumToTeam(loggables);
                    break;
                case 8:
                    addSponsorToTeam(loggables);
                    break;
                case 9:
                    removeTeamMembers(loggables);
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

void ScreenManager::addPlayerToTeam(const std::vector<Loggable*>& teamLoggables) {
    clearScreen();
    int teamIndex = selectItem(teamLoggables, "adicionar jogador (Time)");
    if (teamIndex == -1)
        return;
    Team* team = teams[teamIndex].get();

    std::vector<Loggable*> playerLoggables;
    for (const auto& p : players) {
        playerLoggables.push_back(p.get());
    }

    int playerIndex = selectItem(playerLoggables, "adicionar ao time (Jogador)");
    if (playerIndex == -1)
        return;
    Player* player = players[playerIndex].get();

    team->addPlayer(player);
    Loggable::print("\nJogador ");
    std::cout << player->getName();
    Loggable::print(" adicionado ao time ");
    std::cout << team->getName();
    Loggable::print(" com sucesso!\n");
}

void ScreenManager::setCoachToTeam(const std::vector<Loggable*>& teamLoggables) {
    clearScreen();
    int teamIndex = selectItem(teamLoggables, "definir tecnico (Time)");
    if (teamIndex == -1)
        return;
    Team* team = teams[teamIndex].get();

    std::vector<Loggable*> coachLoggables;
    for (const auto& c : coaches) {
        coachLoggables.push_back(c.get());
    }

    int coachIndex = selectItem(coachLoggables, "definir como tecnico");
    if (coachIndex == -1)
        return;
    Coach* coach = coaches[coachIndex].get();

    team->setCoach(coach);
    Loggable::print("\nTecnico ");
    std::cout << coach->getName();
    Loggable::print(" definido para o time ");
    std::cout << team->getName();
    Loggable::print(" com sucesso!\n");
}

void ScreenManager::setStadiumToTeam(const std::vector<Loggable*>& teamLoggables) {
    clearScreen();
    int teamIndex = selectItem(teamLoggables, "definir estadio (Time)");
    if (teamIndex == -1)
        return;
    Team* team = teams[teamIndex].get();

    std::vector<Loggable*> stadiumLoggables;
    for (const auto& s : stadiums) {
        stadiumLoggables.push_back(s.get());
    }

    int stadiumIndex = selectItem(stadiumLoggables, "definir como estadio");
    if (stadiumIndex == -1)
        return;
    Stadium* stadium = stadiums[stadiumIndex].get();

    team->setStadium(stadium);
    Loggable::print("\nEstadio ");
    std::cout << stadium->getName();
    Loggable::print(" definido para o time ");
    std::cout << team->getName();
    Loggable::print(" com sucesso!\n");
}

void ScreenManager::addSponsorToTeam(const std::vector<Loggable*>& teamLoggables) {
    clearScreen();
    int teamIndex = selectItem(teamLoggables, "adicionar patrocinador (Time)");
    if (teamIndex == -1)
        return;
    Team* team = teams[teamIndex].get();

    std::vector<Loggable*> sponsorLoggables;
    for (const auto& s : sponsors) {
        sponsorLoggables.push_back(s.get());
    }

    int sponsorIndex = selectItem(sponsorLoggables, "adicionar ao time (Patrocinador)");
    if (sponsorIndex == -1)
        return;
    Sponsor* sponsor = sponsors[sponsorIndex].get();

    team->addSponsor(sponsor);
    Loggable::print("\nPatrocinador ");
    std::cout << sponsor->getName();
    Loggable::print(" adicionado ao time ");
    std::cout << team->getName();
    Loggable::print(" com sucesso!\n");
}

void ScreenManager::removeTeamMembers(const std::vector<Loggable*>& teamLoggables) {
    clearScreen();
    // 1. Seleciona o time
    int teamIndex = selectItem(teamLoggables, "remover membro");
    if (teamIndex == -1)
        return;
    Team* team = teams[teamIndex].get();

    Loggable::print("\n-- Remocao de Membros do Time: ");
    std::cout << team->getName();
    Loggable::print(" --\n");

    int memberChoice;
    Loggable::print("[1] Jogador\n");
    Loggable::print("[2] Tecnico\n");
    Loggable::print("[3] Estadio\n");
    Loggable::print("[4] Patrocinador\n");
    Loggable::print("[0] Voltar\n");
    Loggable::print("\nEscolha o tipo de membro para remover: ");

    memberChoice = getMenuOption(0, 4);

    try {
        switch (memberChoice) {
            case 1: {
                std::vector<Loggable*> playerLoggables;
                for (const auto& p : team->getPlayers()) {
                    playerLoggables.push_back(p);
                }

                if (playerLoggables.empty()) {
                    throw ValidationException("Este time nao possui jogadores para remover.");
                }

                int playerIndex = selectItem(playerLoggables, "remover (Jogador)");
                if (playerIndex == -1)
                    return;
                Player* player = dynamic_cast<Player*>(playerLoggables[playerIndex]);

                team->removePlayer(player);
                Loggable::print("\nJogador ");
                std::cout << player->getName();
                Loggable::print(" removido do time com sucesso.\n");
                break;
            }
            case 2: {
                if (team->getCoach() == nullptr) {
                    throw ValidationException("Este time ja nao possui um tecnico.");
                }
                Coach* coach = team->getCoach();
                Loggable::print("Tem certeza que deseja remover o Tecnico ");
                std::cout << coach->getName();
                Loggable::print("? (s/n): ");
                char confirm;
                std::cin >> confirm;
                if (tolower(confirm) == 's') {
                    team->removeCoach();
                    Loggable::print("\nTecnico removido do time com sucesso.\n");
                } else {
                    Loggable::print("\nRemocao cancelada.\n");
                }
                break;
            }
            case 3: {
                if (team->getStadium() == nullptr) {
                    throw ValidationException("Este time ja nao possui um estadio.");
                }
                Stadium* stadium = team->getStadium();
                Loggable::print("Tem certeza que deseja remover o Estadio ");
                std::cout << stadium->getName();
                Loggable::print("? (s/n): ");
                char confirm;
                std::cin >> confirm;
                if (tolower(confirm) == 's') {
                    team->removeStadium();
                    Loggable::print("\nEstadio removido do time com sucesso.\n");
                } else {
                    Loggable::print("\nRemocao cancelada.\n");
                }
                break;
            }
            case 4: {
                std::vector<Loggable*> sponsorLoggables;
                for (const auto& s : team->getSponsors()) {
                    sponsorLoggables.push_back(s);
                }

                if (sponsorLoggables.empty()) {
                    throw ValidationException("Este time nao possui patrocinadores para remover.");
                }

                int sponsorIndex = selectItem(sponsorLoggables, "remover (Patrocinador)");
                if (sponsorIndex == -1)
                    return;
                Sponsor* sponsor = dynamic_cast<Sponsor*>(sponsorLoggables[sponsorIndex]);

                team->removeSponsor(sponsor);
                Loggable::print("\nPatrocinador ");
                std::cout << sponsor->getName();
                Loggable::print(" removido do time com sucesso.\n");
                break;
            }
            case 0:
                return;
        }
    } catch (const std::exception& e) {
        Loggable::print("\n!!! ERRO: ");
        std::cout << e.what();
        Loggable::print(" !!!\n");
    }

    pause();
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
    if (index == -1)
        return;

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
    if (index == -1)
        return;

    Team* team = teams[index].get();

    if (isTeamLinked(team)) {
        throw ValidationException(
            "O time (" + team->getName() +
            ") nao pode ser removido, pois esta vinculado a pelo menos uma liga.");
    }

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