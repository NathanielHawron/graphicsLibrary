#pragma once

#include <cstdint>
#include <cstring>

namespace graphics{
    namespace filters{
        void checkered(unsigned char *img, int width, int height, int bpp){
            //First, consider the image as an array of 4 byte numbers (1 byte for each: RGBA)
            uint32_t *data = (uint32_t*)img;
            //Then,, create filters using hexidecimal.
            uint32_t filter[2] = {
                0xFFFFFFFF,
                0x000000FF,
            };
            //Repeat for every pixel
            for(int i=0;i<width;++i){
                for(int j=0;j<height;++j){
                    //Every square of this pattern will be 2^5 pixels by 2^5 pixels.
                    //Use & to set colors to the minimum between the filter and the pixel value.
                    //Use | to set colors to the maximum between the filter and pixel value.
                    //Use ^ to invert every bit using the filter as a bitmask.
                    data[i + j*width] &= filter[((i>>5) + (j>>5))%2];
                }
            }
        }
        void colorMask(unsigned char *img, int width, int height, int bpp){
            //First, consider the image as an array of 4 byte numbers (1 byte for each: RGBA)
            uint32_t *data = (uint32_t*)img;
            //Then,, create filters using hexidecimal.
            uint32_t filter[4] = {
                0xFFFF00FF,
                0xFF00FFFF,
                0x00FFFFFF,
                0xFFFFFFFF
            };
            //Repeat for every pixel
            for(int i=0;i<width;++i){
                for(int j=0;j<height;++j){
                    //Every square of this pattern will be 2^4 pixels by 2^4 pixels. There are four squares in this pattern.
                    data[i + j*width] &= filter[((i>>5) + (j>>5))%4];
                }
            }
        }
        void invert(unsigned char *img, int width, int height, int bpp){
            //First, consider the image as an array of 4 byte numbers (1 byte for each: RGBA)
            uint32_t *data = (uint32_t*)img;
            //Repeat for every pixel
            for(int i=0;i<width;++i){
                for(int j=0;j<height;++j){
                    //XORing all of the color values inverts the image
                    data[i + j*width] ^= 0xFFFFFF00;
                }
            }
        }
        void edge_h(unsigned char *img, int width, int height, int bpp){
            //Move the image to a second buffer
            uint8_t *buf = new uint8_t[width*height*bpp];
            memcpy(buf,img,width*height*bpp);
            memset(img,0,width*height*bpp);

            //Select parameters for edge detection
            uint8_t jump[4] = {20,20,20,0};
            uint8_t color[4] = {200,200,200,255};

            //Loop through all pixels except for the last one on the x axis
            for(int i=1;i<width;++i){
                for(int j=0;j<height;++j){
                    //Create indices for current and next pixel
                    int index = (i-1)*bpp + j*width*bpp;
                    int nextIndex = i*bpp + j*width*bpp;
                    //Check the difference between each color of the two pixels
                    for(int k=0;k<bpp;++k){
                        if(buf[index+k]-buf[nextIndex+k]>jump[k] || buf[index+k]-buf[nextIndex+k]<-jump[k]){
                            img[index+k] = color[k];
                        }                        
                    }
                }
            }

            delete buf;
        }
        void edge_v(unsigned char *img, int width, int height, int bpp){
            uint8_t *buf = new uint8_t[width*height*bpp];
            memcpy(buf,img,width*height*bpp);
            memset(img,0,width*height*bpp);

            uint8_t jump[4] = {20,20,20,0};
            uint8_t color[4] = {200,200,200,255};

            for(int i=0;i<width;++i){
                for(int j=1;j<height;++j){
                    int index = i*bpp + (j-1)*width*bpp;
                    int nextIndex = i*bpp + j*width*bpp;
                    for(int k=0;k<bpp;++k){
                        if(buf[index+k]-buf[nextIndex+k]>jump[k] || buf[index+k]-buf[nextIndex+k]<-jump[k]){
                            img[index+k] = color[k];
                        }                        
                    }
                }
            }
            delete buf;
        }
        void edge(unsigned char *img, int width, int height, int bpp){
            uint8_t *buf = new uint8_t[width*height*bpp];
            memcpy(buf,img,width*height*bpp);
            memset(img,0,width*height*bpp);

            uint8_t jump[4] = {75,75,75,0};
            uint8_t color[4] = {200,200,200,255};

            for(int i=1;i<width;++i){
                for(int j=1;j<height;++j){
                    int index = (i-1)*bpp + (j-1)*width*bpp;
                    int nextIndexi = i*bpp + (j-1)*width*bpp;
                    int nextIndexj = (i-1)*bpp + j*width*bpp;
                    for(int k=0;k<bpp;++k){
                        if(buf[index+k]-buf[nextIndexi+k]>jump[k] || buf[index+k]-buf[nextIndexi+k]<-jump[k]){
                            img[index+k] = color[k];
                        }    
                        if(buf[index+k]-buf[nextIndexj+k]>jump[k] || buf[index+k]-buf[nextIndexj+k]<-jump[k]){
                            img[index+k] = color[k];
                        }
                    }
                }
            }

            delete buf;
        }
    }
}