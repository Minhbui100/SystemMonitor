#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <SystemMonitor.h>
using namespace std;

class Logger{
    public:
        Logger(const string& filename);
        void log(SystemMonitor& monitor);
    private:
        string filename;
        void writeHeader();
};

#endif