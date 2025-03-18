#pragma once
#include "math.h"
#include "camera.h"


class AbstractMaterial{
public:
    Vec3 color;
    virtual Vec3 Fr(Ray wi, Ray wo,Vec3 n){
    }
};

class MaterialDiffuse : public AbstractMaterial{
public:
   Vec3 Fr(Ray wi, Ray wo,Vec3 n) override {
    Vec3 return_col = color*dot(wi.direction,n);
    return return_col;
    }
};



