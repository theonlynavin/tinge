#pragma once
#include "math.h"
#include <random>

/**************************************
 * Interface for tinge random functions
 **************************************/
class Random {
  private:
    unsigned int seed;      /**< Seed of generator*/
    std::mt19937 generator; /**< Mersenne Twister for random numbers*/

  public:
    /**************************************
     * Constructor
     ***************************************/
    Random(unsigned int seed);

    /**************************************************************
     * Generate a uniform float in [0, 1)
     * @return A random float in [0, 1) with uniform distribution
     ***************************************************************/
    double GenerateUniformFloat();

    /*****************************************
     * Generate a random point in a unit disc
     * @return A random point in the unit disc
     *****************************************/
    Vec3 GenerateUniformPointDisc();

    /*******************************************
     * Generate a random point on a unit sphere
     * @return A random point on the unit sphere
     *******************************************/
    Vec3 GenerateUniformPointSphere();

    /**********************************************************************
     * Generate a random point on a unit hemisphere with specified 'central
     * normal' using a uniform distribution
     * @param n The central normal of the hemisphere
     * @return A random point on the specified unit hemisphere
     **********************************************************************/
    Vec3 GenerateUniformPointHemisphere(const Vec3 &n);

    /**********************************************************************
     * Generate a random point on a unit hemisphere with specified 'central
     * normal' using a cosine weighted distribution
     * @param n The central normal of the hemisphere
     * @return A random point on the specified unit hemisphere
     **********************************************************************/
    Vec3 GenerateCosinePointHemisphere(const Vec3 &n);
};
