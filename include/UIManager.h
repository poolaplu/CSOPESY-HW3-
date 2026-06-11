#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "AWindow.h"

class UIManager {
public:
    // Singleton instance
    static UIManager& getInstance() {
        static UIManager instance;
        return instance;
    }

    void registerWindow(const std::string& name, std::shared_ptr<AWindow> window) {
        windows[name] = window;
    }

    void showWindow(const std::string& name) {
        if (windows.find(name) != windows.end()) windows[name]->show();
    }

    void hideWindow(const std::string& name) {
        if (windows.find(name) != windows.end()) windows[name]->hide();
    }

    // Helper for taskbar buttons
    void toggleWindow(const std::string& name) {
        if (windows.find(name) != windows.end()) {
            if (windows[name]->isShown()) windows[name]->hide();
            else windows[name]->show();
        }
    }

    void renderAllWindows() {
        for (auto& [name, window] : windows) {
            if (window->isShown()) window->draw();
        }
    }

private:
    std::unordered_map<std::string, std::shared_ptr<AWindow>> windows;
};