#pragma once
#include "Loggable.h"
#include "Team.h"
#include <string>
#include <vector>

class League : public Loggable{
private:
    std::string name;
    std::string country;
    std::vector<Team *> teams;

public:
    League(std::string n, std::string c) : name(n), country(c) {}

    std::string getName() const { return name; }
    std::string getCountry() const { return country; }
    void setName(const std::string &n) { name = n; }
    void setCountry(const std::string &c) { country = c; }

    void addTeam(Team *team);
    void removeTeam(Team* team);

    const std::vector<Team *> &getTeams() const { return teams; }

    void display(std::ostream &os) const override;
};