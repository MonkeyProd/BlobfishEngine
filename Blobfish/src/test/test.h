//
// Created by xyamix on 12.07.2022.
//

#ifndef BLOBFISHENGINE_TEST_H
#define BLOBFISHENGINE_TEST_H

// GLAD
#include "glad/glad.h"

// GLFW
#include "GLFW/glfw3.h"
#include <iostream>

struct test {
// Function prototypes
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
    static const GLuint WIDTH = 800, HEIGHT = 600;

    static int run(std::string windowTitile);
};


#endif //BLOBFISHENGINE_TEST_H
