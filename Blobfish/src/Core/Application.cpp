//
// Created by plasm on 14.07.2022.
//

#include "Application.h"
#include <glad/glad.h>

namespace bf {
    Application *Application::s_instance = nullptr;

    Application::Application() {
        BF_ASSERT(not s_instance, "APPLICATION ALREADY EXISTS");
        s_instance = this;
        m_window = Window::Create({"TEST TITLE", 2000, 1600});
        m_window->SetEventCallback(BLOB_BIND(OnEvent));

        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);

        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "out vec3 rPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "   rPos = aPos;\n"
                                         "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "in vec3 rPos;\n"
                                           "uniform float iTime;\n"
                                           "uniform vec3 iColors;\n"
                                           "\n"
                                           "void main()\n"
                                           "{\n"
                                           "    FragColor = vec4(iColors.x*(cos(iTime)/2)+0.2, iColors.y*(cos(iTime)/2)+0.2, iColors.z*(cos(iTime)/2)+0.2, 1.0f);\n"
                                           "}\0";
        m_shader = Shader::Create("test shader", vertexShaderSource, fragmentShaderSource);

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

        float vertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        unsigned int indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    void Application::run() {
        while (m_running) {
            glClearColor(0.5, 0.5, 0.5, 1); //TODO
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->Bind();
            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            float time = Time::GetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            m_shader->setUniform1f("iTime", time);

            for (Layer *layer: m_layerStack) {
                layer->OnUpdate(timestep);
            }

            m_imGuiLayer->Begin();
            for (Layer *layer: m_layerStack) {
                layer->OnImGuiRender();
            }
            m_imGuiLayer->End();
            m_window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
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
        //TODO: update for all layers
    }

    void Application::PushLayer(Layer *layer) {
        m_layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_layerStack.PushOverlay(layer);
    }
} // Blobfish