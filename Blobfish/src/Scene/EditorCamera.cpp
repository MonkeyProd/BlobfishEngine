#include "EditorCamera.h"

using namespace bf;

void EditorCamera::OnUpdate(Timestep ts, glm::vec2 &ViewportSize) {
    if (Input::IsKeyPressed(Key::LEFT_ALT)) {
        auto [x, y] = Input::GetMousePosition();
        glm::vec2 mousePos{x, y};
        auto delta = mousePos - m_previousMousePosition;
        m_previousMousePosition = mousePos;

        if (Input::IsMouseButtonPressed(1)) {
            float speed_x = std::min(ViewportSize.x / 500.0f, 2.4f); // max = 2.4f
            m_MoveSpeed.x = 0.0366f * (speed_x * speed_x) - 0.1778f * speed_x + 0.3021f;

            float speed_y = std::min(ViewportSize.y / 500.0f, 2.4f); // max = 2.4f
            m_MoveSpeed.y = 0.0366f * (speed_y * speed_y) - 0.1778f * speed_y + 0.3021f;
            Transform.Position.x -= delta.x * ts * m_MoveSpeed.x; // for some reason X is inverted. so it's -=
            Transform.Position.y += delta.y * ts * m_MoveSpeed.y;
        }
        if (Input::IsMouseButtonPressed(0)) {
            m_ZoomSpeed = std::min(ViewportSize.y / 2000.0f, 1.0f); // max = 1.0f
            m_ZoomSpeed = 0.01f * (m_ZoomSpeed * m_ZoomSpeed) - 0.1f * m_ZoomSpeed + 0.3021f;
            SetOrthographicSize(GetOrthographicSize() + delta.y * m_ZoomSpeed);
        }
    }
}
