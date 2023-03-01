#pragma once

#include <glad/glad.h>
#include <vector>

namespace graphics{
    struct VertexBufferElement{
        unsigned int type;
        unsigned int count;
        unsigned char normalized;
        static unsigned int getSizeOfType(unsigned int type){
            switch(type){
                case GL_FLOAT:          return sizeof(GLfloat);
                case GL_UNSIGNED_INT:   return sizeof(GLuint);
                case GL_UNSIGNED_BYTE:  return sizeof(GLbyte);
            }
            return 0;
        }
    };

    class VertexBufferLayout{
    private:
        std::vector<VertexBufferElement> elements;
        unsigned int stride;
    public:
        VertexBufferLayout():stride(0){};
        void push(unsigned int type, unsigned int count){
            elements.push_back({type, count, GL_FALSE});
            stride+=count*VertexBufferElement::getSizeOfType(type);
        }

        const std::vector<VertexBufferElement> getElements()const{return elements;};
        unsigned int getStride()const{return stride;};
    };
}