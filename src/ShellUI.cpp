#include "ShellUI.h"
#include "UIManager.h"

// 1. Tell stb_image to create the implementation here
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// --------------------------------------------------------
// TASKBAR IMPLEMENTATION
// --------------------------------------------------------

// Taskbar Constructor
Taskbar::Taskbar() : AWindow("Taskbar") {
    isVisible = true; 
    
    // Load your actual .png files here! 
    loadTexture("sysinfo_icon.png", &sysInfoIcon);
    loadTexture("folder_icon.png", &fileExpIcon);
    loadTexture("taskmgr_icon.png", &taskMgrIcon);
}

// Texture Loader Helper
bool Taskbar::loadTexture(const char* filename, GLuint* out_texture) {
    int image_width = 0, image_height = 0, channels = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, &channels, 4);
    if (image_data == nullptr) return false;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    return true;
}

// Taskbar Draw Function
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
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(15.0f, 0.0f)); 
    
    ImGui::Begin("Taskbar", nullptr, taskbarFlags);

    if (sysInfoIcon != 0) {
        if (ImGui::ImageButton("SysInfoBtn", (void*)(intptr_t)sysInfoIcon, ImVec2(30, 30))) { 
            UIManager::getInstance().toggleWindow("SystemInfo"); 
        }
    } else {
        if (ImGui::Button("System Info", ImVec2(120, 30))) { UIManager::getInstance().toggleWindow("SystemInfo"); }
    }
    
    ImGui::SameLine(); 
    
    if (fileExpIcon != 0) {
        if (ImGui::ImageButton("FileExpBtn", (void*)(intptr_t)fileExpIcon, ImVec2(30, 30))) { 
            UIManager::getInstance().toggleWindow("FileExplorer"); 
        }
    } else {
        if (ImGui::Button("File Explorer", ImVec2(120, 30))) { UIManager::getInstance().toggleWindow("FileExplorer"); }
    }
    
    ImGui::SameLine();
    
    if (taskMgrIcon != 0) {
        if (ImGui::ImageButton("TaskMgrBtn", (void*)(intptr_t)taskMgrIcon, ImVec2(30, 30))) { 
            UIManager::getInstance().toggleWindow("TaskManager"); 
        }
    } else {
        if (ImGui::Button("Task Manager", ImVec2(120, 30))) { UIManager::getInstance().toggleWindow("TaskManager"); }
    }

    ImGui::End();
    ImGui::PopStyleVar(2); 
}

// --------------------------------------------------------
// CUSTOM APP WINDOW IMPLEMENTATIONS
// --------------------------------------------------------

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