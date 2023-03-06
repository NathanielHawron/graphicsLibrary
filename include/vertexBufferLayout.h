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
                //Floating point numbers
                case GL_HALF_FLOAT:     return sizeof(GLhalf);
                case GL_FLOAT:          return sizeof(GLfloat);
                case GL_DOUBLE:         return sizeof(GLdouble);
                //Unsigned integers
                case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
                case GL_UNSIGNED_SHORT: return sizeof(GLushort);
                case GL_UNSIGNED_INT:   return sizeof(GLuint);
                //Signed integers
                case GL_BYTE:           return sizeof(GLbyte);
                case GL_SHORT:          return sizeof(GLshort);
                case GL_INT:            return sizeof(GLint);
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