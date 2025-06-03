#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <vector>
#include <string>

class MemoryMonitor {
public:
    size_t totalMemMb;
    float freeMem;
    size_t swapMemMb;
    float freeSwap;

    bool update();

    unsigned long long getTotalMemory();
    unsigned long long getFreeMemory();
    unsigned long long getTotalSwap();
    unsigned long long getUsedSwap();

    double getMemoryUsagePercentage();
    double getSwapUsagePercentage();
};

#endif
