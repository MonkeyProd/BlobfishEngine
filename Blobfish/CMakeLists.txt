cmake_minimum_required(VERSION 3.13)
project(blobfish)

#add_compile_definitions(TRACY_ENABLE)
add_compile_definitions(STB_IMAGE_IMPLEMENTATION)

set(CMAKE_CXX_STANDARD 20)

# Source files
# Engine
file(GLOB CORE_FILES src/Core/**.cpp src/Core/**.h)
file(GLOB EVENT_FILES src/Event/**.cpp src/Event/**.h)
file(GLOB IMGUI_FILES src/ImGui/**.cpp src/ImGui/**.h)
file(GLOB PLATFORM_FILES src/Platform/**/**.cpp src/Platform/**/**.h)
file(GLOB RENDERER_FILES src/Renderer/**.cpp src/Renderer/**.h)
file(GLOB SCENE_FILES src/Scene/**.cpp src/Scene/**.h)

file(GLOB ENGINE_SOURCE_FILES ${CORE_FILES} ${EVENT_FILES} ${IMGUI_FILES} ${PLATFORM_FILES} ${RENDERER_FILES} ${SCENE_FILES})

# External
file(GLOB GLAD_FILES extern/glad/src/glad.c)
file(GLOB IMGUI_LIB_FILES extern/imgui/**.cpp)
file(GLOB TRACY_PROFILER_FILES extern/tracy/TracyClient.cpp)
file(GLOB ENTT_FILES extern/entt/entt.hpp)

file(GLOB EXTERNAL_SOURCE_FILES ${GLAD_FILES} ${IMGUI_LIB_FILES} ${TRACY_PROFILER_FILES} ${ENTT_FILES})

# All
file(GLOB SOURCE_FILES ${ENGINE_SOURCE_FILES} ${EXTERNAL_SOURCE_FILES})

add_library(blobfish ${SOURCE_FILES})

# Includes
include_directories(extern/glad/include)
include_directories(extern/glfw/include)
include_directories(extern/spdlog/include)
include_directories(extern/imgui)
include_directories(extern/stb)
include_directories(extern/entt)
include_directories(extern/pugixml/src)
include_directories(src)

target_include_directories(blobfish PUBLIC extern/imgui extern/tracy extern/entt)

# Subdirectories
add_subdirectory(extern/glfw)
add_subdirectory(extern/spdlog)
add_subdirectory(extern/glm)
add_subdirectory(extern/tracy)
add_subdirectory(extern/pugixml)

link_directories(extern/glfw)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${TRACY_INCLUDE_DIRS} ${PUGIXML_INCLUDE_DIRS})

target_link_libraries(blobfish OpenGL::GL glfw spdlog glm Tracy::TracyClient pugixml)