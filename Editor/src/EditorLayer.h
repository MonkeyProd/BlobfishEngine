#ifndef COMPOUND_EDITORLAYER_H
#define COMPOUND_EDITORLAYER_H

#include <blobfish.h>

using namespace bf;

class EditorLayer : public Layer {
private:
    bf::Framebuffer *m_Framebuffer;
    bf::Texture2D *m_apples;
    glm::vec2 m_ViewportSize = {0, 0};

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
