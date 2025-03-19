#pragma once
#include "math.h"
#include "camera.h"

class AbstractMaterial{
public:
    Vec3 color;
    virtual Vec3 Fr(const Ray& wi, const Ray& wo, Vec3 n) const = 0;
};

class MaterialDiffuse : public AbstractMaterial{
public:
    Vec3 Fr(const Ray& wi, const Ray& wo, Vec3 n) const override {
        Vec3 return_col = color*dot(wi.direction, n);
        return return_col;
    }
};



