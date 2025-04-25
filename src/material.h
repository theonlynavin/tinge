#pragma once
#include "camera.h"
#include "iostream"
#include "math.h"
#include "random.h"
#include "util.h"
#include <algorithm>
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
    float intensity = 1;

    /***********************************
     * @brief Material Emissive Constructor
     * @param color the color of the light emitted by the material
     ***********************************/
    MaterialEmissive(const Vec3 &color, float intensity) : intensity(intensity) { this->color = color; }
    // light observed because of emission
    /***********************************
     * @brief The light emitted by an emissive object
     * @return Vec 3 Color object which is the color of the light emitted
     ***********************************/
    Vec3 Le(const Ray &wi, Vec3 x) const override { return color * intensity; }
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
/***********************************
 * A class for Dielectric Material (reflective and refractive based on Fresnel equations)
 ***********************************/
class MaterialDielectric : public AbstractMaterial {
    public:
        float refractive_index;
        float roughness;
        float s; // Specular component weight
    
        /***********************************
         * @brief Material Dielectric Constructor
         * @param color The diffuse color of the dielectric material
         * @param refractive_index The refractive index of the material
         * @param roughness Controls the microfacet roughness (0: smooth, 1: rough)
         ***********************************/
        MaterialDielectric(const Vec3 &color, const Vec3 &specular_color,
                           float refractive_index, float roughness)
            : refractive_index(refractive_index), roughness(roughness) {
            this->color = color;
        }
    
        /***********************************
         * @brief The light emitted by a dielectric material
         * @return Returns Zero Vector as dielectric materials emit no light
         ***********************************/
        Vec3 Le(const Ray &wi, Vec3 x) const override {
            return Vec3(0, 0, 0);
        }
    
        /***********************************
         * @brief Compute the Fresnel term using Schlick's approximation
         * @param cos_theta The cosine of the angle between incident light and surface normal
         * @param refractive_index The refractive index of the dielectric material
         * @return Fresnel reflectance value
         ***********************************/
        float Fresnel(float cos_theta, float refractive_index) const {
            float r0 = pow((1 - refractive_index) / (1 + refractive_index), 2);
            return r0 + (1 - r0) * pow(1 - cos_theta, 5);
        }
    
        /***********************************
         * @brief GGX Normal Distribution Function (NDF) for microfacet distribution
         * @param cos_thetah Cosine of the angle between the normal and halfway vector
         * @param roughness Surface roughness of the material
         * @return Distribution factor for microfacets
         ***********************************/
        float GGX_D(float cos_thetah, float roughness) const {
            float alpha2 = roughness * roughness;
            float denom = cos_thetah * cos_thetah * (alpha2 - 1) + 1;
            return alpha2 / (M_PI * denom * denom);
        }
    
        /***********************************
         * @brief Geometric Attenuation function
         * @param cos_theta_in Cosine of angle between incident light and surface normal
         * @param cos_theta_out Cosine of angle between outgoing light and surface normal
         * @param n_dot_h Dot product of normal and halfway vector
         * @param wo_dot_h Dot product of outgoing light direction and halfway vector
         * @return Geometric attenuation factor
         ***********************************/
        float Geometric_Attenuation(float cos_theta_in, float cos_theta_out, float n_dot_h, float wo_dot_h) const {
            float g1 = (2 * n_dot_h * cos_theta_out) / wo_dot_h;
            float g2 = (2 * n_dot_h * cos_theta_in) / wo_dot_h;
            return std::min(1.0f, std::min(g1, g2));
        }
    
        /***********************************
         * @brief The Cook-Torrance BRDF function for dielectric materials
         * @return The combined reflected and transmitted color
         ***********************************/
        Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
            float cos_theta_out = clamp(dot(n, -wo.direction), 0.0f, 1.0f);
            float cos_theta_in = clamp(dot(n, wi.direction), 0.0f, 1.0f);
            
            Vec3 temp = wi.direction - wo.direction;
            Vec3 h = normalize(temp);
    
            float wo_dot_h = clamp(dot(-wo.direction, h), 0.0f, 1.0f);
            float n_dot_h = clamp(dot(n, h), 0.0f, 1.0f);
    
            // Compute GGX, Geometric Attenuation, and Fresnel terms
            float D = GGX_D(n_dot_h, roughness);
            float G = Geometric_Attenuation(cos_theta_in, cos_theta_out, n_dot_h, wo_dot_h);
            float F = Fresnel(wo_dot_h, refractive_index);
    
            // Specular reflection based on microfacet model
            Vec3 specular = s * color * (D * G * F / (4 * cos_theta_out));
    
            // Diffuse reflection component
            Vec3 diffuse = (1 - s) * color * clamp(dot(wi.direction, n), 0, 1) / M_PI;
    
            return diffuse + specular;
        }
        /***********************************
         * @brief Generates the rays reflected by the dielectric material
         * @param wo the incoming ray direction
         * @param at the point of incidence of the reflection, implemented to prevent floating point errors
         * @param n the normal of the object
         * @param random_gen random number generator 
         * @return The direction of the ray reflected
         ***********************************/
       Ray sample_wi(const Ray &wo, const Vec3& at, const Vec3 &n, Random &random_gen) override {
          float cos_theta = clamp(dot(wo.direction, n), 0.0f, 1.0f);
          float F = Fresnel(cos_theta, refractive_index);

        if (random_gen.GenerateUniformFloat() < s * F) {
          // Importance sample half-vector h from GGX
        Vec3 h = random_gen.GenerateImportanceSampleGGX(n, roughness); // You need to define this
        Vec3 dir = reflect(-wo.direction, h); // Reflect wo about h
        if (dot(dir, n) <= 0.0f) // Ensure valid reflection
            return Ray(at, Vec3(0)); // Discard or return black ray

            return Ray(at + dir * 1e-4f, dir);
        }  else {
            Vec3 dir = random_gen.GenerateCosineWeightedHemisphere(n); // Cosine-weighted sampling
            return Ray(at + dir * 1e-4f, dir);
          }
      }
  };    

    using mat_pointer = std::shared_ptr<AbstractMaterial>;
