#ifndef TEXTURE_H
#define TEXTURE_H

#include <Core/BlobPCH.h>

namespace bf{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual unsigned int GetRendererID() const = 0;

        virtual const std::string& GetPath() const = 0;

        virtual void SetData(void* data, unsigned int size) = 0;

        virtual void Bind(unsigned int slot = 0) const = 0;

        virtual bool IsLoaded() const = 0;

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        //todo CHOOSE API
        static Texture2D* Create(unsigned int width, unsigned int height);

        static Texture2D* Create(const std::string& path);
    };
}


#endif //TEXTURE_H
