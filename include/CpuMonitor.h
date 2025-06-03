#ifndef CPUMONITOR_H
#define CPUMONITOR_H

struct CPU {
    unsigned long long user, nice, system, idle;
};

class CpuMonitor {
public:
    short nbrCPU;
    float usagePerCPU;
    float frequency;
    float frequencyMax;
    CPU cpu;

    bool update();
    float getCpuUsage();
    float getCpuFreq();
    std::string getCpuInfo();
};

#endif
