#pragma once
#include "AWindow.h"
#include <GLFW/glfw3.h> 

class Taskbar : public AWindow {
public:
    Taskbar(GLFWwindow* window);
    void draw() override;

private:
    GLFWwindow* appWindow;

    GLuint sysInfoIcon = 0;
    GLuint fileExpIcon = 0;
    GLuint taskMgrIcon = 0;
    GLuint pwrIcon = 0;
    
    bool loadTexture(const char* filename, GLuint* out_texture);
};

class SystemInfoWindow : public AWindow {
public:
    SystemInfoWindow() : AWindow("System Information") {}
    void draw() override;
};

class FileExplorerWindow : public AWindow {
public:
    FileExplorerWindow() : AWindow("File Explorer") {}
    void draw() override;
};