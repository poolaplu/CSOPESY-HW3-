#include "TaskManager.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <cstdlib> // For rand()

struct ProcessInfo {
    int pid;
    std::string name;
    float cpuUsage;    
    float memoryUsage; 
};

static std::vector<ProcessInfo> g_Processes = {
    { 1024, "chrome.exe", 2.5f, 412.3f },
    { 2452, "csopesy.exe", 12.1f, 85.4f }, // Fun reference to your OS class!
    { 884, "Discord.exe", 0.8f, 180.1f },
    { 4120, "svchost.exe", 0.1f, 24.0f },
    { 9132, "visualstudio.exe", 5.4f, 1204.8f }
};

// Helper function to simulate fluctuating metrics
static void UpdateProcessMetrics(std::vector<ProcessInfo>& processes) {
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


void TaskManagerWindow::draw() {
    // 1. Simulate changing values every loop cycle
    static float timer = 0.0f;
    timer += 0.02f; 
    if (timer > 1.0f) {
        UpdateProcessMetrics(g_Processes);
        timer = 0.0f;
    }

    // 2. Render Window Frame
    ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_FirstUseEver);
    
    // Pass a bool ptr if you track open/close state via 'X' button close, e.g., &this->isOpen
    if (!ImGui::Begin(windowName.c_str(), &isVisible, ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        return;
    }

    ImGui::Text("System Diagnostics - Active Processes");
    ImGui::Separator();

    // 3. ImGui Table Definition
    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY;

    if (ImGui::BeginTable("ProcessTable", 4, flags)) {
        // Setup Columns explicitly 
        ImGui::TableSetupColumn("Process Name", ImGuiTableColumnFlags_WidthFixed, 180.0f);
        ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("CPU (%)", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("Memory (MB)", ImGuiTableColumnFlags_WidthFixed, 110.0f);
        ImGui::TableHeadersRow();

        // Populate Table Body Rows
        for (const auto& proc : g_Processes) {
            ImGui::TableNextRow();

            // Column 1: Process Name
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", proc.name.c_str());

            // Column 2: PID
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", proc.pid);

            // Column 3: CPU Usage
            ImGui::TableSetColumnIndex(2);
            if (proc.cpuUsage > 10.0f) {
                // Highlight resource hogs in light orange/red
                ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.2f, 1.0f), "%.1f %%", proc.cpuUsage);
            } else {
                ImGui::Text("%.1f %%", proc.cpuUsage);
            }

            // Column 4: Memory Usage
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%.1f MB", proc.memoryUsage);
        }
        ImGui::EndTable();
    }

    ImGui::End();
}