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
        void init();
        inline unsigned int getIndexCount() const {return this->indexCount;};
        void loadVertexData(const void *vertexData, unsigned int size);
        void loadIndexData(const unsigned int *indexData, unsigned int count);
        void setVBOLayout(const VertexBufferLayout &layout);
        void bindBuffers() const;
        void unbindBuffers() const;
        void render();
    protected:
        unsigned int vao, vbo, ibo;
        unsigned int vertexCount, indexCount;
    };
}