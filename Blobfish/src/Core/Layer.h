#ifndef LAYER_H
#define LAYER_H

#include "BlobPCH.h"
#include <Event/Event.h>
#include <Event/WindowEvent.h>
#include <Event/MouseEvent.h>
#include <Event/KeyEvent.h>
#include "Timestep.h"

namespace bf {

    class Layer {
    public:
        Layer(const std::string &name = "Layer") : m_DebugName(name) {}

        virtual ~Layer() = default;

        virtual void OnAttach() { BF_LOG_TRACE("Layer '{0}' attach", m_DebugName);}

        virtual void OnDetach() {BF_LOG_TRACE("Layer '{0}' detach", m_DebugName);}

        virtual void OnUpdate(Timestep ts) {}

        virtual void OnImGuiRender() {}

        void OnEventBase(Event &event) {
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<WindowCloseEvent>(BLOB_BIND(Layer, OnWindowCloseEvent));
            dispatcher.Dispatch<WindowResizeEvent>(BLOB_BIND(Layer, OnWindowResizeEvent));
            dispatcher.Dispatch<KeyPressedEvent>(BLOB_BIND(Layer, OnKeyPressedEvent));
            dispatcher.Dispatch<KeyReleasedEvent>(BLOB_BIND(Layer, OnKeyReleasedEvent));
            dispatcher.Dispatch<MouseButtonPressedEvent>(BLOB_BIND(Layer, OnMouseButtonPressedEvent));
            dispatcher.Dispatch<MouseButtonReleasedEvent>(BLOB_BIND(Layer, OnMouseButtonReleasedEvent));
            dispatcher.Dispatch<MouseMovedEvent>(BLOB_BIND(Layer, OnMouseMovedEvent));
            dispatcher.Dispatch<MouseScrolledEvent>(BLOB_BIND(Layer, OnMouseScrolledEvent));
            DispatchCustomEvents(dispatcher);
            OnEvent(event);
        }
        virtual void OnEvent(Event &event) {};
        virtual void DispatchCustomEvents(EventDispatcher &dispatcher){};
        virtual bool OnWindowCloseEvent(WindowCloseEvent& event){return false;}
        virtual bool OnWindowResizeEvent(WindowResizeEvent& event){return false;}
        virtual bool OnKeyPressedEvent(KeyPressedEvent& event){return false;}
        virtual bool OnKeyReleasedEvent(KeyReleasedEvent& event){return false;}
        virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event){return false;}
        virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event){return false;}
        virtual bool OnMouseMovedEvent(MouseMovedEvent& event){return false;}
        virtual bool OnMouseScrolledEvent(MouseScrolledEvent& event){return false;}

        const std::string &GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };

} // Blobfish

#endif //LAYER_H
