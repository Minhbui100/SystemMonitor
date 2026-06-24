#include "TempCollector.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void TempCollector::update(){
    ifstream file("/sys/class/thermal/thermal_zone0/temp");
    string line;
    getline(file, line);
    tempC=stoi(line)/1000;
}

double TempCollector::getTempC() const {
    return tempC;
}

