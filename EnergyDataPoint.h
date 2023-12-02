#pragma once
#include <string>
#include <unordered_map>
struct EnergyDataPoint {
    std::string State;
    int Year;
    std::unordered_map<std::string, float> catData;

    void print() const {
        std::cout << "State: " << State << std::endl;
        std::cout << "Year: " << Year << std::endl;

        std::cout << "Category Data:" << std::endl;
        for (const auto& pair : catData) {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }
};