cmake_minimum_required(VERSION 3.13)
project(blobfish)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES extern/glad/src/glad.c)

set(SOURCE_FILES src/test/test.cpp)

include_directories(extern/glad/include)
include_directories(extern/glfw/include)

add_library(blobfish ${SOURCE_FILES} ${GLAD_FILES})

add_subdirectory(extern/glfw)

link_directories(extern/glfw)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(blobfish OpenGL::GL glfw )