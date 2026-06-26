#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "CpuCollector.h"
#include "MemoryCollector.h"
#include "TempCollector.h"
#include "Collector.h"
#include <vector>
#include <memory>
using namespace std;

class SystemMonitor {
public:
    SystemMonitor();  
    void updateAll();

    double getCpuUsage() const;
    double getUsedGB() const;
    double getTotalGB() const;
    double getTempC() const;

private:
    std::vector<std::unique_ptr<Collector>> collectors;

    CpuCollector*    cpu;
    MemoryCollector* mem;
    TempCollector*   temp;
};

#endif
