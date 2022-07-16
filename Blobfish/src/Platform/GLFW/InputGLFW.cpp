//
// Created by plasm on 15.07.2022.
//
#include <Core/InputUtils.h>
#include <Core/Application.h>
#include <GLFW/glfw3.h>

bool bf::Input::IsKeyPressed(int key) {
    auto window = static_cast<GLFWwindow*>(bf::Application::getInstance()->getWindow().GetNativeWindow());
    auto status = glfwGetKey(window, key);
    return status==GLFW_PRESS or status==GLFW_REPEAT;
}

bool bf::Input::IsMouseButtonPressed(int button) {
    auto window = static_cast<GLFWwindow*>(bf::Application::getInstance()->getWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

std::pair<float, float> bf::Input::GetMousePosition() {
    auto* window = static_cast<GLFWwindow*>(bf::Application::getInstance()->getWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return std::make_pair(static_cast<float>(xpos), static_cast<float>(ypos));
}

float bf::Input::GetMouseX() {
    return std::get<0>(GetMousePosition());
}

float bf::Input::GetMouseY() {
    return std::get<1>(GetMousePosition());
}
