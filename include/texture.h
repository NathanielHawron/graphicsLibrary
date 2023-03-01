#pragma once

#include <filesystem>

#include "glad/glad.h"

/*
    Tutorial:
    Create texture using constructor
	(note that the graphics namespace has been removed here for clarity, but is still required):
    Texture texture = Texure(std::filesystem::path texturePath)

    The texture can now be bound to any supported channel:
    texture.bind(int channel);
*/

namespace graphics{
    class Texture{
    private:
        unsigned int id;
        std::filesystem::path path;
        int width, height, bpp;
    public:
        typedef void (*textureCallback)(unsigned char *img, int width, int height, int bpp);
        Texture(const std::filesystem::path &path, bool flipVerticallyOnLoad = true, textureCallback cb = nullptr);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        inline int getWidth() const {return width;};
        inline int getHeight() const {return height;};
    };
}