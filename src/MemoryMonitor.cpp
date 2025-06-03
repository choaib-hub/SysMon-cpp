#include "MemoryMonitor.h"
#include <fstream>
#include <sstream>
#include <string>

bool MemoryMonitor::update() {
    std::ifstream file("/proc/meminfo");
    std::string line;
    if (!file.is_open()) return false;

    unsigned long memTotal = 0, memFree = 0, swapTotal = 0, swapFree = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        unsigned long value;
        std::string unit;

        iss >> key >> value >> unit;

        if (key == "MemTotal:") memTotal = value;
        else if (key == "MemFree:") memFree = value;
        else if (key == "SwapTotal:") swapTotal = value;
        else if (key == "SwapFree:") swapFree = value;
    }

    totalMemMb = memTotal / 1024;
    freeMem = memFree / 1024.0;
    swapMemMb = swapTotal / 1024;
    freeSwap = swapFree / 1024.0;

    return true;
}

unsigned long long MemoryMonitor::getTotalMemory() {
    return totalMemMb;
}

unsigned long long MemoryMonitor::getFreeMemory() {
    return (unsigned long long)freeMem;
}

unsigned long long MemoryMonitor::getTotalSwap() {
    return swapMemMb;
}

unsigned long long MemoryMonitor::getUsedSwap() {
    return swapMemMb - (unsigned long long)freeSwap;
}

double MemoryMonitor::getMemoryUsagePercentage() {
    if (totalMemMb == 0) return 0;
    return 100.0 * (1 - (freeMem / totalMemMb));
}

double MemoryMonitor::getSwapUsagePercentage() {
    if (swapMemMb == 0) return 0;
    return 100.0 * (1 - (freeSwap / swapMemMb));
}
