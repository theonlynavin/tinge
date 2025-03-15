#include "math.h"
#include <random>

class Random {
  private:
    unsigned int seed;
    std::mt19937 generator; // Mersenne Twister for random numbers

  public:
    // Constructor
    Random(unsigned int seed);
    // Generate a uniform float in [0, 1)
    double GenerateUniformFloat();
    // Generate a random point on a disc
    std::pair<double, double> GenerateUniformPointDisc();
    // Generate a random point on a sphere
    Vec3 GenerateUniformPointSphere();
    // Generate a random point on a hemisphere around a normal vector
    Vec3 GenerateUniformPointHemisphere(const Vec3 &n);
};
