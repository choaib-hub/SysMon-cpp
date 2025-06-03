#include "CpuMonitor.h"
#include <fstream>
#include <sstream>
#include <string>

bool CpuMonitor::update() {
    std::ifstream file("/proc/stat");
    std::string line;
    if (file.is_open() && std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cpuLabel;
        iss >> cpuLabel >> cpu.user >> cpu.nice >> cpu.system >> cpu.idle;

        unsigned long long total = cpu.user + cpu.nice + cpu.system + cpu.idle;
        usagePerCPU = 100.0f * (cpu.user + cpu.nice + cpu.system) / total;

        return true;
    }
    return false;
}

float CpuMonitor::getCpuUsage() {
    return usagePerCPU;
}

float CpuMonitor::getCpuFreq() {
    // فرضياً 2.6 GHz
    return 2.6;
}

std::string CpuMonitor::getCpuInfo() {
    return "CPU Usage: " + std::to_string(getCpuUsage()) + "%";
}
