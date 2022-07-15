cmake_minimum_required(VERSION 3.13)
project(blobfish)

add_definitions(-DDEBUG=1)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES extern/glad/src/glad.c)

file(GLOB IMGUI_FILES extern/imgui/*.cpp)

set(SOURCE_FILES src/test/test.cpp src/Core/Application.cpp src/Core/Application.h src/Core/EntryPoint.h src/Core/Logger.h src/Core/Window.cpp src/Core/Window.h src/Event/Event.h src/Event/KeyEvent.h src/Event/WindowEvent.h src/Event/MouseEvent.h src/Platform/GLFW/WindowGLFW.cpp src/Platform/GLFW/WindowGLFW.h src/Core/Layer.h src/Core/LayerStack.h src/Core/Timestep.h src/Core/TimeUtils.h src/Platform/GLFW/TimeGLFW.cpp src/Platform/OpenGL/ImGuiOpenGL.cpp src/Platform/OpenGL/ImGuiOpenGL.h src/Platform/OpenGL/ImGuiOpenGL_loader.h src/ImGui/ImGuiLayer.cpp src/ImGui/ImGuiLayer.h src/Platform/OpenGL/ImGuiGLFW.cpp src/Platform/OpenGL/ImGuiGLFW.h src/Core/InputUtils.h src/Platform/GLFW/InputGLFW.cpp src/Core/KeyCodes.h)

include_directories(extern/glad/include)
include_directories(extern/glfw/include)
include_directories(extern/spdlog/include)
include_directories(extern/imgui)
include_directories(src)

add_library(blobfish ${SOURCE_FILES} ${GLAD_FILES} ${IMGUI_FILES})
target_include_directories(blobfish PUBLIC extern/imgui)

add_subdirectory(extern/glfw)
add_subdirectory(extern/spdlog)

link_directories(extern/glfw)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(blobfish OpenGL::GL glfw spdlog)