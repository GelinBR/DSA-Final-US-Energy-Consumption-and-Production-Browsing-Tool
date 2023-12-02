#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "EnergyDataPoint.h"
#include "EnergyData.h"
using namespace std;

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

	return 0;
}