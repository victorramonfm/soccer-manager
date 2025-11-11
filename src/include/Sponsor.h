#pragma once
#include <string>

#include "Organization.h"

class Sponsor : public Organization, public Loggable {
   private:
    std::string industry;

   public:
    Sponsor(std::string n, int y, std::string i) : Organization(n, y), industry(i) {}

    std::string getIndustry() const { return industry; }
    void setIndustry(const std::string& i) { industry = i; }

    void displayDetails() const override {
        Organization::displayDetails();
        std::cout << ", Industria: " << industry;
    }

    void display(std::ostream& os) const override {
        os << "PATROCINADOR: " << name << " (Fundado: " << foundedYear << ", Ramo: " << industry
           << ")";
    }
};