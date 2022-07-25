#include <blobfish.h>
#include <Tracy.hpp>
#include <Renderer/Texture.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Renderer/OrthographicCameraController.h>

using namespace bf;

class ExampleCustomEvent : public CustomEvent {
public:
    ExampleCustomEvent(int mData) : m_data(mData) {}

    const char *GetName() const override {
        return "My custom event";
    }

    int GetCategoryFlags() const override {
        return EventCategory::EMouse;
    }

    EventType GetEventType() const override {
        return EventType::CustomEvent;
    }

    std::string ToString() const override {
        return std::string(GetName()) + "data: " + std::to_string(m_data);
    }

private:
    int m_data;
};

class MyLayer : public Layer {
public:
    MyLayer() : Layer("My layer"), m_cameraController(1.0f, true) {
        //vertex array
        m_vertexArray = VertexArray::Create();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        // vertex buffer
        m_vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        m_vertexBuffer->SetLayout({
                                          {ShaderDataType::Float3, "aPos"},
                                          {ShaderDataType::Float3, "aTextureCord"}
                                  });

        //index buffer
        unsigned int indices[3] = {0, 1, 2};
        m_indexBuffer = IndexBuffer::Create(indices, 3);

        m_vertexArray->AddVertexBuffer(m_vertexBuffer);
        m_vertexArray->SetIndexBuffer(m_indexBuffer);

        m_shaderLibrary.Load("shader 1", "../../Sandbox/assets/shaders/triangleShader.glsl");

        //BOX
        m_BoxvertexArray = VertexArray::Create();

        float verticesBOX[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f
        };

        // vertex buffer
        m_BoxvertexBuffer = VertexBuffer::Create(verticesBOX, sizeof(verticesBOX));

        m_BoxvertexBuffer->SetLayout({
                                             {ShaderDataType::Float3, "aPos"},
                                             {ShaderDataType::Float2, "aTextureCord"}
                                     });

        //index buffer
        unsigned int indicesBOX[6] = {0, 1, 2, 2, 1, 3};
        m_iBoxndexBuffer = IndexBuffer::Create(indicesBOX, 6);

        m_BoxvertexArray->AddVertexBuffer(m_BoxvertexBuffer);
        m_BoxvertexArray->SetIndexBuffer(m_iBoxndexBuffer);

        m_shaderLibrary.Load("shader 2", "../../Sandbox/assets/shaders/boxShader.glsl");

        m_texture = Texture2D::Create("../../Sandbox/assets/chessmate.jpg");
        m_texture2 = Texture2D::Create("../../Sandbox/assets/apples.png");
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

        m_cameraController.OnUpdate(ts);

        glm::mat4 triangle_transform = glm::translate(glm::mat4(1.0f), trianglePos);
        glm::mat4 box_transform = glm::translate(glm::mat4(1.0f), boxPos);

        Renderer::BeginScene(m_cameraController.GetCamera());

        auto shader = m_shaderLibrary.Get("shader 2");
        Renderer::Submit(m_BoxvertexArray, shader, box_transform, m_texture);
        Renderer::Submit(m_BoxvertexArray, shader, triangle_transform, m_texture2);

        Renderer::EndScene();
    }

    void OnImGuiRender() override {
        ImGui::SliderFloat("speed camera", &m_cameraSpeed, 0.0f, 50.0f);
        ImGui::SliderFloat("rotation camera", &m_cameraRotationSpeed, 0.0f, 50.0f);
        ImGui::DragFloat3("triangle pos", glm::value_ptr(trianglePos), 0.1f);
        ImGui::DragFloat3("box pos", glm::value_ptr(boxPos), 0.1f);
        auto camera_pos = m_cameraController.GetCamera().GetPosition();
        ImGui::DragFloat3("camera pos", glm::value_ptr(camera_pos), 0.1f);
        m_cameraController.GetCamera().SetPosition(camera_pos);
    }

    void OnEvent(Event &event) override {
        m_cameraController.OnEvent(event);
    }

    void DispatchCustomEvents(EventDispatcher &dispatcher) override {
        dispatcher.Dispatch<ExampleCustomEvent>(BLOB_BIND(MyLayer, OnExampleCustomEvent));
    }

    bool OnExampleCustomEvent(ExampleCustomEvent &event) {
        BF_LOG_INFO("GOT EXAMPLE CUSTOM EVENT {0}", event);
        return true;
    }

    bool OnKeyPressedEvent(KeyPressedEvent &event) override {
        if (event.getKeycode() == bf::Key::C) {
            BF_LOG_DEBUG("THROWING EXAMPLE CUSTOM EVENT");
            ExampleCustomEvent e(125);
            Application::EmitEvent(e);
        }
        return true;
    }

private:
    ShaderLibrary m_shaderLibrary;
    VertexArray *m_vertexArray;
    VertexBuffer *m_vertexBuffer;
    IndexBuffer *m_indexBuffer;

    VertexArray *m_BoxvertexArray;
    VertexBuffer *m_BoxvertexBuffer;
    IndexBuffer *m_iBoxndexBuffer;

    Texture2D *m_texture;
    Texture2D *m_texture2;

    OrthographicCameraController m_cameraController;
    float m_cameraSpeed = 3.0f;
    float m_cameraRotationSpeed = 40.0f;
    glm::vec3 trianglePos;
    glm::vec3 boxPos;
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