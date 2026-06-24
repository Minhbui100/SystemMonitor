#include "CpuCollector.h"

#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void CpuCollector::update(){
    ifstream file("/proc/stat");
    string line;
    getline(file, line);

    //cout<<line<<endl;
    istringstream ss(line);
    string cpu;
    long user, nice, system, idle, iowait, irq, softirq;
    ss>>cpu;
    ss>>user;
    ss>>nice;
    ss>>system;
    ss>>idle;
    ss>>iowait;
    ss>>irq;
    ss>>softirq;

    long total=user+ nice+ system+ idle+ iowait+ irq+ softirq;
    long totalDelta=total-prevTotal;
    long idleDelta=idle-prevIdle;

    if(totalDelta>0){
        usage=100*(totalDelta-idleDelta)/totalDelta;
    }
    prevTotal=total;
    prevIdle=idle;
}

double CpuCollector::getUsage() const {
    return usage;
}
