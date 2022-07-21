//
// Created by plasm on 14.07.2022.
//

#include "Application.h"
#include <Tracy.hpp>

namespace bf {
    Application *Application::s_instance = nullptr;

    Application::Application()  {
        BF_ASSERT(not s_instance, "APPLICATION ALREADY EXISTS");
        s_instance = this;
        m_window = Window::Create({"TEST TITLE", 800, 600});
        m_window->SetEventCallback(BLOB_BIND(OnEvent));

        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);
    }

    void Application::run() {
        ZoneScoped;
        while (m_running) {
            float time = Time::GetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer *layer: m_layerStack) {
                layer->OnUpdate(timestep);
            }

            m_imGuiLayer->Begin();
            for (Layer *layer: m_layerStack) {
                layer->OnImGuiRender();
            }
            m_imGuiLayer->End();
            m_window->OnUpdate();
            FrameMark;
        }
    }

    void Application::OnEvent(Event &e) {
        ZoneScoped;
        bf::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<bf::WindowCloseEvent>([this](bf::WindowCloseEvent &) {
            m_running = false;
            return true;
        });
        dispatcher.Dispatch<bf::WindowResizeEvent>([this](bf::WindowResizeEvent &) {
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
        ZoneScoped;
        //TODO: update for all layers
    }

    void Application::PushLayer(Layer *layer) {
        ZoneScoped;
        m_layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        ZoneScoped;
        m_layerStack.PushOverlay(layer);
    }
} // Blobfish