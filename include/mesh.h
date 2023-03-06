#pragma once

#include <iostream>
#include <cstdint>
#include <array>
#include <vector>

#include <glad/glad.h>

namespace graphics{
    namespace vertex{
        struct pos3ub_tex2us_color3ub{
            uint8_t pos[3];
            uint16_t texCoords[2];
            uint8_t col[3];
        };
        struct position2f_texture2f{
            float pos[2], texCoords[2];
        };
        struct position3f_texture2f{
            float pos[3], texCoords[2];
        };
        struct position3f_color4f{
            float pos[3];
            uint8_t col[4];
        };
        struct position3f_texture2f_normal3f{
            float pos[3], texCoords[2], norm[3];
        };
        struct position3f_texture2f_normalMap2f_color4b{
            float pos[3], texCoords[2], normMap[2];
            uint8_t col[4];
        };
        
    };
    template <class VT, class IT = GLuint>
    class Mesh{
    private:
        std::vector<VT> vertexData;
        std::vector<IT> indexData;
    public:
        Mesh();
        Mesh(const VT *vertices, const IT *indices, std::size_t vertexCount, std::size_t indexCount);
        ~Mesh();
        void reserve(std::size_t vertices, std::size_t indices);
        void add(const Mesh<VT,IT> &mesh);
        void add(const std::array<Mesh<VT,IT>, 8> &meshes, uint8_t faces);
        VT *getVertices();
        IT *getIndices();
        std::size_t getVertexCount();
        std::size_t getIndexCount();
    };

    /*
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
    };*/
}
