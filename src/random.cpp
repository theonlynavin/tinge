#include "random.h"
#include "math.h"
#include <cmath>
/************************
 * Constructor for generating Random number 
 ************************/
Random::Random(unsigned int seed) : seed(seed), generator(seed) {}

/**********************
 * Generates a random number from 0 to 1
 * @return number from (0,1)
 * ********************/
double Random::GenerateUniformFloat() {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    return distribution(this->generator);
}

/****************************
 * Generates a random point on a disc of radius 1
 * Sqrt is used to make more uniform distribution on the disc otherwise the randomly generated numbers will be more concentrated to center 
 * @return random point from a disc of radius 1 
 * ****************************/
Vec3 Random::GenerateUniformPointDisc() {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    double r = std::sqrt(distribution(generator));
    double theta = distribution(generator) * 2 * M_PI;

    double x = r * std::cos(theta);
    double y = r * std::sin(theta);
    return Vec3(x, y, 0);
}

/*********************
 * Generates a random point on a sphere of radius 1
 * @return point on sphere of radius 1
 *******************/
Vec3 Random::GenerateUniformPointSphere() {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    float u = distribution(generator);
    float v = distribution(generator);

    float theta = u * 2 * M_PI;                         // Using Spherical polar coordinates 
    float cos_phi = 2 * v - 1;
    float sin_phi = std::sqrt(1 - cos_phi * cos_phi);

    Vec3 ret;

    ret.x = cos_phi;
    ret.y = std::sin(theta) * sin_phi;
    ret.z = std::cos(theta) * sin_phi;
    return ret;
}

/*****************************
 *  Generates a random point on a hemisphere around a normal vector
 * @par n ,A 3D vector representing a normal passing through hemisphere 
 * @return random point on the hemisphere 
 *  */
Vec3 Random::GenerateUniformPointHemisphere(const Vec3 &n) {
    Vec3 ret = GenerateUniformPointSphere();
    float factor = dot(ret, n) > 0 ? 1 : -1;

    return ret * factor;
}
