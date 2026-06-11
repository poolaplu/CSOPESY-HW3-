#pragma once
#include "AWindow.h"
#include <GLFW/glfw3.h> // Needed for GLuint textures

// --------------------------------------------------------
// 1. THE TASKBAR CLASS
// --------------------------------------------------------
class Taskbar : public AWindow {
public:
    Taskbar(); // Constructor declaration
    void draw() override;

private:
    // Variables to store the loaded image IDs
    GLuint sysInfoIcon = 0;
    GLuint fileExpIcon = 0;
    GLuint taskMgrIcon = 0;
    
    // Helper function to load the images
    bool loadTexture(const char* filename, GLuint* out_texture);
};

// --------------------------------------------------------
// 2. SYSTEM INFO WINDOW CLASS
// --------------------------------------------------------
class SystemInfoWindow : public AWindow {
public:
    SystemInfoWindow() : AWindow("System Information") {}
    void draw() override;
};

// --------------------------------------------------------
// 3. FILE EXPLORER WINDOW CLASS
// --------------------------------------------------------
class FileExplorerWindow : public AWindow {
public:
    FileExplorerWindow() : AWindow("File Explorer") {}
    void draw() override;
};