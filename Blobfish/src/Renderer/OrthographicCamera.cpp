//
// Created by plasm on 21.07.2022.
//

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace bf {
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_ProjectionMatrix(
            glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
        ZoneScoped;

        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }


    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
        ZoneScoped;

        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix() {

        ZoneScoped;
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
} // bf