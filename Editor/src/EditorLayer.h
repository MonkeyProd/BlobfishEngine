#ifndef COMPOUND_EDITORLAYER_H
#define COMPOUND_EDITORLAYER_H

#include <blobfish.h>
#include "EntityEditor.h"
#include "Scene/EditorCamera.h"
#include <Scene/Serializer.h>
#include <ImGuiFileDialog.h>

using namespace bf;

class EditorLayer : public Layer {
private:
    bf::Framebuffer *m_Framebuffer;
    bf::Texture2D *m_apples;
    EntityEditor m_entityEditor;
    EditorCamera *m_camera;
    bool running = false;
    std::string m_path;

protected:
    glm::vec2 m_ViewportSize = {0, 0};
    Scene *m_scene;
public:
    EditorLayer();

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(Timestep ts) override;

    void OnImGuiRender() override;

    bool OnKeyPressedEvent(KeyPressedEvent &event) override;

private:
    void DisplayDrawStatsWindow() const;

    void DisplayViewport();

    void Save();

    void SaveAs();

    void Open();

    void NewScene();

    void Exit() const;
};


#endif //COMPOUND_EDITORLAYER_H
