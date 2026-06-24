#ifndef COLLECTOR_H
#define COLLECTOR_H

class Collector{
    public: 
        virtual void update()=0;
        virtual ~Collector()=default;
};

#endif