#include "SysMon.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

// Déclaration des variables globales
int updateInterval = 1;
std::string exportPath = "sysmon_output.csv";
bool help = false;

std::string getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool update(CpuMonitor& cpuMon, MemoryMonitor& memMon, ProcessMonitor& procMon) {
    return cpuMon.update() && memMon.update() && procMon.update();
}

std::string exportAsText(CpuMonitor& cpu, MemoryMonitor& mem, ProcessMonitor& proc) {
    std::stringstream ss;
    ss << "Heure: " << getTime() << "\n";
    ss << cpu.getCpuInfo() << "\n";
    ss << "RAM utilisée: " << mem.getMemoryUsagePercentage() << "%\n";
    ss << "Swap utilisée: " << mem.getSwapUsagePercentage() << "%\n";
    ss << "Processus actifs:\n";
    for (auto& p : proc.getProcesses()) {
        ss << "PID: " << p.pid << " | Nom: " << p.name
           << " | CPU: " << p.cpuUsage << " | RAM: " << p.memUsage << "MB\n";
    }
    return ss.str();
}

std::string exportAsCSV(CpuMonitor& cpu, MemoryMonitor& mem, ProcessMonitor& proc) {
    std::stringstream ss;
    ss << "Time,CPU_Usage,RAM_Usage,Swap_Usage\n";
    ss << getTime() << ","
       << cpu.getCpuUsage() << ","
       << mem.getMemoryUsagePercentage() << ","
       << mem.getSwapUsagePercentage() << "\n\n";

    ss << "PID,Name,CPU,Memory(MB)\n";
    for (auto& p : proc.getProcesses()) {
        ss << p.pid << "," << p.name << "," << p.cpuUsage << "," << p.memUsage << "\n";
    }
    return ss.str();
}

std::string getInfo() {
    return "SysMon-cpp: Moniteur système léger en C++";
}
