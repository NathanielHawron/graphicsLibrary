#pragma once

#include <iostream>
#include <cstdint>
#include <array>
#include <vector>

namespace graphics{
    struct Mesh{
    private:
        std::vector<float> data;
        std::vector<unsigned int> indices;
        bool empty;
    public:
        Mesh();
        Mesh(const float *vertices, const unsigned int *indices, uint32_t vertexCount, uint32_t indexCount);
        inline void reserve(uint32_t vertexCount, uint32_t indexCount){this->data.reserve(vertexCount*5);this->indices.reserve(indexCount);};
        inline void clear(){this->data.clear();this->indices.clear();};
        void add(const float *vertices, const uint32_t *indices, uint32_t vertexCount, uint32_t indexCount, float dx=0, float dy=0, float dz=0, float du=0, float dv=0);
        void add(Mesh &mesh, float dx=0, float dy=0, float dz=0, float du=0, float dv=0);
        void add(std::array<Mesh,8> *mesh, uint8_t faces = (uint8_t)0b11111111, float dx=0, float dy=0, float dz=0, float du=0, float dv=0);
        inline const float *getVertices() const {return this->data.data();};
        inline const unsigned int *getIndices() const {return this->indices.data();};
        inline uint32_t vertexCount() const {return this->data.size()/5;};
        inline uint32_t indexCount() const {return this->indices.size();};
    };
}