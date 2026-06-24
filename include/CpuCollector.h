#ifndef CPU_COLLECTOR_H
#define CPU_COLLECTOR_H

#include "Collector.h"

class CpuCollector: public Collector {
    public:
        void update() override;
        double getUsage() const;  
};

#endif