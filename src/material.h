#pragma once
#include "camera.h"
#include "iostream"
#include "math.h"
#include "random.h"
#include "util.h"
#include <cmath>
#include <memory>
#include <ostream>

class AbstractMaterial {
  public:
    Vec3 color;
    virtual Vec3 Le(const Ray &wo, Vec3 x) const = 0; // light emitted
    virtual Vec3 Fr(const Ray &wi, const Ray &wo,
                    Vec3 n) const = 0; // light reflected
    virtual Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &r) = 0;
};

class MaterialDiffuse : public AbstractMaterial {
  public:
    MaterialDiffuse(const Vec3 &color) { this->color = color; }
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        Vec3 return_col = color * clamp(dot(wi.direction, n), 0, 1);
        return return_col; // light observed because of reflection
    }
    // as, most of the reflective surfaces do not emit light
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }

    Ray sample_wi(const Ray &wo, const Vec3& at,const Vec3 &n, Random &random_gen) override {
        return Ray(at + n * 1e-4f, random_gen.GenerateUniformPointHemisphere(n));
    }
};

class MaterialEmissive : public AbstractMaterial {
  public:
    MaterialEmissive(const Vec3 &color) { this->color = color; }
    // light observed because of emission
    Vec3 Le(const Ray &wi, Vec3 x) const override { return color; }
    // as, most of the emissive surfaces do not reflect
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return Vec3(0, 0, 0);
    }
    Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &random_gen) override {
        return Ray(0, Vec3(0,0,0));
    }
};

class MaterialMetallic : public AbstractMaterial {
  public:
    float p;
    MaterialMetallic(const Vec3 &color, float roughness_constant)
        : p(roughness_constant) {
        this->color = color;
    }
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return color ;
    }
    // Diffuse with probability p
    Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &random_gen) override {
        if (random_gen.GenerateUniformFloat() < p)
            return Ray(at + n * 1e-4f, random_gen.GenerateUniformPointHemisphere(n));
        else
            return reflect(wo, at, n);
    }
};

class MaterialTransmission : public AbstractMaterial {
  public:
    float mu;
    MaterialTransmission(const Vec3 &color, float refractive_index) {
        this->color = color;
        this->mu = refractive_index;
    }
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return color;
    }
    Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &random_gen) override {
        float etai_over_etat = 1/mu;
        Vec3 outward_normal = n;

        if (dot(wo.direction, outward_normal) > 0) // Inside the material
        {
            etai_over_etat = mu;
            outward_normal = -n;
        }

        return refract(wo, at, outward_normal, etai_over_etat);
    }
};

using mat_pointer = std::shared_ptr<AbstractMaterial>;
