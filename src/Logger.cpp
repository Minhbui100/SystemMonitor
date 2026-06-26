#include "Logger.h"
#include "SystemMonitor.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <chrono>

using namespace std;

Logger::Logger(const string& filename): filename(filename){
    writeHeader();
}

void Logger::writeHeader(){
    ifstream check(filename);
    if(!check.good()){
        ofstream file(filename);
        file<<"timestamp,cpu_pct,mem_used_gb,mem_total_gb,temp_c"<<endl;
    }
}

void Logger::log(SystemMonitor& monitor){
    auto now=chrono::system_clock::now();
    time_t t=chrono::system_clock::to_time_t(now);
    ostringstream timestamp;
    timestamp<<put_time(localtime(&t), "%Y-%m-%dT%H:%M:%S");

    ofstream file(filename, ios::app);

    file<<fixed<<setprecision(1);
    file<<timestamp.str()<<","
        <<monitor.getCpuUsage()<<","
        <<monitor.getUsedGB()<<","
        <<monitor.getTotalGB()<<","
        <<monitor.getTempC()<<endl;



}