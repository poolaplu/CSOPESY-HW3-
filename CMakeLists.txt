cmake_minimum_required(VERSION 3.10)
project(CSOPESY_Desktop_OS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find the required libraries (OpenGL and GLFW)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 2. Tell CMake where to look for Header (.h) files
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/imgui
)

# 3. Gather all ImGui source files
file(GLOB IMGUI_SOURCES "imgui/*.cpp")

# 4. Gather all of your group's source files
file(GLOB PROJECT_SOURCES "src/*.cpp")

# 5. Build the final executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${IMGUI_SOURCES})

# 6. Link everything together
target_link_libraries(${PROJECT_NAME} 
    glfw 
    OpenGL::GL 
)