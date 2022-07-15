#include <blobfish.h>

class MyApp : public Blobfish::Application {
public:
    MyApp() {
        PushLayer(new Blobfish::Layer());
        PushOverlay(new Blobfish::ImGuiLayer());
    }
};

Blobfish::Application *Blobfish::create_application() {
    return new MyApp;
}