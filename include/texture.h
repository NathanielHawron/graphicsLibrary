#pragma once

#include <filesystem>
#include <vector>
#include <utility>

#include "glad/glad.h"

/*
    Tutorial:
    First, create image, then create texture using the image.
	(note that the graphics namespace has been removed here for clarity, but is still required):
    Image img("path to image");
    Texture texture(img)

    The texture can now be bound to any supported channel:
    texture.bind(int channel);
*/

namespace graphics{
    struct Image{
    private:
        const bool stbiFree;
    public:
        uint8_t *buffer;
        uint16_t *buffer16;
        uint32_t *buffer32;
        int width, height, bpp;
    public:
        Image(const std::filesystem::path &filepath, int bpp = 4);
        Image(int width, int height, int bpp = 4);
        ~Image();
    };
    class Texture{
    private:
        unsigned int id;
        int width, height, bpp;
    public:
        Texture(const Image &img, const std::vector<std::pair<int,int>> &texParams={{GL_TEXTURE_MIN_FILTER, GL_NEAREST},{GL_TEXTURE_MAG_FILTER, GL_NEAREST},{GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE},{GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE}});
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        inline int getWidth() const {return width;};
        inline int getHeight() const {return height;};
    };
}