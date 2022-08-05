#ifndef COMPOUND_EDITORLAYER_H
#define COMPOUND_EDITORLAYER_H

#include <blobfish.h>

using namespace bf;

class EditorLayer : public Layer {
private:
    bf::Framebuffer *m_Framebuffer;
    bf::OrthographicCameraController m_cameraController;
    bf::Texture2D *m_apples;
    glm::vec3 m_apple_pos;
    glm::vec2 m_ViewportSize = {0, 0};

    Entity m_test_entity;
    Entity m_apples_entity;
    Scene m_scene;
public:
    EditorLayer();

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(Timestep ts) override;

    void OnImGuiRender() override;
};


#endif //COMPOUND_EDITORLAYER_H
