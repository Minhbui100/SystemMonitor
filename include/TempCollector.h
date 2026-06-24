#ifndef TEMP_COLLECTOR_H
#define TEMP_COLLECTOR_H

#include "Collector.h"

class TempCollector: public Collector{
    public:
        void update() override;
        double getTempC() const;
};

#endif