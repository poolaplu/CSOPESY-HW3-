#pragma once

#include <GLFW/glfw3.h>

class Desktop {
public:
    Desktop();
    ~Desktop();

    void draw(GLFWwindow* window);

private:
    unsigned int backgroundTexture;
    int backgroundWidth;
    int backgroundHeight;
    bool triedLoadingBackground;

    void loadBackground();
    void drawBackground();
    void drawClock();
};