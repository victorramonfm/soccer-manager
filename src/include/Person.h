#pragma once
#include <string>

#include "Loggable.h"

class Person {
   protected:
    std::string name;
    int age;

   public:
    Person(const std::string& n, int a) : name(n), age(a) {}
    virtual ~Person() {}

    std::string getName() const { return name; }
    int getAge() const { return age; }
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }

    virtual void displayDetails() const { std::cout << "  Nome: " << name << ", Idade: " << age; }
};