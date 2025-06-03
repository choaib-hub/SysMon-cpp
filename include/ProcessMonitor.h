#ifndef PROCESSMONITOR_H
#define PROCESSMONITOR_H

#include <vector>
#include <string>

struct ActiveProcess {
    int pid;
    std::string name;
    float cpuUsage;
    float memUsage;
};

class ProcessMonitor {
public:
    std::vector<ActiveProcess> processes;

    bool update();

    std::vector<ActiveProcess> getProcesses();
};

#endif
