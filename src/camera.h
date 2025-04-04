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
