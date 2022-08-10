#ifndef COMPOUND_EDITORCAMERA_H
#define COMPOUND_EDITORCAMERA_H

#include <Scene/Components.h>
#include <Core/Timestep.h>
#include <Event/Event.h>
#include <Event/MouseEvent.h>
#include <Core/InputUtils.h>
#include <Renderer/Camera.h>

using namespace bf;

class EditorCamera : public Camera {
public:
    EditorCamera() : Camera() {}

    bf::TransformComponent Transform;

    void OnUpdate(Timestep ts, glm::vec2 &ViewportSize);

private:
    glm::vec2 m_previousMousePosition{0.0f};
    glm::vec2 m_MoveSpeed{1.0f};
    float m_ZoomSpeed{1.0f};
};


#endif //COMPOUND_EDITORCAMERA_H
