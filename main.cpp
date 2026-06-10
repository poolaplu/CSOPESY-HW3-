#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// --- Placeholder functions for your team's components ---
void RenderDesktop() {
    // Role 1 (Core Architect) will build the background, clock, and PWR button here.
}

void RenderTaskbar() {
    // Role 2 (Window Manager) will build the bottom taskbar and app buttons here.
}

void RenderTaskManager() {
    // Role 3 (Analyst) will build the Windows-style Task Manager table here.
}

int main() {
    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version (Adjust this depending on your target system, 3.0 is a safe baseline)
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // 2. Create the main application window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "CSOPESY Desktop OS Emulator", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // 3. Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // Setup Dear ImGui style (Dark mode by default)
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 4. The Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ==========================================
        // TEAM INJECTION POINTS - Render UI Here
        // ==========================================
        
        RenderDesktop();      // Base layer goes first
        RenderTaskbar();      // UI elements go on top
        RenderTaskManager();  // Apps and windows 

        // ==========================================

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        // Clear the screen with a solid color before drawing ImGui
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw ImGui data
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // 5. Cleanup and Shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}