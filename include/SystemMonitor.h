#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "CpuCollector.h"
#include "MemoryCollector.h"
#include "TempCollector.h"

class SystemMonitor{
    public:
        void updateAll();
};

#endif