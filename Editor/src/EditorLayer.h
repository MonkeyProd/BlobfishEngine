#ifndef COMPOUND_EDITORLAYER_H
#define COMPOUND_EDITORLAYER_H

#include <blobfish.h>
#include "EntityEditor.h"
#include "Scene/EditorCamera.h"

using namespace bf;

class EditorLayer : public Layer {
private:
    bf::Framebuffer *m_Framebuffer;
    bf::Texture2D *m_apples;
    EntityEditor m_entityEditor;
    EditorCamera *m_camera;
    bool running = false;

protected:
    glm::vec2 m_ViewportSize = {0, 0};
    Scene m_scene;
public:
    EditorLayer();

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(Timestep ts) override;

    void OnImGuiRender() override;

private:
    void DisplayDrawStatsWindow() const;

    void DisplayViewport();
};


#endif //COMPOUND_EDITORLAYER_H
