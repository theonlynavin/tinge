#pragma once
#include "frame.h"
#include "math.h"
#include "random.h"
/*****************
 * A Ray Class 
 *****************/
struct Ray {
    Vec3 origin;
    Vec3 direction;

    Ray();
/**************
 *  Parameterized constructor
 ************/ 
    Ray(Vec3 origin, Vec3 direction);
    // Direction must be normalized while taking in
/*************
* Should return origin + t*direction;
 **************/
    Vec3 at(float t) const;
   
};
/********
 * Generates reflected ray given a ray , normal and the point of incident
 * @par incident ray
 * @par incident point 
 * @par normal ray 
 * @return reflected ray 
 */
static inline Ray reflect(const Ray& in, const Vec3& at, const Vec3& n)
{
    return Ray(at + 1e-4f * n, in.direction - (2 * dot(n, in.direction)) * n);
}
/********
 * Generates refracted ray given a ray , normal , the point of incident and relative refractive index (named badly as eta1_eta2)
 * @par incident ray
 * @par incident point 
 * @par normal ray 
 * @return refracted ray 
 */
static inline Ray refract(const Ray& in, const Vec3& at, const Vec3& n, float eta1_eta2)
{
    float cos_i = dot(in.direction, n);
    float D = 1 - eta1_eta2 * eta1_eta2 * (1 - cos_i * cos_i);
/*************
* This checks whether there is TIR or not 
 **********/       
    if (D < 0)
        return reflect(in, at, n);
/************
* Some method to find refracted ray
 */
    Vec3 t_perp = -std::sqrt(D) * n;
    Vec3 t_pll = eta1_eta2 * (in.direction - cos_i * n);

    return Ray(at - 1e-4f * n, (t_perp + t_pll).normalized());
}
/************************
 * A Camera class consisting film details and related functions
 ************************/
struct Camera {
    float vertical_fov;
    int film_width, film_height;
    float focal_length;
    float z_near = 1e-6f, z_far = 1e6f;
    float aperture_size;
/********
 *   Parameterized constructor
 ********/
    Camera(float vertical_fov, int film_width, int film_height,
           float focal_length, float aperture_size);
   

    ~Camera(); // Destructor
/********************
 * Given NDC coordinates (u, v), should generate the corresponding ray
 *********************/
    Ray generate_ray(float u, float v, Random &random_gen);

    void look_at(Vec3 from, Vec3 to);
/**************
 * Matrix containing transformation from world space to camera space
 ****************/
    Frame frame;
   
};
