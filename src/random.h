#include <cmath>
#include <random>
#include <vector>

class Random {
private:
    unsigned int seed;
    std::mt19937 generator; // Mersenne Twister for random numbers

    // Function to normalize a vector
    std::vector<double> normalize(const std::vector<double>& vec) {
        double length = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
        return {vec[0] / length, vec[1] / length, vec[2] / length};
    }

public:
    // Constructor
    Random(unsigned int seed) : seed(seed), generator(seed) {}

    // Generate a uniform float in [0, 1)
    double GenerateUniformFloat() {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    }

    // Generate a random point on a disc
    std::pair<double, double> GenerateUniformPointDisc() {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double r = distribution(generator);
        double theta = distribution(generator) * 2 * M_PI;

        double x = r * std::cos(theta);
        double y = r * std::sin(theta);
        return {x, y};
    }

    // Generate a random point on a sphere
    std::vector<double> GenerateUniformPointSphere() {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double theta = distribution(generator) * 2 * M_PI;
        double phi = distribution(generator) * 2 * M_PI;

        double x = std::cos(theta);
        double y = std::sin(theta) * std::cos(phi);
        double z = std::sin(theta) * std::sin(phi);
        return {x, y, z};
    }

    // Generate a random point on a hemisphere around a normal vector
    std::vector<double> GenerateUniformPointHemisphere(const std::vector<double>& n) {
        std::vector<double> normalizedN = normalize(n);
        std::vector<double> oldPoint = GenerateUniformPointSphere();

        double dotProduct = normalizedN[0] * oldPoint[0] + normalizedN[1] * oldPoint[1] + normalizedN[2] * oldPoint[2];

        if (dotProduct < 0) {
            oldPoint[0] -= 2 * dotProduct * normalizedN[0];
            oldPoint[1] -= 2 * dotProduct * normalizedN[1];
            oldPoint[2] -= 2 * dotProduct * normalizedN[2];
        }
        return oldPoint;
    }
};
