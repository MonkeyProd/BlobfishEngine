//
// Created by plasm on 23.07.2022.
//

#include "Texture2DOpenGL.h"
#include <Tracy.hpp>
#include <stb_image.h>

namespace bf {
    Texture2DOpenGL::Texture2DOpenGL(uint32_t mWidth, uint32_t mHeight) : m_Width(mWidth), m_Height(mHeight) {
        ZoneScoped;
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    Texture2DOpenGL::Texture2DOpenGL(const std::string &mPath) : m_Path(mPath) {
        ZoneScoped;

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = nullptr;
        {
            data = stbi_load(mPath.c_str(), &width, &height, &channels, 0);
        }

        if (data) {
            m_IsLoaded = true;

            m_Width = width;
            m_Height = height;

            GLenum internalFormat = 0, dataFormat = 0;
            if (channels == 4) {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            } else if (channels == 3) {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            m_InternalFormat = internalFormat;
            m_DataFormat = dataFormat;

            BF_ASSERT(internalFormat & dataFormat, "Format not supported!");

            glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
//            glBindTexture(GL_TEXTURE_2D, m_RendererID);
            glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

            glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        } else {
            BF_LOG_WARN("ERROR WHILE LOADING TEXTURE: '{0}'", mPath);
        }
    }

    unsigned int Texture2DOpenGL::GetWidth() const {
        return m_Width;
    }

    unsigned int Texture2DOpenGL::GetHeight() const {
        return m_Height;
    }

    unsigned int Texture2DOpenGL::GetRendererID() const {
        return m_RendererID;
    }

    const std::string &Texture2DOpenGL::GetPath() const {
        return m_Path;
    }

    void Texture2DOpenGL::SetData(void *data, unsigned int size) {
        ZoneScoped;
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        BF_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void Texture2DOpenGL::Bind(unsigned int slot) const {
        ZoneScoped;
        glBindTextureUnit(slot, m_RendererID);
    }

    bool Texture2DOpenGL::IsLoaded() const {
        return m_IsLoaded;
    }

    bool Texture2DOpenGL::operator==(const Texture &other) const {
        return m_RendererID == other.GetRendererID();
    }
} // bf