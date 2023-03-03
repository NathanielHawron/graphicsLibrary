#pragma once

#include <glad/glad.h>

#include <vector>

namespace graphics{
    class FBO{
    private:
        unsigned int fbo, rbo, tex;
        int width, height;
    public:
        FBO(int width, int height, const std::vector<std::pair<int,int>> &texParams={{GL_TEXTURE_MIN_FILTER, GL_NEAREST},{GL_TEXTURE_MAG_FILTER, GL_NEAREST},{GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE},{GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE}});
        ~FBO();
        void bind();
        void unbind();
        void bindTexture(unsigned int slot);
        void unbindTexture();
    };
}