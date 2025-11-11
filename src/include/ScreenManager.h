#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Loggable.h" 
#include "Player.h"
#include "Coach.h"
#include "Team.h"
#include "Stadium.h"
#include "Sponsor.h"
#include "League.h"

using PlayerPtr = std::unique_ptr<Player>;
using CoachPtr = std::unique_ptr<Coach>;
using TeamPtr = std::unique_ptr<Team>;
using StadiumPtr = std::unique_ptr<Stadium>;
using SponsorPtr = std::unique_ptr<Sponsor>;
using LeaguePtr = std::unique_ptr<League>;

class ScreenManager {
private:
    std::vector<PlayerPtr> players;
    std::vector<CoachPtr> coaches;
    std::vector<TeamPtr> teams;
    std::vector<StadiumPtr> stadiums;
    std::vector<SponsorPtr> sponsors;
    std::vector<LeaguePtr> leagues;

    int getMenuOption(int min, int max);
    void clearScreen();
    void pause();
    void print(const std::string& message);

    void showMainMenu();

    void managePlayers();
    void manageCoaches();
    void manageTeams();
    void manageStadiums();
    void manageSponsors();
    void manageLeagues();

    void listItems(const std::vector<Loggable*>& items, const std::string& title);
    int selectItem(const std::vector<Loggable*>& items, const std::string& prompt);
    
    void addPlayer();
    void addCoach();
    void addTeam();
    void addStadium();
    void addSponsor();
    void addLeague();
    void addPlayerToTeam(const std::vector<Loggable*>& teamLoggables);
    void addSponsorToTeam(const std::vector<Loggable*>& teamLoggables);
    void addTeamToLeague(const std::vector<Loggable*>& leagueLoggables);

    void updatePlayer(const std::vector<Loggable*>& loggables);
    void updateCoach(const std::vector<Loggable*>& loggables);
    void updateTeam(const std::vector<Loggable*>& loggables);
    void updateStadium(const std::vector<Loggable*>& loggables);
    void updateSponsor(const std::vector<Loggable*>& loggables);
    void updateLeague(const std::vector<Loggable*>& loggables);

    void setCoachToTeam(const std::vector<Loggable*>& teamLoggables);
    void setStadiumToTeam(const std::vector<Loggable*>& teamLoggables);
    
    void removePlayer(const std::vector<Loggable*>& loggables);
    void removeCoach(const std::vector<Loggable*>& loggables);
    void removeTeam(const std::vector<Loggable*>& loggables);
    void removeStadium(const std::vector<Loggable*>& loggables);
    void removeSponsor(const std::vector<Loggable*>& loggables);
    void removeLeague(const std::vector<Loggable*>& loggables);
    void removeTeamMembers(const std::vector<Loggable*>& teamLoggables);
    void removeTeamFromLeague(const std::vector<Loggable*>& leagueLoggables);
    
    bool isPlayerLinked(const Player* player) const;
    bool isCoachLinked(const Coach* coach) const;
    bool isStadiumLinked(const Stadium* stadium) const;
    bool isSponsorLinked(const Sponsor* sponsor) const;
    bool isTeamLinked(const Team* team) const;

public:
    ScreenManager();

    void run();
};