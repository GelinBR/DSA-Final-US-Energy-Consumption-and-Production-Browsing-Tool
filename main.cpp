#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include "EnergyDataPoint.h"
#include "EnergyData.h"
using namespace std;

struct EnergyType {
    std::string type;
    std::vector<std::string> methods;
};

std::map<std::string, EnergyType> energyData = {
    {"Commercial", {"Commercial", {"Coal", "Distillate Fuel Oil", "Geothermal", "Hydropower", "Kerosene", "Petroleum", "Natural Gas", "Solar", "Wind", "Wood"}}},
    {"Electric Power", {"Electric Power", {"Coal", "Distillate Fuel Oil", "Natural Gas", "Wood"}}},
    {"Industrial", {"Industrial", {"Coal", "Distillate Fuel Oil", "Geothermal", "Hydropower", "Kerosene", "Petroleum", "Natural Gas", "Other Petroleum Products","Solar", "Wind", "Wood"}}},
    {"Refinery", {"Refinery", {"Coal", "Distillate Fuel Oil", "Natural Gas"}}},
    {"Residential", {"Residential", {"Coal", "Distillate Fuel Oil", "Geothermal", "Kerosene", "Petroleum", "Natural Gas", "Wood"}}},
    {"Transportation", {"Transportation", {"Coal", "Distillate Fuel Oil", "Petroleum", "Natural Gas"}}},
};

void displayOptions() {
    std::cout << "Consumption methods:\n";
    for (const auto& entry : energyData) {
        std::cout << entry.first << "\n";
    }
}

void displayMethods(const std::string& type) {
    const auto& methods = energyData[type].methods;
    std::cout << "Energy types for " << type << ":\n";
    for (const auto& method : methods) {
        std::cout << method << "\n";
    }
}

bool isValidType(const std::string& type) {
    return energyData.find(type) != energyData.end();
}

bool isValidMethod(const std::string& type, const std::string& method) {
    const auto& methods = energyData[type].methods;
    return std::find(methods.begin(), methods.end(), method) != methods.end();
}

int main() {
    // File selection
    const string filename = "energy (OG).csv";

    // File Validation
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file. Error point 1" << std::endl;
        return 1;
    }

    // Dataset Creation
    EnergyData dataset = EnergyData(filename);
    //dataset.print();

    std::string energyType, consumptionMethod;

    //Welcome message
    std::cout << "Welcome to the US Energy Consumption History Browsing Tool!" << std::endl;

    // Display options
    displayOptions();

    while (true) {
        std::cout << "Enter consumption method: ";
        std::cin >> consumptionMethod;
        cout << endl;

        if (isValidType(consumptionMethod)) {
            break;
        }
        else {
            std::cout << "Invalid consumption method. Please try again.\n";
        }
    }

    // Display valid consumption methods for the selected energy type
    displayMethods(consumptionMethod);

    // Get and validate user input for consumption method
    while (true) {
        cout << "Enter energy type: ";
        cin >> energyType;
        cout << endl;

        if (isValidMethod(consumptionMethod, energyType)) {
            break;
        }
        else {
            cout << "Invalid energy type. Please try again.\n";
        }
    }

    int year = 0;
    string temp;
    bool isNum;
    // Get and validate the user input for the year
    while (true)
    {
        cout << "Enter the year from 1960 to 2019: ";
        cin >> temp;
        year = 0;
        isNum = true;
        for (auto i : temp)
        {
            if (!isdigit(i))
            {
                isNum = false;
            }
        }

        if (isNum)
        {
            year = stoi(temp);
        }
        if (isNum && year >= 1960 && year <= 2019)
        {
            break;
        }
        else
        {
            cout << "Invalid year. please try again." << endl;
        }
    }

    //concatenate Consumption.consumptionMethod.energyType
    string type = "Consumption." + consumptionMethod + "." + energyType;

    //call each sortings function(quick sort and Merge sort)
    dataset.createList(year, type);
    dataset.mergeSort(dataset.states, 0, dataset.states.size() - 1);
    cout << "Merge Sort" << endl;
    dataset.print();
    cout << endl << endl;
    dataset.createList(year, type);
    dataset.quickSort(dataset.states, 0, dataset.states.size() - 1);
    cout << "Quick Sort" << endl;
    dataset.print();

    return 0;
}
