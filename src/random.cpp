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

// Generate a random point on a hemisphere around a normal vector
Vec3 Random::GenerateCosinePointHemisphere(const Vec3 &n) {
    Vec3 ret = GenerateUniformPointDisc();
    ret.z = std::sqrt(1 - dot(ret, ret));

    float c1 = 1 / (1 + n.z);
    float c2 = n.y * c1;
    float c3 = n.x * c1;
    Mat3 m{};
    m[0][0] = 1 - n.x * c3;
    m[0][1] = -n.x * c2;
    m[0][2] = n.x;
    m[1][0] = -n.x * c2;
    m[1][1] = 1 - n.y * c2;
    m[1][2] = n.y;
    m[2][0] = -n.x;
    m[2][1] = -n.y;
    m[2][2] = n.z;

    return m * ret;
}
