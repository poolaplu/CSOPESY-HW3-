#include "Desktop.h"

#include "imgui.h"
#include "stb_image.h"

#include <ctime>
#include <cstdio>
#include <cstdint>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

static const char* BACKGROUND_PATHS[] = {
    "WindowsBg.png",
    "../WindowsBg.png",
    "../../WindowsBg.png"
};

Desktop::Desktop()
    : backgroundTexture(0),
      backgroundWidth(0),
      backgroundHeight(0),
      triedLoadingBackground(false)
{
}

Desktop::~Desktop()
{
    if (backgroundTexture != 0) {
        glDeleteTextures(1, &backgroundTexture);
        backgroundTexture = 0;
    }
}

void Desktop::loadBackground()
{
    if (triedLoadingBackground) {
        return;
    }

    triedLoadingBackground = true;

    for (const char* path : BACKGROUND_PATHS) {
        int width = 0;
        int height = 0;
        int channels = 0;

        unsigned char* imageData = stbi_load(path, &width, &height, &channels, 4);

        if (imageData == nullptr) {
            continue;
        }

        glGenTextures(1, &backgroundTexture);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            imageData
        );

        stbi_image_free(imageData);

        backgroundWidth = width;
        backgroundHeight = height;

        return;
    }
}

void Desktop::drawBackground()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    ImVec2 screenPos = viewport->Pos;
    ImVec2 screenSize = viewport->Size;

    ImVec2 screenEnd(
        screenPos.x + screenSize.x,
        screenPos.y + screenSize.y
    );

    if (backgroundTexture != 0) {
        drawList->AddImage(
            (ImTextureID)(intptr_t)backgroundTexture,
            screenPos,
            screenEnd
        );
    } else {
        drawList->AddRectFilledMultiColor(
            screenPos,
            screenEnd,
            IM_COL32(20, 35, 70, 255),
            IM_COL32(20, 35, 70, 255),
            IM_COL32(5, 10, 25, 255),
            IM_COL32(5, 10, 25, 255)
        );

        for (float x = screenPos.x; x < screenEnd.x; x += 40.0f) {
            drawList->AddLine(
                ImVec2(x, screenPos.y),
                ImVec2(x, screenEnd.y),
                IM_COL32(255, 255, 255, 18)
            );
        }

        for (float y = screenPos.y; y < screenEnd.y; y += 40.0f) {
            drawList->AddLine(
                ImVec2(screenPos.x, y),
                ImVec2(screenEnd.x, y),
                IM_COL32(255, 255, 255, 18)
            );
        }
    }
}

void Desktop::drawClock()
{
    char dayName[32];
    char monthName[32];
    char timePart[32];
    char finalText[128];

    std::time_t now = std::time(nullptr);
    std::tm localTime{};

#if defined(_WIN32)
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    std::strftime(dayName, sizeof(dayName), "%A", &localTime);
    std::strftime(monthName, sizeof(monthName), "%B", &localTime);
    std::strftime(timePart, sizeof(timePart), "%I:%M %p", &localTime);

    std::snprintf(
        finalText,
        sizeof(finalText),
        "%s, %s %d, %d | %s",
        dayName,
        monthName,
        localTime.tm_mday,
        localTime.tm_year + 1900,
        timePart
    );

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    ImVec2 textSize = ImGui::CalcTextSize(finalText);

    float padding = 10.0f;
    float boxPaddingX = 12.0f;
    float boxPaddingY = 6.0f;

    ImVec2 boxMin(
        viewport->Pos.x + viewport->Size.x - textSize.x - boxPaddingX * 2.0f - padding,
        viewport->Pos.y + padding
    );

    ImVec2 boxMax(
        boxMin.x + textSize.x + boxPaddingX * 2.0f,
        boxMin.y + textSize.y + boxPaddingY * 2.0f
    );

    drawList->AddRectFilled(
        boxMin,
        boxMax,
        IM_COL32(0, 0, 0, 170),
        6.0f
    );

    drawList->AddText(
        ImVec2(boxMin.x + boxPaddingX, boxMin.y + boxPaddingY),
        IM_COL32(235, 235, 235, 255),
        finalText
    );
}

void Desktop::draw(GLFWwindow* window)
{
    (void)window;

    loadBackground();
    drawBackground();
    drawClock();
}