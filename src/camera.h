#pragma once
#include "math.h"
#include "Frame.h"
struct Ray {
    Vec3 origin;
    Vec3 direction;

    Ray(Vec3 origin , Vec3 direction);  // Parameterized constructor
    // Direction must be normalized while taking in

    Vec3 at(float t) const; 
    // Should return origin + t*direction;

};
class Camera {
    public:
        float vertical_fov;
        int film_width , film_height;
        float focal_length;
        float z_near = 1e-6f, z_far = 1e6f;

    Camera(float vertical_fov , int film_width , int film_height , float focal_length); 
    // Parameterized constructor

    ~Camera (); // Destructor

    Ray generate_ray(float u, float v);
    // Given NDC coordinates (u, v), should generate the corresponding ray
    
    Frame frame;
    // Matrix containing transformation from world space to camera space
}; 
