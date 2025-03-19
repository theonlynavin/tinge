#pragma once
#include "math.h"
#include "camera.h"

class AbstractMaterial{
public:
    Vec3 color;
    virtual Vec3 Le(const Ray& wo, Vec3 x) const = 0;  // light emitted
    virtual Vec3 Fr(const Ray& wi, const Ray& wo, Vec3 n) const = 0; // light reflected
};

class MaterialDiffuse : public AbstractMaterial{
public:
    Vec3 Fr(const Ray& wi, const Ray& wo, Vec3 n) const override {
        Vec3 return_col = color*dot(wi.direction, n);
        return return_col; // light observed because of reflection 
    }
    Vec3 Le(const Ray& wi, Vec3 x)const override{
        return (0,0,0); // as, most of the reflective surfaces do not emit light
    }
};

class MaterialEmissive : public AbstractMaterial{
    public: 
        Vec3 Le(const Ray& wi, Vec3 x)const override{
            return color; // light observed because of emission
        }
        Vec3 Fr(const Ray& wi, const Ray& wo, Vec3 n) const override {
            return (0,0,0); // as, most of the emissive surfaces do not reflect 
        }
};
