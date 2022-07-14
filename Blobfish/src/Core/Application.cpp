//
// Created by plasm on 14.07.2022.
//

#include "Application.h"

namespace Blobfish {
    Application::Application() {
        m_window = Window::Create();
        m_window->SetEventCallback(BLOB_BIND(OnEvent));
    }

    void Application::run() {
        while (m_running) {

            float time = Time::GetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer *layer: m_layerStack) {
                layer->OnUpdate(timestep);
            }
            m_window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        BLOB_LOG_TRACE("EVENT {0}", e);
        Blobfish::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Blobfish::WindowCloseEvent>([this](Blobfish::WindowCloseEvent &) {
            m_running = false;
            return true;
        });
        dispatcher.Dispatch<Blobfish::WindowResizeEvent>([this](Blobfish::WindowResizeEvent &) {
            //TODO: RENDERER
            return false;
        });

        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it) {
            if (e.m_handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::OnUpdate() {
        //TODO: update for all layers
    }

    void Application::PushLayer(Layer *layer) {
        m_layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_layerStack.PushOverlay(layer);
    }
} // Blobfish