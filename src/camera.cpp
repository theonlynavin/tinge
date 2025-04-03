#include "camera.h"
#include "math.h"
#include <ctime>

Ray ::Ray() {} // Parameterized constructor

Ray ::Ray(Vec3 origin, Vec3 direction)
    : origin(origin), direction(normalize(direction)) {
} // Parameterized constructor
// Direction must be normalized while taking in

Vec3 Ray::at(float t) const {
    return origin + direction * t;
} // Should return origin + t*direction;

Camera ::Camera(float vertical_fov, int film_width, int film_height,
                float focal_length, float aperture_size)
    : vertical_fov(vertical_fov), film_width(film_width),
      film_height(film_height), focal_length(focal_length),
      aperture_size(aperture_size) {}

Camera ::~Camera() {}

Ray Camera ::generate_ray(float u, float v, Random &random_gen) {

    // Given NDC coordinates (u, v), should generate the corresponding ray
    float aspect_ratio = static_cast<float>(film_width) / film_height;
    float half_height = (focal_length)*tan((vertical_fov) / 2);
    float half_width = aspect_ratio * half_height;

    float x_coord = (2 * u - 1) * half_width;
    float y_coord = (2 * v - 1) * half_height;

    Vec3 origin(0, 0, 0); // All rays start from the pin-hole(assumed at origin)
    Vec3 direction(x_coord, y_coord, -focal_length);
    direction = (frame.frameToWorld & direction).normalized();
    origin = frame.frameToWorld * origin;
    // Position vector for the given NDC{assumed range [0,1]}

    Vec3 focal_point = Ray(origin, direction).at(focal_length);
    auto [dx, dy] = random_gen.GenerateUniformPointDisc();
    Vec3 n_origin = origin;
    n_origin.x += aperture_size * dx;
    n_origin.y += aperture_size * dy;
    Vec3 n_direction = (focal_point - n_origin).normalized();

    return Ray(n_origin, n_direction);
}
