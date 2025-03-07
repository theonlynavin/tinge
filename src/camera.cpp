#include "math.h"
#include "camera.h"
Ray :: Ray(Vec3 origin , Vec3 direction) : origin(origin), direction(normalize(direction)) {} // Parameterized constructor
// Direction must be normalized while taking in
Ray :: ~Ray() {}

Vec3 Ray::at(float t) {
    return origin + direction * t;
} // Should return origin + t*direction;

Camera :: Camera(float vertical_fov , int film_width , int film_height , float focal_length)
: vertical_fov(vertical_fov), film_width(film_width), 
film_height(film_height), focal_length(focal_length) {} 

Camera :: ~Camera() {}

Ray Camera :: generate_ray(float u, float v) {

    // Given NDC coordinates (u, v), should generate the corresponding ray
    float aspect_ratio = static_cast<float>(film_width) / film_height;
    float half_height = (focal_length) * tan((vertical_fov) / 2);
    float half_width = aspect_ratio * half_height;

    float x_coord = (2 * u - 1) * half_width;
    float y_coord = (2 * v - 1) * half_height;

    Vec3 origin(0, 0, 0); // All rays start from the pin-hole(assumed at origin)
    Vec3 direction(x_coord, y_coord, -focal_length);
    // Position vector for the given NDC{assumed range [0,1]}
    
    return Ray((frame).frameToWorld * origin, ((frame).frameToWorld&direction).normalized());
}
