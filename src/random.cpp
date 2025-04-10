#include "random.h"
#include "math.h"
#include <cmath>

Random::Random(unsigned int seed) : seed(seed), generator(seed) {}

double Random::GenerateUniformFloat() {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    return distribution(this->generator);
}

Vec3 Random::GenerateUniformPointDisc() {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    double r = std::sqrt(distribution(generator));
    double theta = distribution(generator) * 2 * M_PI;

    double x = r * std::cos(theta);
    double y = r * std::sin(theta);
    return Vec3(x, y, 0);
}

Vec3 Random::GenerateUniformPointSphere() {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    float u = distribution(generator);
    float v = distribution(generator);

    float theta = u * 2 * M_PI;
    float cos_phi = 2 * v - 1;
    float sin_phi = std::sqrt(1 - cos_phi * cos_phi);

    Vec3 ret;

    ret.x = cos_phi;
    ret.y = std::sin(theta) * sin_phi;
    ret.z = std::cos(theta) * sin_phi;
    return ret;
}

// Generate a random point on a hemisphere around a normal vector
Vec3 Random::GenerateUniformPointHemisphere(const Vec3 &n) {
    Vec3 ret = GenerateUniformPointSphere();
    float factor = dot(ret, n) > 0 ? 1 : -1;

    return ret * factor;
}
