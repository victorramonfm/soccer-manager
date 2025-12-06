#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Configuration {
private:
    std::string displayName;
    std::string theme;
    const std::string CONFIG_FILE = "user_preferences.txt";

public:
    Configuration() : displayName("Usuário Padrão"), theme("claro") {}

    std::string getDisplayName() const { return displayName; }
    std::string getTheme() const { return theme; }

    void setDisplayName(const std::string& name) { displayName = name; }
    void setTheme(const std::string& t) { theme = t; }

    void save();
    void load();

    std::string getDisplayHeader() const;
};

#endif