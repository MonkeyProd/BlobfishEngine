#include <blobfish.h>
#include <Tracy.hpp>

using namespace bf;

class MyLayer : public Layer {
    float *colors;
public:
    MyLayer() : Layer("My layer"), m_camera(-1.0f, 1.0f, -1.0f, 1.0f) {
        colors = new float[3];
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
                                         "uniform mat4 u_ViewProjection;\n"
                                         "out vec3 rPos;\n"
                                         "out vec3 rColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = u_ViewProjection * vec4(aPos, 1.0);\n"
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
        unsigned int indicesBOX[6] = {0, 1, 2, 2, 1, 3};
        m_iBoxndexBuffer = IndexBuffer::Create(indicesBOX, 6);

        m_BoxvertexArray->AddVertexBuffer(m_BoxvertexBuffer);
        m_BoxvertexArray->SetIndexBuffer(m_iBoxndexBuffer);

        const char *vertexShaderSourceBOX = "#version 330 core\n"
                                            "layout (location = 0) in vec3 aPos;\n"
                                            "uniform mat4 u_ViewProjection;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   gl_Position = u_ViewProjection * vec4(aPos, 1.0);\n"
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

    ~MyLayer() override = default;

    void OnAttach() override {
        BF_LOG_WARN("MY LAYER ATTACHED");
    }

    void OnDetach() override {
        BF_LOG_WARN("MY LAYER DETACHED");
    }

    void OnUpdate(Timestep ts) override {

        RenderCommand::SetClearColor({0.5, 0.5, 0.5, 1});
        RenderCommand::Clear();

        {
            if (Input::IsKeyPressed(BF_KEY_W)) {
                auto pos = m_camera.GetPosition();
                pos.y += m_cameraSpeed * ts;
                m_camera.SetPosition(pos);
            }
            if (Input::IsKeyPressed(BF_KEY_A)) {
                auto pos = m_camera.GetPosition();
                pos.x += -m_cameraSpeed * ts;
                m_camera.SetPosition(pos);
            }
            if (Input::IsKeyPressed(BF_KEY_S)) {
                auto pos = m_camera.GetPosition();
                pos.y -= m_cameraSpeed * ts;
                m_camera.SetPosition(pos);
            }
            if (Input::IsKeyPressed(BF_KEY_D)) {
                auto pos = m_camera.GetPosition();
                pos.x += m_cameraSpeed * ts;
                m_camera.SetPosition(pos);
            }
            if (Input::IsKeyPressed(BF_KEY_Q)) {
                auto rot = m_camera.GetRotation();
                rot -= m_cameraRotationSpeed * ts;
                m_camera.SetRotation(rot);
            }
            if (Input::IsKeyPressed(BF_KEY_E)) {
                auto rot = m_camera.GetRotation();
                rot += m_cameraRotationSpeed * ts;
                m_camera.SetRotation(rot);
            }
        }

        m_shader->setUniform1f("iTime", ts);

        Renderer::BeginScene(m_camera);

        Renderer::Submit(m_BoxvertexArray, m_sBoxhader);

        Renderer::Submit(m_vertexArray, m_shader);

        Renderer::EndScene();

        m_shader->setUniform3f("iColors", colors);
    }

    void OnImGuiRender() override {
        ImGui::ColorEdit3("Color edit", colors);
        ImGui::SliderFloat("speed camera", &m_cameraSpeed, 0.0f, 50.0f);
        ImGui::SliderFloat("rotation camera", &m_cameraRotationSpeed, 0.0f, 50.0f);
    }

    void OnEvent(Event &event) override {
        EventDispatcher dispatcher(event);
    }

private:
    VertexArray *m_vertexArray;
    VertexBuffer *m_vertexBuffer;
    IndexBuffer *m_indexBuffer;
    Shader *m_shader;

    VertexArray *m_BoxvertexArray;
    VertexBuffer *m_BoxvertexBuffer;
    IndexBuffer *m_iBoxndexBuffer;
    Shader *m_sBoxhader;

    OrthographicCamera m_camera;
    float m_cameraSpeed = 25.0f;
    float m_cameraRotationSpeed = 3.0f;
};

class MyApp : public Application {
public:
    MyApp() {
        PushLayer(new MyLayer);
    }
};

bf::Application *bf::create_application() {
    return new MyApp;
}