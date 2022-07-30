#ifndef COMPOUND_SUBTEXTURE2D_H
#define COMPOUND_SUBTEXTURE2D_H

#include <glm/glm.hpp>
#include "Texture.h"

namespace bf {
    //TODO smart pointers
    class SubTexture2D {
    public:
        SubTexture2D(Texture2D *texture, const glm::vec2 min, const glm::vec2 max);

        Texture2D * GetTexture() const;

        const glm::vec2 *GetTextureCoordinates() const;

        static SubTexture2D*
        CreateFromCoordinates(Texture2D *texture, const glm::vec2 &cords, const glm::vec2 &cellSize,
                              const glm::vec2 &spriteSize = glm::vec2(1.0f));

    private:
        Texture2D *m_Texture;
        glm::vec2 m_TextureCoordinates[4];
    };
} // bf

#endif //COMPOUND_SUBTEXTURE2D_H
