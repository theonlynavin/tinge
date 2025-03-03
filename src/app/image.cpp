#include<iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "..\..\club\stb_image_write.h"

using namespace std;





int main(){
   unsigned char* imageData = new unsigned char[1920 * 1080 * 3];
    for (size_t i = 0; i < 1920; i++)
    {
        for (size_t j = 0; j < 1080; j++)
        {
           int pxl = 1920*j+i;
           float x = i/1920.0f;
           float y = j/1080.0f;

            imageData[pxl*3+0]=255*((x*x+y*y)/2);
            imageData[pxl*3+1]=255*(x*x);
            imageData[pxl*3+2]=255*(y*y);

            
        }
        
       
    }
 stbi_write_png("output.png", 1920, 1080, 3, imageData, 1920 * 3);
    






}