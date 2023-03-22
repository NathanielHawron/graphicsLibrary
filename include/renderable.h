#pragma once
#include "vertexBufferLayout.h"
#include "glm.hpp"

namespace graphics{
    class Renderable{
    public:
        bool renderReady;
    public:
        Renderable();
        ~Renderable();
        //Must be called in main thread
        void init();
        inline unsigned int getIndexCount() const {return this->indexCount;};
        void loadVertexData(const void *vertexData, std::size_t size);
        void loadIndexData(const GLuint *indexData, std::size_t count);
        void loadIndexData(const GLushort *indexData, std::size_t count);
        void loadIndexData(const GLubyte *indexData, std::size_t count);
        void setVBOLayout(const VertexBufferLayout &layout);
        void bindBuffers() const;
        void unbindBuffers() const;
        void render();
    protected:
        unsigned int vao, vbo, ibo;
        unsigned int vertexCount, indexCount;
        GLenum indexType;
    };
}