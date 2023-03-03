#pragma once

#include "glm.hpp"

#include "texture.h"
#include <iostream>
#include <map>

namespace graphics{
    namespace filter{
        namespace raytracer{
            struct OriginPlane{
                glm::vec3 dir, up, side;
                int width, height;
                OriginPlane(glm::vec3 dir, glm::vec3 up, glm::vec3 side, int width, int height):dir(dir),up(up),side(side),width(width),height(height){}
                glm::vec3 getDir(int x, int y){return dir + ((float)(x-width*0.5))*side + ((float)(y-height*0.5))*up;};
            };
            struct Sphere{
                glm::vec3 pos;
                float radius;
                std::array<float, 4> color;
                bool light;
                Sphere(glm::vec3 center, float radius, float r, float g, float b, float a, bool light = false):pos(center),radius(radius),color({r,g,b,a}),light(light){};
            };
            class Ray{
            private:
                std::vector<std::array<float,4>> colors;
            public:
                glm::vec3 origin;
                glm::vec3 dir;
                Ray(glm::vec3 origin, glm::vec3 dir):colors(std::vector<std::array<float,4>>()),origin(origin),dir(dir){};
                float intersects(Sphere &s){
                    //(o.x+d.x*t-s.x)^2+(o.y+d.y*t-s.y)^2+(o.z+d.z*t-s.z)^2-r^2 = 0
                    //(d.x*t+(o.x-s.x))^2+(d.y*t+(o.y-s.y))^2+(d.z*t+(o.z-s.z))^2-r^2 = 0)
                    //(d.x*t)^2+2*(d.x*t*(o.x-s.x))+(o.x-s.x)^2 ... -r^2 = 0
                    //t^2 * (d.x^2+d.y^2+d.z^2) + 2t * (d.x*(o.x-s.x)+d.y*(o.y-s.y)+d.z*(o.z-s.z)) + (o.x-s.x)^2 + (o.y-s.y)^2 + (o.z-s.z)^2 - r^2 = 0
                    //b^2-4*a*c
                    float a = dir.x*dir.x+dir.y*dir.y+dir.z*dir.z;
                    float b = 2*(dir.x*(origin.x-s.pos.x)+dir.y*(origin.y-s.pos.y)+dir.z*(origin.z-s.pos.z));
                    float c = (origin.x-s.pos.x)*(origin.x-s.pos.x) + (origin.y-s.pos.y)*(origin.y-s.pos.y) + (origin.z-s.pos.z)*(origin.z-s.pos.z) - s.radius*s.radius;
                    float descriminant = b*b - 4.0f*a*c;
                    //std::cout << "a: " << a << " b: " << b << " c: " << c << " d: " <<descriminant << std::endl;
                    if(descriminant>=0){
                        float res = std::min(-b+std::pow(descriminant,0.5),-b-std::pow(descriminant,0.5))/(2*a);
                        if(res<0){
                            return std::max(-b+std::pow(descriminant,0.5),-b-std::pow(descriminant,0.5))/(2*a);
                        }else{
                            return res;
                        }
                    }else{
                        return -1;
                    }
                }
                void addColor(std::array<float,4> color){this->colors.push_back(color);};
                uint32_t getColor(){
                    float rayColor[4] = {1.0f,1.0f,1.0f,1.0f};
                    for(int i=this->colors.size()-1;i>=0;--i){
                        std::array<float,4> color = this->colors.at(i);
                        for(int c=0;c<3;++c){
                            rayColor[c] *= color[c];
                        }
                    }
                    uint32_t res = 0xFFFFFFFF;
                    uint8_t *resComponents = (uint8_t*)&res;
                    for(int i=0;i<3;++i){
                        resComponents[i] = 255*rayColor[i];
                    }
                    return res;
                }
                void reflect(glm::vec3 n, glm::vec3 p){
                    this->origin = p;
                    // Normalize the normal vector of the plane
                    glm::vec3 n_hat = glm::normalize(n);
    
                    // Compute the dot product between v and n_hat
                    float v_dot_nhat = glm::dot(this->dir, n_hat);
    
                    // Multiply the dot product by two
                    float scale = 2.0 * v_dot_nhat;
    
                    // Multiply the normalized normal vector by the scale factor
                    glm::vec3 n_scale = n_hat * scale;
    
                    // Subtract the scaled normal vector from the original vector
                    this->dir = this->dir - n_scale;    
                }
            };
            void render(Image &img, Sphere *spheres, std::size_t sphereCount, glm::vec3 camPos, OriginPlane op){
                for(int i=0;i<img.width;++i){
                    //std::cout << "w: " << i << std::endl;
                    for(int j=0;j<img.height;++j){
                        //std::cout << "h: " << j << std::endl;
                        glm::vec3 pixelDirection = glm::normalize(op.getDir(i,j));
                        Ray ray(camPos, pixelDirection);
                        bool hit = false;
                        bool hitLight = false;
                        int prevIndex = -1;
                        for(int d=0;d<5;++d){
                            float closestDist = FLT_MAX;
                            std::array<float, 4> closestColor;
                            int closestIndex = -1;
                            for(int s=0;s<sphereCount;++s){
                                if(prevIndex != s){
                                    float dist = ray.intersects(spheres[s]);
                                    if(dist<closestDist && dist>0){
                                        closestDist = dist;
                                        closestColor = spheres[s].color;
                                        closestIndex = s;
                                        hit = true;
                                    }
                                }
                            }
                            if(closestIndex<0){
                                break;
                            }
                            prevIndex = closestIndex;
                            glm::vec3 intersection = ray.origin + ray.dir*closestDist;
                            glm::vec3 normal = spheres[closestIndex].pos-intersection;
                            if(spheres[closestIndex].light){
                                hitLight = true;
                                float dot = glm::dot(glm::normalize(ray.dir),glm::normalize(normal));
                                ray.addColor({closestColor[0]*dot,closestColor[1]*dot,closestColor[2]*dot});
                                break;
                            }else{
                                ray.addColor(closestColor);
                            }
                            ray.reflect(normal,intersection);
                        }
                        if(hit){
                            if(hitLight){
                                img.buffer32[i+img.width*j] = ray.getColor();
                            }else{
                                float dot = glm::dot(glm::normalize(ray.dir),glm::normalize(glm::vec3(0,1,0)));
                                if(dot>0){
                                    ray.addColor({1.0f*dot,1.0f*dot,0.9f*dot,1.0f*dot});
                                    img.buffer32[i+img.width*j] = ray.getColor();
                                }else{
                                    img.buffer32[i+img.width*j] = 0xFF000000;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}