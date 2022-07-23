#ifndef TEXTURE2DOPENGL_H
#define TEXTURE2DOPENGL_H

#include <Renderer/Texture.h>
#include <glad/glad.h>

namespace bf {

    class Texture2DOpenGL : public Texture2D {
    public:
        Texture2DOpenGL(unsigned int mWidth, unsigned int mHeight);

        Texture2DOpenGL(const std::string &mPath);

        ~Texture2DOpenGL() override = default;

        unsigned int GetWidth() const override;

        unsigned int GetHeight() const override;

        unsigned int GetRendererID() const override;

        const std::string &GetPath() const override;

        void SetData(void *data, unsigned int size) override;

        void Bind(unsigned int slot = 0) const override;

        bool IsLoaded() const override;

        bool operator==(const Texture &other) const override;

    private:
        std::string m_Path;
        bool m_IsLoaded = false;
        unsigned int m_Width, m_Height;
        unsigned int m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };

} // bf

#endif //TEXTURE2DOPENGL_H
