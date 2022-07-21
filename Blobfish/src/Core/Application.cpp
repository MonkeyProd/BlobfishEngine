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
        m_window = Window::Create({"TEST TITLE", 800, 600});
        m_window->SetEventCallback(BLOB_BIND(OnEvent));

        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);

        //vertex array
        m_vertexArray = VertexArray::Create();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.0f,
                0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f
        };

        // vertex buffer
        m_vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        m_vertexBuffer->SetLayout({
                                          {ShaderDataType::Float3, "aPos"},
                                          {ShaderDataType::Float3, "aColor"}
                                  });

        //index buffer
        unsigned int indices[3] = {0, 1, 2};
        m_indexBuffer = IndexBuffer::Create(indices, 3);

        m_vertexArray->AddVertexBuffer(m_vertexBuffer);
        m_vertexArray->SetIndexBuffer(m_indexBuffer);

        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "layout (location = 1) in vec3 aColor;\n"
                                         "out vec3 rPos;\n"
                                         "out vec3 rColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "   rPos = aPos;\n"
                                         "   rColor = aColor;\n"
                                         "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "in vec3 rPos;\n"
                                           "in vec3 rColor;\n"
                                           "uniform float iTime;\n"
                                           "uniform vec3 iColors;\n"
                                           "\n"
                                           "void main()\n"
                                           "{\n"
                                           "    FragColor = vec4(rColor.x, rColor.y, rColor.z + iColors.z * cos(iTime*2), 1.0f);\n"
                                           "}\0";
        m_shader = Shader::Create("test shader", vertexShaderSource, fragmentShaderSource);


        //BOX
        m_BoxvertexArray = VertexArray::Create();

        float verticesBOX[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
        };

        // vertex buffer
        m_BoxvertexBuffer = VertexBuffer::Create(verticesBOX, sizeof(verticesBOX));

        m_BoxvertexBuffer->SetLayout({
                                             {ShaderDataType::Float3, "aPos"}
                                     });

        //index buffer
        unsigned int indicesBOX[6] = {0, 1, 2,2,1,3};
        m_iBoxndexBuffer = IndexBuffer::Create(indicesBOX, 6);

        m_BoxvertexArray->AddVertexBuffer(m_BoxvertexBuffer);
        m_BoxvertexArray->SetIndexBuffer(m_iBoxndexBuffer);

        const char *vertexShaderSourceBOX = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";

        const char *fragmentShaderSourceBOX = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "\n"
                                           "void main()\n"
                                           "{\n"
                                           "    FragColor = vec4(0.5f, 0.3f, 0.6f, 1.0f);\n"
                                           "}\0";
        m_sBoxhader = Shader::Create("BOX shader", vertexShaderSourceBOX, fragmentShaderSourceBOX);
    }

    void Application::run() {
        while (m_running) {
            glClearColor(0.5, 0.5, 0.5, 1); //TODO
            glClear(GL_COLOR_BUFFER_BIT);

            m_sBoxhader->Bind();
            m_BoxvertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_BoxvertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            m_shader->Bind();
            m_vertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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