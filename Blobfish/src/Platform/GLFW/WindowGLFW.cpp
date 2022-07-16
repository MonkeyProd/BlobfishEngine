//
// Created by plasm on 14.07.2022.
//

#include "WindowGLFW.h"

namespace bf {
    WindowGLFW::WindowGLFW(const WindowProps &props) {
        m_props = props;
        m_Data.Title = props.Title;
        m_Data.Height = props.Height;
        m_Data.Width = props.Width;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_props.Width, m_props.Height, m_props.Title.c_str(), NULL, NULL);


        m_context = RenderContext::Create(m_window);
        m_context->init();


        glfwSetWindowUserPointer(m_window, &m_Data);
        SetVSync(true);

        //set callbacks

        //window callbacks
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        //key callbacks
        glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, false);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        //mouse callbacks
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event(xPos, yPos);
            data.EventCallback(event);
        });
    }

    void WindowGLFW::SetVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_Data.VSync = enabled;
    }

    bool WindowGLFW::IsVSync() const {
        return m_Data.VSync;
    }

    WindowGLFW::~WindowGLFW() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void WindowGLFW::OnUpdate() {
        glfwPollEvents();
        m_context->swapBuffers();
    }

    void WindowGLFW::SetEventCallback(const Window::EventCallbackFn &callback) {
        m_Data.EventCallback = callback;
    }

    void *WindowGLFW::GetNativeWindow() const {
        return m_window;
    }
} // Blobfish