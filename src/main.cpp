#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// NEW: Object-Oriented Architecture
#include "UIManager.h"
#include "ShellUI.h"
#include "Desktop.h"

int main() {
    // 1. Initialize GLFW
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "CSOPESY Desktop OS Emulator", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    // 2. Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    // ==========================================
    // Phase 3: Start System Services - Register Windows
    // ==========================================
    Desktop desktop;

    auto taskbar = std::make_shared<Taskbar>(window);
    auto sysInfo = std::make_shared<SystemInfoWindow>();
    auto fileExp = std::make_shared<FileExplorerWindow>();

    UIManager::getInstance().registerWindow("Taskbar", taskbar);
    UIManager::getInstance().registerWindow("SystemInfo", sysInfo);
    UIManager::getInstance().registerWindow("FileExplorer", fileExp);

    // ==========================================
    // Phase 4: The Main Render Loop
    // ==========================================
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Let the UIManager handle all registered windows!
        UIManager::getInstance().renderAllWindows();

        desktop.draw(window);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // 5. Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}