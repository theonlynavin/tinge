#pragma once
#include "camera.h"
#include "iostream"
#include "math.h"
#include "random.h"
#include "util.h"
#include <cmath>
#include <memory>
#include <ostream>

/***********************************
 * A class to store the different types of materials which are going to be used and their corresponding BRDF functions
 * ***********************************/
class AbstractMaterial {
  public:
    Vec3 color;
    /***********************************
     * @brief The virtual function for the light emitted by some material
     * @return Returns the light vector emitted by some material
     ***********************************/
    virtual Vec3 Le(const Ray &wo, Vec3 x) const = 0; // light emitted
    /***********************************
     * @brief The virtual function for light reflected by some material
     * @return Returns the color vector of the light reflected
     ***********************************/
    virtual Vec3 Fr(const Ray &wi, const Ray &wo,
                    Vec3 n) const = 0; // light reflected
     /***********************************
      * @brief The virtual function for direction of light reflected by some material
     * @param wo the incoming ray direction
     * @param at the point of incidence of the reflection, implemented to prevent floating point errors
     * @param n the normal of the object
     * @param random_gen random number generator 
     * @return Returns the direction vector of the light reflected
     ***********************************/
    virtual Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &r) = 0;
};

/***********************************
 * A class that considers diffuse material specifically and its corresponding BRDF which means that equal amount of light is reflected in all directions
 * ***********************************/
class MaterialDiffuse : public AbstractMaterial {
  public:
   /***********************************
     * @brief Material Diffuse Constructor
     * @param color the color of the diffuse material
     ***********************************/
    MaterialDiffuse(const Vec3 &color) { this->color = color; }

    /***********************************
     * @brief The light reflected in a particular direction by diffuse material
     * @return Vec 3 Color object of the reflected light which decreases for rays farther from the normal
     ***********************************/
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        Vec3 return_col = color * clamp(dot(wi.direction, n), 0, 1);
        return return_col; // light observed because of reflection
    }
    // as, most of the reflective surfaces do not emit light

    /***********************************
     * @brief Light emitted by Diffuse Object
     * @return 0 Vector, the diffuse object emits no light
     ***********************************/
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }

    /***********************************
     * @brief Generates the direction of reflected rays 
     * @param wo the incoming ray direction
     * @param at the point of incidence of the reflection, implemented to prevent floating point errors
     * @param n the normal of the object
     * @param random_gen random number generator 
     * @return A object of the Ray class pointing in a random direction chosen from the hemisphere in the outward direction of the object
     ***********************************/

    Ray sample_wi(const Ray &wo, const Vec3& at,const Vec3 &n, Random &random_gen) override {
        return Ray(at + n * 1e-4f, random_gen.GenerateUniformPointHemisphere(n));
    }
};
/***********************************
 * A class for Purely Emissive Materials, the material is considered to not reflect and purely emit
 * ***********************************/
class MaterialEmissive : public AbstractMaterial {
  public:
    /***********************************
     * @brief Material Emissive Constructor
     * @param color the color of the light emitted by the material
     ***********************************/
    MaterialEmissive(const Vec3 &color) { this->color = color; }
    // light observed because of emission
    /***********************************
     * @brief The light emitted by an emissive object
     * @return Vec 3 Color object which is the color of the light emitted
     ***********************************/
    Vec3 Le(const Ray &wi, Vec3 x) const override { return color; }
    // as, most of the emissive surfaces do not reflect
    /***********************************
     * @brief The light reflected in a particular direction by emissive material which is 0
     * @return Zero Vector as it reflects no light
     ***********************************/
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return Vec3(0, 0, 0);
    }
    /***********************************
     * @brief The rays sampled for reflection which is none since emissive material assumed to not relfect light
     * @param wo the incoming ray direction
     * @param at the point of incidence of the reflection, implemented to prevent floating point errors
     * @param n the normal of the object
     * @param random_gen random number generator 
     * @return Ray object of origin 0 and direction 0 as no light reflected
     ***********************************/
    Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &random_gen) override {
        return Ray(0, Vec3(0,0,0));
    }
};
/***********************************
 * A class for Metallic Material and its BRDF which means the material is assumed to emit no light of its own, and has a probability p to behave as diffuse and otherwise as a purely reflective material
 * ***********************************/

class MaterialMetallic : public AbstractMaterial {
  public:
    float p;
    /***********************************
     * @brief Material Emissive Constructor
     * @param color the color of the metallic object
     * @param roughtness_constant shows how rough the object it is, the more rough it is the more fraction of light will behave as diffuse reflection and less as normal reflection
     ***********************************/
    MaterialMetallic(const Vec3 &color, float roughness_constant)
        : p(roughness_constant) {
        this->color = color;
    }
    /***********************************
     * @brief The light emitted by metallic object
     * @return Returns Zero Vector since metallic object emits no light
     ***********************************/
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }
    /***********************************
     * @brief The light reflected by metallic object
     * @return Returns color vector of light reflected by metallic object
     ***********************************/
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return color ;
    }
    /***********************************
     * @brief The rays sampled for reflection by the metallic object
     * @param wo the incoming ray direction
     * @param at the point of incidence of the reflection, implemented to prevent floating point errors
     * @param n the normal of the object
     * @param random_gen random number generator 
     * @return Either a normal reflected ray or a diffuse reflected ray depending upon the random number generated
     ***********************************/
    // Diffuse with probability p
    Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &random_gen) override {
        if (random_gen.GenerateUniformFloat() < p)
            return Ray(at + n * 1e-4f, random_gen.GenerateUniformPointHemisphere(n));
        else
            return reflect(wo, at, n);
    }
};
/***********************************
 * A class for Transmissive Material, it emits no light, purely transmissive material NOT considering Schlick's approximation with partial reflection
 * ***********************************/
class MaterialTransmission : public AbstractMaterial {
  public:
    float mu;
    /***********************************
     * @brief Transmissive Material Constructor
     * @param color the color of the transmissive object
     * @param refractive_index the refractive index of the transmissive object
     ***********************************/
    MaterialTransmission(const Vec3 &color, float refractive_index) {
        this->color = color;
        this->mu = refractive_index;
    }
    /***********************************
     * @brief The light emitted by transmissive object
     * @return Returns Zero Vector since transmissive object emits no light
     ***********************************/
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }
    /***********************************
     * @brief The color of the light reflected by the transmissive object 
     * @return Vec 3 object of the color of the light reflected
     ***********************************/
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return color;
    }
    /***********************************
     * @brief Generates the rays reflected by the transmissive material
     * @param wo the incoming ray direction
     * @param at the point of incidence of the reflection, implemented to prevent floating point errors
     * @param n the normal of the object
     * @param random_gen random number generator 
     * @return The direction of the ray reflected
     ***********************************/
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
