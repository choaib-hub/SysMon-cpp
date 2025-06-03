#include "ProcessMonitor.h"
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>

bool is_number(const std::string& s) {
    for (char const& c : s) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

bool ProcessMonitor::update() {
    processes.clear();

    DIR* dir = opendir("/proc");
    if (!dir) return false;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR && is_number(entry->d_name)) {
            int pid = std::atoi(entry->d_name);
            std::string statPath = "/proc/" + std::string(entry->d_name) + "/stat";
            std::ifstream statFile(statPath);

            if (statFile.is_open()) {
                std::string name;
                char ch;
                float utime, stime;
                int i = 0;
                std::string word;

                std::getline(statFile, word, '('); // skip pid
                std::getline(statFile, name, ')');
                statFile >> std::ws;

                for (int j = 0; j < 11; ++j) statFile >> word; // skip to utime
                statFile >> utime >> stime;

                float total_time = utime + stime;
                float cpu_usage = total_time / sysconf(_SC_CLK_TCK);

                std::string statusPath = "/proc/" + std::to_string(pid) + "/status";
                std::ifstream statusFile(statusPath);
                std::string line;
                float mem_usage = 0;

                if (statusFile.is_open()) {
                    while (std::getline(statusFile, line)) {
                        if (line.find("VmRSS:") == 0) {
                            std::istringstream iss(line);
                            std::string key;
                            float value;
                            std::string unit;
                            iss >> key >> value >> unit;
                            mem_usage = value / 1024.0f; // KB -> MB
                            break;
                        }
                    }
                }

                processes.push_back({ pid, name, cpu_usage, mem_usage });
            }
        }
    }

    closedir(dir);
    return true;
}

std::vector<ActiveProcess> ProcessMonitor::getProcesses() {
    return processes;
}
