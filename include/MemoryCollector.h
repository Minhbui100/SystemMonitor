#ifndef MEMORY_COLLECTOR_H
#define MEMORY_COLLECTOR_H

#include "Collector.h"

class MemoryCollector: public Collector{
    public:
        void update() override;
        long getUsedMB() const;
        long getTotalMB() const;
};

#endif