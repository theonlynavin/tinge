#pragma once
#include "math.h"
class Frame{
public:
    Vec3 scale;
    Vec3 rotation;
    Vec3 origin;
    
    Frame() 
    : scale(Vec3(1,1,1)), rotation(Vec3(0,0,0)), origin(Vec3(0,0,0)) {
        
    }

    Mat4 frameToWorld, worldToFrame;

    void lockFrame()
    {
        Mat4 result;
        Mat4 sca = Transform :: scale(scale);
        Mat4 transla = Transform :: translate(origin);
        Mat4 rotat = Transform :: rotate(rotation.x, rotation.y, rotation.z);
        frameToWorld = transla * rotat * sca;
        worldToFrame = frameToWorld.inverse();
    }
};