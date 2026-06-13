#pragma once
#include <string>
#include <vector>
#include <cstdlib> 

struct ProcessInfo{
    int pid;
    std::string name;
    float cpuUsage;    
    float memoryUsage; 
};

inline void UpdateProcessMetrics(std::vector<ProcessInfo>& processes) {
    for (auto& proc : processes) {
        float cpuDelta = ((rand() % 300) - 150) / 100.0f;
        proc.cpuUsage += cpuDelta;
        if (proc.cpuUsage < 0.0f) proc.cpuUsage = 0.1f;
        if (proc.cpuUsage > 100.0f) proc.cpuUsage = 99.9f;

        float memDelta = ((rand() % 1000) - 500) / 100.0f;
        proc.memoryUsage += memDelta;
        if (proc.memoryUsage < 1.0f) proc.memoryUsage = 1.0f;
    }
}