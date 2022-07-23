#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

namespace bf {
    class RenderContext {
    public:
        virtual ~RenderContext() = default;

        virtual void init() = 0;

        virtual void swapBuffers() = 0;

        static RenderContext *Create(void *window);
    };
}

#endif //RENDERCONTEXT_H
