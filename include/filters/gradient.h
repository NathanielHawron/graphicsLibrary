#pragma once

#include <cstdint>

#include "texture.h"

namespace graphics{
    namespace filter{
        void gradient_xy(Image &img){
            uint32_t *buf = (uint32_t*)img.buffer;
            for(int i=0;i<img.width;++i){
                for(int j=0;j<img.height;++j){
                    buf[i+j*img.width] = (int)(255*(float)i/(float)img.width) | ((int)(255*(float)j/(float)img.height))<<8 | 0xFF000000;
                }
            }
        }
    }
}