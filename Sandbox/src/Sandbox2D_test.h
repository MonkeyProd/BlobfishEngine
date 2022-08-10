#ifndef COMPOUND_SANDBOX2D_TEST_H
#define COMPOUND_SANDBOX2D_TEST_H

#include <blobfish.h>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2D : public bf::Layer {
private:
    bf::Framebuffer* m_Framebuffer;
    bf::Texture2D *m_apples;
    glm::vec3 m_apple_pos;

    bf::Texture2D *m_RPGTileset;
    bf::SubTexture2D *m_LightSprites[6];
public:
    Sandbox2D();

    ~Sandbox2D() override = default;

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(bf::Timestep ts) override;

    void OnImGuiRender() override;

    void OnEvent(bf::Event &event) override;
};


#endif //COMPOUND_SANDBOX2D_TEST_H
