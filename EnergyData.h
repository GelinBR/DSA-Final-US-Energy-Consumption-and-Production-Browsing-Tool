#pragma once
#include <string>
#include <vector>
#include "EnergyDataPoint.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

class EnergyData
{
public:
    EnergyData(const std::string& file);
    ~EnergyData();
    void mergeSort(vector<pair<string, float>> &vec, int start, int end);
    void quickSort(vector<pair<string, float>> &vec, int start, int end);
    void createList(int year, string type);
    vector<pair<string, float>> states;
    void print();
    



private:
     // Data Point Container
    //Methods to refine the data:
    EnergyDataPoint makeLineToDataPoint(string& line, vector<string>& headers);
    string quotRemover(string& str);
    vector<EnergyDataPoint> dataPoints;
    //
    void merge(vector<pair<string, float>> &vec, int p, int q, int r);
    int partition(vector<pair<string, float>> &vec, int start, int end);
    int time = 0;
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
    //for (EnergyDataPoint dp : dataPoints) {
    //    dp.print();
    //    cout << endl;
    //}
    for (auto i : states)
    {
        cout << i.first << ": " << i.second << endl;
    }
    cout << "Time to sort" << clock() - time;
}

inline EnergyDataPoint EnergyData::makeLineToDataPoint(string& line, vector<string>& headers)
{
    EnergyDataPoint dataPoint;
    istringstream ss(line);
    string value;

    //Obtain initial 2 Properties
    getline(ss, value, ',');
    dataPoint.State = quotRemover(value);
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
    return str.substr(1, str.length() - 2);
}


inline void EnergyData::createList(int year, string type)
{
    for (auto i : dataPoints)
    {
        if (i.Year == year)
        {
            states.push_back(make_pair(i.State, i.catData[type]));
        }
    }
    time = clock();
}

void EnergyData::merge(vector<pair<string, float>>& vec, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<pair<string, float>> leftSubarray(vec.begin() + p, vec.begin() + p + n1);
    vector<pair<string, float>> rightSubarray(vec.begin() + q + 1, vec.begin() + q + 1 + n2);

    int i = 0;
    int j = 0;
    int k = p;

    while (i < n1 && j < n2)
    {
        if (leftSubarray[i].second <= rightSubarray[j].second)
        {
            vec[k] = leftSubarray[i];
            i++;
        }
        else
        {
            vec[k] = rightSubarray[j];
            j++;
        }

        k++;
    }

    while (i < n1) 
    {
        vec[k] = leftSubarray[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        vec[k] = rightSubarray[j];
        j++;
        k++;
    }
}

void EnergyData::mergeSort(vector<pair<string, float>> &vec, int start, int end)
{
    if (start < end) 
    {
        int mid = start + (end - start) / 2;
        mergeSort(vec, start, mid);
        mergeSort(vec, mid + 1, end);
        merge(vec, start, mid, end);
    }
}

int EnergyData::partition(vector<pair<string, float>> &vec, int start, int end)
{
    int pivotIndex = start;
    pair<string, float> pivotElement = vec[end];

    for (int i = start; i < end; i++)
    {
        if (vec[i].second < pivotElement.second)
        {
            swap(vec[i], vec[pivotIndex]);
            pivotIndex++;
        }
    }

    swap(vec[pivotIndex], vec[end]);
    return pivotIndex;
}

void EnergyData::quickSort(vector<pair<string, float>> &vec, int start, int end)
{
    if (start < end)
    {
        int partitionIndex = partition(vec, start, end);
        quickSort(vec ,start, partitionIndex - 1);
        quickSort(vec ,partitionIndex + 1, end);
    }
}
