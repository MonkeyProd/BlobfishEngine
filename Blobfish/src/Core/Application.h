//
// Created by plasm on 14.07.2022.
//
#ifndef COMPOUND_APPLICATION_H
#define COMPOUND_APPLICATION_H

#include "BlobPCH.h"
#include "../Event/Event.h"
#include "../Event/KeyEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "Timestep.h"
#include "TimeUtils.h"

#define BLOB_BIND(func) std::bind(&Application::func, this, std::placeholders::_1)

namespace Blobfish {
    class Application {
    protected:
        bool m_running = true;
        Window* m_window = nullptr;
        LayerStack m_layerStack;
        float m_LastFrameTime = 0.0f;
    public:
        Application();
        void run();
        void OnEvent(Event &e);
        void OnUpdate();
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    };

    Application *create_application();
} // Blobfish

#endif //COMPOUND_APPLICATION_H
