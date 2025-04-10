#pragma once
#include "frame.h"
#include "math.h"
#include "random.h"

struct Ray {
    Vec3 origin;
    Vec3 direction;

    Ray();
    Ray(Vec3 origin, Vec3 direction); // Parameterized constructor
    // Direction must be normalized while taking in

    Vec3 at(float t) const;
    // Should return origin + t*direction;
};

static inline Ray reflect(const Ray& in, const Vec3& at, const Vec3& n)
{
    return Ray(at + 1e-4f * n, in.direction - (2 * dot(n, in.direction)) * n);
}

static inline Ray refract(const Ray& in, const Vec3& at, const Vec3& n, float eta1_eta2)
{
    float cos_i = dot(in.direction, n);
    float D = 1 - eta1_eta2 * eta1_eta2 * (1 - cos_i * cos_i);

    if (D < 0)
        return reflect(in, at, n);

    Vec3 t_perp = -std::sqrt(D) * n;
    Vec3 t_pll = eta1_eta2 * (in.direction - cos_i * n);

    return Ray(at - 1e-4f * n, (t_perp + t_pll).normalized());
}

struct Camera {
    float vertical_fov;
    int film_width, film_height;
    float focal_length;
    float z_near = 1e-6f, z_far = 1e6f;
    float aperture_size;

    Camera(float vertical_fov, int film_width, int film_height,
           float focal_length, float aperture_size);
    // Parameterized constructor

    ~Camera(); // Destructor

    Ray generate_ray(float u, float v, Random &random_gen);
    // Given NDC coordinates (u, v), should generate the corresponding ray

    void look_at(Vec3 from, Vec3 to);

    Frame frame;
    // Matrix containing transformation from world space to camera space
};
