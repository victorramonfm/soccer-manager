#pragma once
#include <string>

#include "Person.h"

class Coach : public Person, public Loggable {
   private:
    std::string license;

   public:
    Coach(std::string n, int a, std::string l) : Person(n, a), license(l) {}

    std::string getLicense() const { return license; }
    void setLicense(const std::string& l) { license = l; }

    void displayDetails() const override {
        Person::displayDetails();
        std::cout << ", Licenca: " << license;
    }

    void display(std::ostream& os) const override {
        os << "TECNICO: " << name << " (Idade: " << age << ", Licenca: " << license << ")";
    }
};