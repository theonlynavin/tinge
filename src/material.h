#pragma once
#include "camera.h"
#include "iostream"
#include "math.h"
#include "random.h"
#include "util.h"
#include <cmath>
#include <ostream>

class AbstractMaterial {
  public:
    Vec3 color;
    virtual Vec3 Le(const Ray &wo, Vec3 x) const = 0; // light emitted
    virtual Vec3 Fr(const Ray &wi, const Ray &wo,
                    Vec3 n) const = 0; // light reflected
    virtual Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &r) = 0;
};

class MaterialDiffuse : public AbstractMaterial {
  public:
    MaterialDiffuse(const Vec3 &color) { this->color = color; }
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        Vec3 return_col = color * dot(wi.direction, n);
        return return_col; // light observed because of reflection
    }
    // as, most of the reflective surfaces do not emit light
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }

    Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &random_gen) override {
        return random_gen.GenerateUniformPointHemisphere(n);
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
    Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &random_gen) override {
        return Vec3(0, 0, 0);
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
        return color;
    }
    // Diffuse with probability p
    Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &random_gen) override {
        if (random_gen.GenerateUniformFloat() < p)
            return random_gen.GenerateUniformPointHemisphere(n);
        else
            return (w_o.direction - n * 2 * dot(n, w_o.direction)).normalized();
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
        return color / mu;
    }
    Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &random_gen) override {
        float dp = dot(w_o.direction, n);

        if (dp < 0) {
            float theta = std::acos(-dp);
            float st = std::sin(theta);
            if (st / mu < 1) {
                float alpha = std::asin(st / mu);
                Vec3 perp = cross(n, cross(w_o.direction, n)).normalized();
                return -n * std::cos(alpha) + perp * std::sin(alpha);
            } else
                return (w_o.direction - n * 2 * dot(n, w_o.direction))
                    .normalized();

        } else {
            float theta = std::acos(dp);
            float st = std::sin(theta);
            if (st * mu < 1) {
                float alpha = std::asin(st * mu);
                Vec3 perp = cross(n, cross(w_o.direction, n)).normalized();
                return n * std::cos(alpha) + perp * std::sin(alpha);
            } else {
                return (w_o.direction - n * 2 * dot(n, w_o.direction))
                    .normalized();
            }
        }
    }
};

using mat_pointer = std::shared_ptr<AbstractMaterial>;
