//
// Created by plasm on 16.07.2022.
//

#ifndef COMPOUND_RENDERCONTEXT_H
#define COMPOUND_RENDERCONTEXT_H

namespace bf {
    class RenderContext {
    public:
        virtual ~RenderContext() = default;

        virtual void init() = 0;

        virtual void swapBuffers() = 0;

        static RenderContext *Create(void *window);
    };
}

#endif //COMPOUND_RENDERCONTEXT_H
