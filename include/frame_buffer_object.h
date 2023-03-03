#pragma once

#include <glad/glad.h>

namespace graphics{
    class FBO{
    private:
        unsigned int fbo, rbo, tex;
        int width, height;
    public:
        FBO(int width, int height);
        ~FBO();
        void bind();
        void unbind();
        void bindTexture(unsigned int slot);
        void unbindTexture();
    };
}