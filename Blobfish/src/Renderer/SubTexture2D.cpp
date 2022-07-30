#include "SubTexture2D.h"

namespace bf {
    SubTexture2D::SubTexture2D(Texture2D *texture, const glm::vec2 min, const glm::vec2 max)
            : m_Texture(texture) {
        m_TextureCoordinates[0] = {min.x, min.y};
        m_TextureCoordinates[1] = {max.x, min.y};
        m_TextureCoordinates[2] = {max.x, max.y};
        m_TextureCoordinates[3] = {min.x, max.y};
    }

    Texture2D *SubTexture2D::GetTexture() const {
        return m_Texture;
    }

    const glm::vec2 *SubTexture2D::GetTextureCoordinates() const {
        return m_TextureCoordinates;
    }

    SubTexture2D *SubTexture2D::CreateFromCoordinates(Texture2D *texture,
                                                      const glm::vec2 &cords,
                                                      const glm::vec2 &cellSize,
                                                      const glm::vec2 &spriteSize) {
        glm::vec2 min = {(cords.x * cellSize.x) / texture->GetWidth(),
                         (cords.y * cellSize.y) / texture->GetHeight()};

        glm::vec2 max = {((cords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
                         ((cords.y + spriteSize.y) * cellSize.y) / texture->GetHeight()};
        return new SubTexture2D(texture, min, max);
    }
} // bf