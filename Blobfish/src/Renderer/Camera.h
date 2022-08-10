#ifndef COMPOUND_CAMERA_H
#define COMPOUND_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/BlobPCH.h"

namespace bf {

    class Camera {
    public:
        Camera() {
            RecalculateProjection();
        }

        Camera(const glm::mat4 &projection)
                : m_Projection(projection) {}

        virtual ~Camera() = default;

        const glm::mat4 &GetProjection() const { return m_Projection; }

        void SetOrthographic(float size, float nearClip, float farClip) {
            m_OrthographicSize = size;
            m_OrthographicNear = nearClip;
            m_OrthographicFar = farClip;
            RecalculateProjection();
        }

        void SetViewportSize(uint32_t width, uint32_t height) {
            m_AspectRatio = (float) width / (float) height;
            RecalculateProjection();
        }

        float GetOrthographicSize() const { return m_OrthographicSize; }

        void SetOrthographicSize(float size) {
            m_OrthographicSize = size;
            RecalculateProjection();
        }

    private:
        void RecalculateProjection() {
            float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
            float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
            float orthoBottom = -m_OrthographicSize * 0.5f;
            float orthoTop = m_OrthographicSize * 0.5f;

            m_Projection = glm::ortho(orthoLeft, orthoRight,
                                      orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
        }

        glm::mat4 m_Projection{1.0f};
        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

        float m_AspectRatio = 0.0f;
    };

} // bf

#endif //COMPOUND_CAMERA_H
