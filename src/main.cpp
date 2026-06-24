#include "SystemMonitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std;

int main(){
    //SystemMonitor monitor;
    //monitor.updateAll();
    TempCollector temp;
    temp.update();


    CpuCollector cpu;
    MemoryCollector memory;
    while(true){
        cout << fixed << setprecision(2);
        cpu.update();
        cout<<"CPU: "<<cpu.getUsage()<<"%"<<endl;
        memory.update();
        cout<<"RAM: "<<memory.getUsedGB()<<" GB / "<<memory.getTotalGB()<<" GB ("<<memory.getUsedRate()<<"%)"<<endl;
        temp.update();
        cout<<"Temp: "<<temp.getTempC()<<"°C"<<endl;
        this_thread::sleep_for(chrono::seconds(1));
        

    }
    
    return 0;
}