#pragma once
#include <string>
#include <vector> 

#include "Organization.h"
#include "Player.h"
#include "Coach.h"
#include "Stadium.h"
#include "Sponsor.h"

class Team : public Organization, public Loggable {
private:
    std::string city;
    std::vector<Player*> players;
    Coach* coach = nullptr;
    Stadium* stadium = nullptr;
    std::vector<Sponsor*> sponsors;

public:
    Team(std::string n, int y, std::string c)
        : Organization(n, y), city(c) {}

    std::string getCity() const { return city; }
    void setCity(const std::string& c) { city = c; }

    void addPlayer(Player* player);
    void addSponsor(Sponsor* sponsor);
    
    void setCoach(Coach* coach);
    void setStadium(Stadium* stadium);

    void removePlayer(Player* player);
    void removeSponsor(Sponsor* sponsor);
    void removeCoach();  
    void removeStadium();

    Coach* getCoach() const { return coach; }
    Stadium* getStadium() const { return stadium; }
    const std::vector<Player*>& getPlayers() const { return players; }
    const std::vector<Sponsor*>& getSponsors() const { return sponsors; }
    
    void displayDetails() const override; 
    void display(std::ostream& os) const override; 
};