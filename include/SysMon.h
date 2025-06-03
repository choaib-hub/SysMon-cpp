#ifndef SYSMON_H
#define SYSMON_H

#include <string>

extern int updateInterval;
extern std::string exportPath;
extern bool help;

std::string exportAsText();
std::string exportAsCSV();
bool update(class CpuMonitor& cpuMon, class MemoryMonitor& memMon, class ProcessMonitor& procMon);
std::string getTime();
std::string getInfo();

#endif
