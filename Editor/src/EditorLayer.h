#ifndef COMPOUND_EDITORLAYER_H
#define COMPOUND_EDITORLAYER_H

#include <blobfish.h>

using namespace bf;

class EditorLayer : public Layer {
private:
    bf::Framebuffer *m_Framebuffer;
    bf::OrthographicCameraController m_cameraController;
    bf::Texture2D *m_apples;
    glm::vec2 m_ViewportSize = {0, 0};

    Entity m_test_entity;
    Entity m_apples_entity;
    Scene m_scene;
    Entity m_SelectedEntity;
public:
    EditorLayer();

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(Timestep ts) override;

    void OnImGuiRender() override;
private:
    template<class T, class F>
    bool DisplayComponent(F UIfunction, const char* title);

    void DisplayDrawStatsWindow() const;

    void DisplayEntityEditorWindow();

    void DisplayViewport();
};


#endif //COMPOUND_EDITORLAYER_H
