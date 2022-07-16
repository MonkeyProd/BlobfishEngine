#include <blobfish.h>

using namespace bf;

class MyLayer : public Layer {
    float *colors;
public:
    MyLayer() : Layer("My layer"){
        colors = new float[3];
    }
    ~MyLayer() override = default;

    void OnAttach() override {
        BF_LOG_WARN("MY LAYER ATTACHED");
    }

    void OnDetach() override {
        BF_LOG_WARN("MY LAYER DETACHED");
    }

    void OnUpdate(Timestep ts) override {
        if (Input::IsKeyPressed(BF_KEY_Q)) {
            BF_LOG_INFO("KEY PRESSED Q UPDATE");
        }
        Application *app = Application::getInstance();
        app->getShader().setUniform3f("iColors", colors);
    }

    void OnImGuiRender() override {
        ImGui::ColorEdit3("Color edit", colors);
    }

    void OnEvent(Event &event) override {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent &e) {
            if (e.getKeycode() == BF_KEY_Q) {
                BF_LOG_ERROR("Q PRESSED ON_EVENT");
            }
            return true;
        });
    }
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