#include "SystemMonitor.h"
using namespace std;

SystemMonitor::SystemMonitor() {
    auto cpuPtr  = make_unique<CpuCollector>();
    auto memPtr  = make_unique<MemoryCollector>();
    auto tempPtr = make_unique<TempCollector>();

    cpu  = cpuPtr.get();
    mem  = memPtr.get();
    temp = tempPtr.get();

    collectors.push_back(move(cpuPtr));
    collectors.push_back(move(memPtr));
    collectors.push_back(move(tempPtr));
}

void SystemMonitor::updateAll() {
    for (auto& collector : collectors) {
        collector->update();
    }
}

double SystemMonitor::getCpuUsage() const { return cpu->getUsage(); }
double SystemMonitor::getUsedGB()   const { return mem->getUsedGB(); }
double SystemMonitor::getTotalGB()  const { return mem->getTotalGB(); }
double SystemMonitor::getTempC()    const { return temp->getTempC(); }