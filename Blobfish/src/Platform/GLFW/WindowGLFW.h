#ifndef WINDOWGLFW_H
#define WINDOWGLFW_H

#include "../../Core/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <Core/InputUtils.h>

namespace bf {

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

#endif //WINDOWGLFW_H
