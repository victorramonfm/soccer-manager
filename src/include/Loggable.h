#pragma once
#include <iostream>

class Loggable {
public:
    virtual ~Loggable() {}
    virtual void display(std::ostream& os) const = 0;
    static void print(const std::string& message);
};

inline std::ostream& operator<<(std::ostream& os, const Loggable& entity) {
    entity.display(os);
    return os;
}