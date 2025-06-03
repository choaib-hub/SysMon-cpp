#include "CpuMonitor.h"
#include "MemoryMonitor.h"
#include "ProcessMonitor.h"
#include "SysMon.h"
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
    CpuMonitor cpu;
    MemoryMonitor mem;
    ProcessMonitor proc;

    while (true) {
        if (!update(cpu, mem, proc)) {
            std::cerr << "Erreur lors de la mise à jour.\n";
            break;
        }

        std::cout << getTime() << "\n";
        std::cout << cpu.getCpuInfo() << "\n\n";

        std::this_thread::sleep_for(std::chrono::seconds(updateInterval));
    }

    return 0;
}
