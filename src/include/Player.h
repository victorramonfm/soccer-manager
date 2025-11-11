#pragma once
#include <string>

#include "Person.h"

class Player : public Person, public Loggable {
   private:
    std::string position;
    int number;

   public:
    Player(std::string n, int a, std::string p, int num) : Person(n, a), position(p), number(num) {}

    std::string getPosition() const { return position; }
    void setPosition(const std::string& p) { position = p; }

    void displayDetails() const override {
        Person::displayDetails();
        std::cout << ", Posicao: " << position << ", Numero: " << number;
    }

    void display(std::ostream& os) const override {
        os << "JOGADOR [Num " << number << "]: " << name << " (Idade: " << age
           << ", Pos: " << position << ")";
    }
};
