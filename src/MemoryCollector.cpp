#include "MemoryCollector.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void MemoryCollector::update(){
    ifstream file("/proc/meminfo");
    string line;
    string name;
    double value;

    while(getline(file, line)){        
        istringstream ss(line);
        ss>>name;
        ss>>value;
        if (name=="MemTotal:"){
            memTotal=value/1024/1024;//kB to GB
        }
        if (name=="MemAvailable:"){
            memAvailable=value/1024/1024;
        }
    }

    usedMem=memTotal-memAvailable; 
}
double MemoryCollector::getUsedGB() const {
    return usedMem;
}
double MemoryCollector::getTotalGB() const {
    return  memTotal;
}
double MemoryCollector::getUsedRate() const {
    return  usedMem/memTotal*100;
}