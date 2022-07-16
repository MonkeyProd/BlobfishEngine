cmake_minimum_required(VERSION 3.13)
project(blobfish)

add_definitions(-DDEBUG=1)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES extern/glad/src/glad.c src/Renderer/RenderContext.h src/Platform/OpenGL/RenderContextOpenGl.cpp src/Platform/OpenGL/RenderContextOpenGl.h src/Renderer/RenderContext.cpp src/Renderer/Shader.cpp src/Renderer/Shader.h src/Platform/OpenGL/ShaderOpenGL.cpp src/Platform/OpenGL/ShaderOpenGL.h)

file(GLOB IMGUI_LIB_FILES extern/imgui/**.cpp)
file(GLOB CORE_FILES src/Core/**.cpp core/**.h)
file(GLOB EVENT_FILES src/Event/**.cpp src/Event/**.h)
file(GLOB IMGUI_FILES src/ImGui/**.cpp src/ImGui/**.h)
file(GLOB PLATFORM_FILES src/Platform/**/**.cpp src/Platform/**/**.h)



include_directories(extern/glad/include)
include_directories(extern/glfw/include)
include_directories(extern/spdlog/include)
include_directories(extern/imgui)
include_directories(extern/glm/glm)
include_directories(src)

add_library(blobfish  ${GLAD_FILES} ${IMGUI_LIB_FILES} ${CORE_FILES} ${EVENT_FILES} ${IMGUI_FILES} ${PLATFORM_FILES})
target_include_directories(blobfish PUBLIC extern/imgui)

add_subdirectory(extern/glfw)
add_subdirectory(extern/spdlog)
add_subdirectory(extern/glm)

link_directories(extern/glfw)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(blobfish OpenGL::GL glfw spdlog)