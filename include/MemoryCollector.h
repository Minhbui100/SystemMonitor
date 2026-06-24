#ifndef MEMORY_COLLECTOR_H
#define MEMORY_COLLECTOR_H

#include "Collector.h"

class MemoryCollector: public Collector{
    public:
        void update() override;
        double getUsedGB() const;
        double getTotalGB() const;
        double getUsedRate() const;
    private:
        double memTotal=0.0;
        double memAvailable=0.0;
        double usedMem=0.0;
        
};

#endif