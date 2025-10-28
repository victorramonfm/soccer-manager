#pragma once
#include "Loggable.h"
#include <string>

class League : public Loggable {
private:
    std::string name;
    std::string country;

public:
    League(std::string n, std::string c) : name(n), country(c) {}

    std::string getName() const { return name; }
    std::string getCountry() const { return country; }
    void setName(const std::string& n) { name = n; }
    void setCountry(const std::string& c) { country = c; }
    
    void display(std::ostream& os) const override {
        os << "LIGA: " << name
           << " (Pais: " << country << ")";
    }
};