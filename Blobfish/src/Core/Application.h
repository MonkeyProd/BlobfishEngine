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
#include "InputUtils.h"
#include "ImGui/ImGuiLayer.h"
#include <Renderer/Shader.h>
#include <Renderer/Buffer.h>
#include <Renderer/VertexArray.h>

#define BLOB_BIND(func) std::bind(&Application::func, this, std::placeholders::_1)

namespace bf {
    class Application {
    protected:
        bool m_running = true;
        Window *m_window = nullptr;
        LayerStack m_layerStack;
        ImGuiLayer *m_imGuiLayer;
        float m_LastFrameTime = 0.0f;
        static Application *s_instance;

        VertexArray *m_vertexArray;
        VertexBuffer *m_vertexBuffer;
        IndexBuffer *m_indexBuffer;
        Shader *m_shader;

        VertexArray *m_BoxvertexArray;
        VertexBuffer *m_BoxvertexBuffer;
        IndexBuffer *m_iBoxndexBuffer;
        Shader *m_sBoxhader;
    public:
        Application();

        void run();

        void OnEvent(Event &e);

        void OnUpdate();

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        Window &getWindow() const { return *m_window; }

        Shader &getShader() const { return *m_shader; }

        static Application *getInstance() {
            return s_instance;
        }
    };

    Application *create_application();
} // Blobfish

#endif //COMPOUND_APPLICATION_H
