#pragma once
#include "Organization.h"
#include <string>

class Team : public Organization, public Loggable {
private:
    std::string city;

public:
    Team(std::string n, int y, std::string c)
        : Organization(n, y), city(c) {}

    std::string getCity() const { return city; }
    void setCity(const std::string& c) { city = c; }

    void displayDetails() const override {
        Organization::displayDetails();
        std::cout << ", Cidade: " << city;
    }

    void display(std::ostream& os) const override {
        os << "TIME: " << name
           << " (Fundado: " << foundedYear << ", Cidade: " << city << ")";
    }
};