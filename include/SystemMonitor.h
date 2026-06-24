#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "CpuCollector.h"
#include "MemoryCollector.h"
#include "TempCollector.h"
#include "Collector.h"
#include <vector>
#include <memory>
using namespace std;

class SystemMonitor{
    vector<unique_ptr<Collector>> collectors;
    public:
        void updateAll();
        void addCollector(unique_ptr<Collector> c);
};

#endif