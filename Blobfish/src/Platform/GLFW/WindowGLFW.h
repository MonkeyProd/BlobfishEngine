//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_WINDOWGLFW_H
#define COMPOUND_WINDOWGLFW_H

#include "../../Core/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <Core/InputUtils.h>

namespace Blobfish {

    class WindowGLFW : public Window {
    public:
        WindowGLFW(const WindowProps &props);

        virtual ~WindowGLFW() override;

        virtual void OnUpdate() override;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) override;

        virtual void SetVSync(bool enabled) override;

        virtual bool IsVSync() const override;

        virtual void *GetNativeWindow() const override;

    private:
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
        GLFWwindow *m_window;
    };

} // Blobfish

#endif //COMPOUND_WINDOWGLFW_H
