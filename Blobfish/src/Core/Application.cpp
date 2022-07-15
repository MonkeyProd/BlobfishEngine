//
// Created by plasm on 14.07.2022.
//

#include "Application.h"
#include <glad/glad.h>

namespace Blobfish {
    Application* Application::s_instance = nullptr;
    Application::Application() {
        BLOB_ASSERT(not s_instance, "APPLICATION ALREADY EXISTS");
        s_instance = this;
        m_window = Window::Create({"TEST TITLE",2000,1600});
        m_window->SetEventCallback(BLOB_BIND(OnEvent));

        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);
    }

    void Application::run() {
        while (m_running) {
            glClearColor(0.5,0.5,0.5,1); //TODO
            glClear(GL_COLOR_BUFFER_BIT);

            float time = Time::GetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer *layer: m_layerStack) {
                layer->OnUpdate(timestep);
            }

            m_imGuiLayer->Begin();
            for(Layer * layer: m_layerStack){
                layer->OnImGuiRender();
            }
            m_imGuiLayer->End();
            m_window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
//        BLOB_LOG_TRACE("EVENT {0}", e);
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