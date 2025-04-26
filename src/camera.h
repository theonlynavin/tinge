#pragma once
#include "frame.h"
#include "math.h"
#include "random.h"

/*****************
 * A Ray Class
 *****************/
struct Ray {
    Vec3 origin;        // Starting point of the ray
    Vec3 direction;     // Normalized direction
    Vec3 inv_dir;       // (1/dir.x, 1/dir.y, 1/dir.z), stored for convenience

    Ray();

    Ray(Vec3 origin, Vec3 direction);
    
    /***************************************
     * @brief at(t) = origin + t*direction;
     ****************************************/
    Vec3 at(float t) const;
};

/*************************************************************************
 * Generates reflected ray given a ray , normal and the point of incident
 * @param incident ray
 * @param incident point
 * @param normal ray
 * @return reflected ray
 **************************************************************************/
static inline Ray reflect(const Ray &in, const Vec3 &at, const Vec3 &n) {
    return Ray(at + 1e-4f * n, in.direction - (2 * dot(n, in.direction)) * n);
}

/*************************************************************************
 * @brief Compute the Fresnel term using Schlick's approximation
 * @param cos_theta The cosine of the angle between incident light and surface normal
 * @param refractive_index The refractive index of the dielectric material
 * @return Fresnel reflectance value
*************************************************************************/
static inline float fresnel(float cos_theta, float refractive_index) {
    float r0 = pow((1 - refractive_index) / (1 + refractive_index), 2);
    return r0 + (1 - r0) * pow(1 - cos_theta, 5);
}

/*************************************************************************
 * Generates refracted ray given a ray, normal, the point of incident and
 * relative refractive index (named badly as eta1_eta2)
 * @param in incident ray
 * @param at incident point
 * @param n surface outward normal
 * @param eta1_eta2 relative refractive index (r_incident/r_next)
 * @return refracted ray
 **************************************************************************/
static inline Ray refract(const Ray &in, const Vec3 &at, const Vec3 &n,
                          float eta1_eta2) {
    float cos_i = dot(in.direction, n);
    float D = 1 - eta1_eta2 * eta1_eta2 * (1 - cos_i * cos_i);
    
    // This checks whether there is TIR or not
    if (D < 0)
        return reflect(in, at, n);
    
    // Orthogonal decomposition method to find refracted ray
    Vec3 t_perp = -std::sqrt(D) * n;
    Vec3 t_pll = eta1_eta2 * (in.direction - cos_i * n);

    return Ray(at - 1e-4f * n, (t_perp + t_pll).normalized());
}

/*************************************************************************
 * A Camera class consisting film details and related functions
*************************************************************************/
struct Camera {
    float vertical_fov;     // Extent of observable world expressend in terms of vertical angle (in radians)
    int film_width;         // Horizontal measurement of the film (in pixels)
    int film_height;        // Vertical measurement of the film (in pixels)
    float focal_length;     // Focal length of the lens of the camera
    float aperture_size;    // Radius of the aperture of camera
    
    /*************************************************************************  
     * @param vertical_fov It is the extent of observable world expressend in terms
     * of vertical angle (in radians) 
     * @param film_width It is the horizontal measurement of the film (in pixels)
     * @param film_height It is the vertical measurement of the film (in pixels)
     * @param focal_length Focal length of the lens of the camera
     * @param aperture_size Radius of the aperture of camera
    *************************************************************************/
    Camera(float vertical_fov, int film_width, int film_height,
           float focal_length, float aperture_size);

    ~Camera(); // Destructor

    /************************************************************************
    * @brief Given NDC coordinates (u, v) generates the corresponding ray
    ************************************************************************/
    Ray generate_ray(float u, float v, Random &random_gen);
    
    /************************************************************************
    * @brief Positions the camera frame to orient in such a way that the camera
    * is placed at "from" and look towards "to"
    ************************************************************************/
    void look_at(Vec3 from, Vec3 to);
    
    Frame frame;    // Camera frame of reference
};
