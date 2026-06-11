#include "ShellUI.h"
#include "UIManager.h"

void Taskbar::draw() {
    if (!isVisible) return;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    float taskbarHeight = 50.0f;
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));

    ImGuiWindowFlags taskbarFlags = ImGuiWindowFlags_NoTitleBar | 
                                    ImGuiWindowFlags_NoResize | 
                                    ImGuiWindowFlags_NoMove | 
                                    ImGuiWindowFlags_NoScrollbar | 
                                    ImGuiWindowFlags_NoSavedSettings;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));
    ImGui::Begin("Taskbar", nullptr, taskbarFlags);

    if (ImGui::Button("System Info", ImVec2(120, 30))) { 
        UIManager::getInstance().toggleWindow("SystemInfo"); 
    }
    ImGui::SameLine(); 
    if (ImGui::Button("File Explorer", ImVec2(120, 30))) { 
        UIManager::getInstance().toggleWindow("FileExplorer"); 
    }
    ImGui::SameLine();
    if (ImGui::Button("Task Manager", ImVec2(120, 30))) { 
        UIManager::getInstance().toggleWindow("TaskManager"); 
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void SystemInfoWindow::draw() {
    if (!beginWindow()) return;
    
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "CSOPESY Operating System");
    ImGui::Separator();
    
    ImGui::Text("Manufacturer: S07_GRP11");
    ImGui::Text("Creators: Widenmar Embuscado, Jandeil Dural, Luke Regaldo");
    ImGui::Text("Environment: Taft Node");
    
    ImGui::Spacing();
    ImGui::Text("Processor: AMD Ryzen 9 7950X3D 16-Core Processor");
    ImGui::Text("Memory: 65536 MB (64.0 GB) DDR5 @ 6000MT/s");
    
    ImGui::Spacing();
    ImGui::Text("Architecture: x64-based PC, UEFI Secure Boot");
    ImGui::Text("Graphics: NVIDIA GeForce RTX 4090 (24GB GDDR6X)");
    ImGui::Text("Storage: 2TB Samsung 990 PRO NVMe M.2 PCIe 4.0");
    ImGui::Text("Display: 3840x2160 (4K UHD) @ 144Hz");
    
    endWindow();
}

void FileExplorerWindow::draw() {
    if (!beginWindow()) return;
    
    ImGui::Text("C:\\CSOPESY\\Projects\\");
    ImGui::Separator();

    ImGui::BulletText("sys_boot.log");
    ImGui::BulletText("network_config.json");
    ImGui::Spacing();
    ImGui::BulletText("STADVDB_MCO_Final.zip");
    ImGui::BulletText("STINTSY_Model_Training.py");
    ImGui::BulletText("STSWENG_API_Backend.kt");
    ImGui::Spacing();
    ImGui::BulletText("Black_Myth_Wukong.exe");
    ImGui::BulletText("CivVI.exe");
    ImGui::BulletText("ARC_Raiders.exe");

    endWindow();
}