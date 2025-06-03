#include "../include/CpuMonitor.h"
#include <iostream>

int main() {
    CpuMonitor cpu;
    if (cpu.update()) {
        std::cout << "CPU usage: " << cpu.getCpuUsage() << "%" << std::endl;
        return 0;
    } else {
        std::cerr << "Erreur lors de la mise à jour du CPU." << std::endl;
        return 1;
    }
}
