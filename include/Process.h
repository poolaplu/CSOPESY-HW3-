#pragma once
#include <string>
#include <vector>
#include <cstdlib> // For rand()

struct ProcessInfo{
    int pid;
    std::string name;
    float cpuUsage;    // Percentage (0.0f - 100.0f)
    float memoryUsage; // In MBs
};

// Simple function to simulate fluctuating metrics
inline void UpdateProcessMetrics(std::vector<ProcessInfo>& processes) {
    for (auto& proc : processes) {
        // Random slight fluctuation between -1.5% and +1.5%
        float cpuDelta = ((rand() % 300) - 150) / 100.0f;
        proc.cpuUsage += cpuDelta;
        if (proc.cpuUsage < 0.0f) proc.cpuUsage = 0.1f;
        if (proc.cpuUsage > 100.0f) proc.cpuUsage = 99.9f;

        // Random memory fluctuation between -5MB and +5MB
        float memDelta = ((rand() % 1000) - 500) / 100.0f;
        proc.memoryUsage += memDelta;
        if (proc.memoryUsage < 1.0f) proc.memoryUsage = 1.0f;
    }
}