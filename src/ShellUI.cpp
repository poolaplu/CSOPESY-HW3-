#include "ShellUI.h"
#include "imgui.h"

void RenderTaskbar(AppState& state) {
    // --------------------------------------------------------
    // 1. THE TASKBAR (Fixed at the bottom)
    // --------------------------------------------------------
    
    // Get the size of the main window so we can anchor the taskbar
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    float taskbarHeight = 50.0f;
    
    // Position it at the bottom left (X: 0, Y: total height - taskbar height)
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
    
    // Stretch it completely across the screen width
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));

    // Flags to make it behave like a real taskbar (no borders, no moving, no resizing)
    ImGuiWindowFlags taskbarFlags = ImGuiWindowFlags_NoTitleBar | 
                                    ImGuiWindowFlags_NoResize | 
                                    ImGuiWindowFlags_NoMove | 
                                    ImGuiWindowFlags_NoScrollbar | 
                                    ImGuiWindowFlags_NoSavedSettings;

    // Remove window padding for a cleaner look
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));

    ImGui::Begin("Taskbar", nullptr, taskbarFlags);

    // --- TASKBAR BUTTONS ---
    // If a button is clicked, we flip the boolean switch in AppState.h

    if (ImGui::Button("System Info", ImVec2(120, 30))) {
        state.showApp1 = !state.showApp1; // Toggles App 1 on/off
    }
    
    ImGui::SameLine(); // Keeps the next button on the same horizontal row
    
    if (ImGui::Button("File Explorer", ImVec2(120, 30))) {
        state.showApp2 = !state.showApp2; // Toggles App 2 on/off
    }

    ImGui::SameLine();
    
    if (ImGui::Button("Task Manager", ImVec2(120, 30))) {
        state.showTaskManager = !state.showTaskManager; // Member 3's window
    }

    ImGui::End();
    ImGui::PopStyleVar(); // Restore padding settings

    // --------------------------------------------------------
    // 2. CUSTOM APP 1: System Profiler
    // --------------------------------------------------------
    if (state.showApp1) {
        // Passing &state.showApp1 adds an 'X' close button to the top right of the window
        ImGui::Begin("System Information", &state.showApp1);
        
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "CSOPESY Operating System v1.0");
        ImGui::Separator();
        
        ImGui::Text("Manufacturer: DLSU GAME Lab");
        ImGui::Text("Creator: Dr. Neil Patrick Del Gallego");
        ImGui::Text("Environment: Taft Node");
        
        ImGui::Spacing();
        ImGui::Text("Processor: Pentium III (Emulated)");
        ImGui::Text("Memory: 64000K OK");
        
        ImGui::End();
    }

    // --------------------------------------------------------
    // 3. CUSTOM APP 2: Dummy File Explorer
    // --------------------------------------------------------
    if (state.showApp2) {
        ImGui::Begin("File Explorer", &state.showApp2);
        
        ImGui::Text("C:\\CSOPESY\\Projects\\");
        ImGui::Separator();

        // A fake list of files using ImGui Selectables
        ImGui::Selectable("  MCO_Requirements.pdf");
        ImGui::Selectable("  Task_Manager_Logic.cpp");
        ImGui::Selectable("  Background_Image.png");
        ImGui::Selectable("  secret_game.exe");

        ImGui::Spacing();
        
        // A dummy slider just to show off immediate-mode UI capabilities
        static float volume = 50.0f;
        ImGui::SliderFloat("System Volume", &volume, 0.0f, 100.0f);

        ImGui::End();
    }
}