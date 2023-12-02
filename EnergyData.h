#pragma once
#include <string>
#include <vector>
#include "EnergyDataPoint.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class EnergyData
{
public:
	EnergyData(const std::string& file);
	~EnergyData();
    void mergeSort(int year, string type);
    void mergeSort(int year, string type);
    void print();
    


private:
	vector<EnergyDataPoint> dataPoints; // Data Point Container
    //Methods to refine the data:
    EnergyDataPoint makeLineToDataPoint(string& line, vector<string>& headers);
    string quotRemover(string& str);
    //
};

EnergyData::EnergyData(const string& file) {
    ifstream inputFile(file);
    // Checking if file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return;
    }

    string line;
    
    getline(inputFile, line); // getting first line
    istringstream ss(line);
    // Obtaining headers of first row for CVS file:
    vector<string> headers;
    string header;
    while (getline(ss, header, ',')) {
        headers.push_back(quotRemover(header));
    }
    // Creating EnergyDataPoint object for the remaining lines
    while (std::getline(inputFile, line)) {
        dataPoints.push_back(makeLineToDataPoint(line, headers));
    }

    inputFile.close();
}

EnergyData::~EnergyData()
{
}

inline void EnergyData::print()
{
    for (EnergyDataPoint dp: dataPoints) {
        dp.print();
        cout << endl;
    }
}

inline EnergyDataPoint EnergyData::makeLineToDataPoint(string& line, vector<string>& headers)
{
    EnergyDataPoint dataPoint;
    istringstream ss(line);
    string value;

    //Obtain initial 2 Properties
    getline(ss, value, ',');
    dataPoint.State = value;
    getline(ss, value, ',');
    dataPoint.Year = stoi(quotRemover(value));

    //Obtain the rest of float properties
    int count = 2;
    while (getline(ss, value, ',')) {
        //cout << headers.at(count) << " --> " << quotRemover(value) << endl;
        dataPoint.catData[headers.at(count)] = stof(quotRemover(value));
        
        count++;
    }

    return dataPoint;
}

inline string EnergyData::quotRemover(string& str)
{
    return str.substr(1, str.length()-2);
}

    void EnergyData::mergeSort(int year, string type)
{
	vector<pair(string, float)> states;
	for(auto i:dataPoints)
	{
		if(i.Year == year)
		{
			states.push_back(make_pair(i.State,i.catData.find(type)));
		}
	}

	
}

    void EnergyData::mergeSort(int year, string type)
{
	vector<pair(string, int)> states;
}
