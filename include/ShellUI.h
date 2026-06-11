#pragma once
#include "AWindow.h"

class Taskbar : public AWindow {
public:
    Taskbar() : AWindow("Taskbar") {
        // The taskbar is a persistent system service, so it starts visible
        isVisible = true; 
    }
    void draw() override;
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