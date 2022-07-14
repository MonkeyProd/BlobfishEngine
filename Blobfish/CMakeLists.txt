cmake_minimum_required(VERSION 3.13)
project(blobfish)

add_definitions(-DDEBUG=1)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES extern/glad/src/glad.c)

set(SOURCE_FILES src/test/test.cpp src/Core/Application.cpp src/Core/Application.h src/Core/EntryPoint.h src/Core/Logger.h src/Core/Window.cpp src/Core/Window.h src/Event/Event.h src/Event/KeyEvent.h src/Event/WindowEvent.h src/Event/MouseEvent.h src/Platform/WindowGLFW.cpp src/Platform/WindowGLFW.h src/Core/Layer.h src/Core/LayerStack.h src/Core/Timestep.h src/Core/TimeUtils.h src/Platform/TimeGLFW.cpp)

include_directories(extern/glad/include)
include_directories(extern/glfw/include)
include_directories(extern/spdlog/include)

add_library(blobfish ${SOURCE_FILES} ${GLAD_FILES})

add_subdirectory(extern/glfw)
add_subdirectory(extern/spdlog)

link_directories(extern/glfw)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(blobfish OpenGL::GL glfw spdlog)