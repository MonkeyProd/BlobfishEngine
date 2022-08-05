#ifndef COMPOUND_FRAMEBUFFEROPENGL_H
#define COMPOUND_FRAMEBUFFEROPENGL_H

#include <Renderer/Framebuffer.h>

namespace bf {

    class FramebufferOpenGL : public Framebuffer {
    public:
        FramebufferOpenGL(const FramebufferSpecification &spec);

        virtual ~FramebufferOpenGL();

        void Invalidate();

        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual void Bind() override;

        virtual void Unbind() override;

        virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

        virtual const FramebufferSpecification &GetSpecification() const override { return m_Specification; }

    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        FramebufferSpecification m_Specification;
    };

} // bf

#endif //COMPOUND_FRAMEBUFFEROPENGL_H
