//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_WINDOW_H
#define COMPOUND_WINDOW_H

#include "BlobPCH.h"
#include "../Event/Event.h"
#include "../Event/WindowEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"
#include <Renderer/RenderContext.h>

namespace bf {
    struct WindowProps {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string &title = "Blobfish Engine",
                    uint32_t width = 1600,
                    uint32_t height = 900)
                : Title(title), Width(width), Height(height) {
        }
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        uint32_t GetWidth() const {
            return m_props.Width;
        }

        uint32_t GetHeight() const {
            return m_props.Height;
        }

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

        virtual void SetVSync(bool enabled) = 0;

        virtual bool IsVSync() const = 0;

        virtual void *GetNativeWindow() const = 0;

        static Window *Create(const WindowProps &props = WindowProps());

    protected:
        WindowProps m_props;
        RenderContext *m_context;
    };

}

#endif //COMPOUND_WINDOW_H
