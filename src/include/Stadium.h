#pragma once
#include "Loggable.h"
#include <string>

class Stadium : public Loggable {
private:
    std::string name;
    int capacity;
    std::string address;

public:
    Stadium(std::string n, int c, std::string a)
        : name(n), capacity(c), address(a) {}

    std::string getName() const { return name; }
    int getCapacity() const { return capacity; }
    void setName(const std::string& n) { name = n; }
    void setCapacity(int c) { capacity = c; }

    void display(std::ostream& os) const override {
        os << "ESTADIO: " << name
           << " (Capacidade: " << capacity << ", End: " << address << ")";
    }
};