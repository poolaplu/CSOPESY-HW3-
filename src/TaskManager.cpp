#include "TaskManager.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <cstdlib> 

struct ProcessInfo {
    int pid;
    std::string name;
    float cpuUsage;    
    float memoryUsage; 
};

static std::vector<ProcessInfo> g_Processes = {
    { 1024, "chrome.exe", 2.5f, 412.3f },
    { 2452, "csopesy.exe", 12.1f, 85.4f },
    { 884, "Discord.exe", 0.8f, 180.1f },
    { 4120, "svchost.exe", 0.1f, 24.0f },
    { 9132, "visualstudio.exe", 5.4f, 1204.8f }
};

static void UpdateProcessMetrics(std::vector<ProcessInfo>& processes) {
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


void TaskManagerWindow::draw() {
    static float timer = 0.0f;
    timer += 0.02f; 
    if (timer > 1.0f) {
        UpdateProcessMetrics(g_Processes);
        timer = 0.0f;
    }

    ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_FirstUseEver);
    
    if (!ImGui::Begin(windowName.c_str(), &isVisible, ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        return;
    }

    ImGui::Text("System Diagnostics - Active Processes");
    ImGui::Separator();

    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY;

    if (ImGui::BeginTable("ProcessTable", 4, flags)) {
        ImGui::TableSetupColumn("Process Name", ImGuiTableColumnFlags_WidthFixed, 180.0f);
        ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("CPU (%)", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("Memory (MB)", ImGuiTableColumnFlags_WidthFixed, 110.0f);
        ImGui::TableHeadersRow();

        for (const auto& proc : g_Processes) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", proc.name.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", proc.pid);

            ImGui::TableSetColumnIndex(2);
            if (proc.cpuUsage > 10.0f) {
                ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.2f, 1.0f), "%.1f %%", proc.cpuUsage);
            } else {
                ImGui::Text("%.1f %%", proc.cpuUsage);
            }

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%.1f MB", proc.memoryUsage);
        }
        ImGui::EndTable();
    }

    ImGui::End();
}