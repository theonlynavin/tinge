#include "camera.h"
#include "math.h"
#include "util.h"
#include <cmath>
#include <ctime>
#include <system_error>

Ray ::Ray() {} 
/************
 * Parameterized constructor
 * Direction must be normalized while taking in
 ***********/
Ray ::Ray(Vec3 origin, Vec3 direction)
    : origin(origin), direction(normalize(direction)) {
} 
// Direction must be normalized while taking in

/***************
 * @par direction vector and the distance from origin 
 * Generates a ray 
 * @return  return origin + t*direction;
 ***************/
Vec3 Ray::at(float t) const {
    return origin + direction * t;
} 

/***************
 * parameterized constructor for class Camera 
 * @par film-height : It is the vertical measurement of the film 
 * @par film-width : It is the horizontal measurement of the film 
 * @par focal length : Focal length of the aperture of camera 
 * @par vertical_fov : It is the extent of observable world expressend in terms of vertical angle (in radians)
 * @par aperture_size : Radius of the aperture of camera 
 ******************/
Camera ::Camera(float vertical_fov, int film_width, int film_height,
                float focal_length, float aperture_size)
    : vertical_fov(vertical_fov), film_width(film_width),
      film_height(film_height), focal_length(focal_length),
      aperture_size(aperture_size) {}
/********************
 * Destructor for class Camera 
 ************/
Camera ::~Camera() {}


/********************
 * Given NDC coordinates (u, v), should generate the corresponding ray
 * @par (u,v) NDC coordinates of a point 
 * @par random_gen : member function of class Random 
 * @return Corresponding ray to that point 
 */

Ray Camera ::generate_ray(float u, float v, Random &random_gen) {

    
    float aspect_ratio = static_cast<float>(film_width) / film_height;
    float half_height = (focal_length)*tan((vertical_fov) / 2);
    float half_width = aspect_ratio * half_height;

    float x_coord = (2 * u - 1) * half_width;
    float y_coord = (2 * v - 1) * half_height;
// All rays start from the pin-hole(assumed at origin)

    Vec3 origin(0, 0, 0); 
    Vec3 direction(x_coord, y_coord, -focal_length);

// Converting the ray from camera frame to world frame and then normalizing as well

    direction = (frame.frameToWorld & direction).normalized();
    origin = frame.frameToWorld * origin;
// Position vector for the given NDC{assumed range [0,1]}

    Vec3 focal_point = Ray(origin, direction.normalized()).at(focal_length);

// Origin randomly shifted in the aperture only 

    Vec3 n_origin = origin + aperture_size * random_gen.GenerateUniformPointDisc();
// Direction of ray from the shifted origin to the point on the frame (whose z-component is -focal length)     
    Vec3 n_direction = (focal_point - n_origin).normalized();

    return Ray(n_origin, n_direction);
}

/************
 * Changes the focus of camera aperture from one point to another 
 * @par "from" is the origin of camera and "at" is the final point to be focused upon 
 * @return nothing , void type 
 */
void Camera::look_at(Vec3 from, Vec3 to) {
    Vec3 direction = to - from;                 //final vector direction 
    focal_length = direction.length();          //focal length fixing 
    Vec3 A = Vec3(0, 0, -1);                    //initial vector direction
    Vec3 B = direction / direction.length();
    frame.origin = from;                        //center of camera 

    Vec3 axis = cross(A, B).normalized();       // axis of rotaion , which we got through cross multiplication of initial and final vectors
    float dp = dot(A, B);                       // angle through which vector need to be rotated
    float angle = std::acos(dp);                

    Mat3 K;
    Mat3 I;
    K.m[0][0] = 0;                              // rotation matrix , to know more details read about "Rodrigues's Rotation" 
    K.m[0][1] = -axis.z;
    K.m[0][2] = axis.y;
    K.m[1][0] = axis.z;
    K.m[1][1] = 0;
    K.m[1][2] = -axis.x;
    K.m[2][0] = -axis.y;
    K.m[2][1] = axis.x;
    K.m[2][2] = 0;

    K = I - K * std::sin(angle) + K * K * (1 - dp);
    float pitch = -std::asin(K.m[2][0]);                    // Extraction of rotation angle needed about various axes using the rotation matrix 
    float yaw = std::atan2(K.m[1][0], K.m[1][1]);           // For more details , google pitch ,yaw and roll
    float roll = std::atan2(K.m[2][1], K.m[2][2]);

    frame.rotation.x = -roll;
    frame.rotation.y = -pitch;
    frame.rotation.z = yaw;
    frame.lockFrame();
}
