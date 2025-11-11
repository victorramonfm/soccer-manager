#pragma once
#include <string>

#include "Loggable.h"

class Organization {
   protected:
    std::string name;
    int foundedYear;

   public:
    Organization(const std::string& n, int y) : name(n), foundedYear(y) {}
    virtual ~Organization() {}

    std::string getName() const { return name; }
    int getFoundedYear() const { return foundedYear; }
    void setName(const std::string& n) { name = n; }

    virtual void displayDetails() const {
        std::cout << "  Nome: " << name << ", Fundacao: " << foundedYear;
    }
};