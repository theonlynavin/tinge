#pragma once
#include "math.h"
// WARN: Need to include lib for Ray

struct Triangle {
  Vec3 v1, v2, v3; // Position vectors of triangle vertices
  Vec3 n;          // Normal vector of triangle

  Triangle(Vec3 v1, Vec3 v2, Vec3 v3); // Parametrized triangle constructor
  ~Triangle();
};

struct Sphere {
  Vec3 c;  // Position vector of sphere centre
  float r; // Radius of sphere

  Sphere(Vec3 centre, float radius); // Parametrized triangle constructor
  ~Sphere();
};

struct Plane {
  Vec3 n; // Normal vector of plane
  Vec3 p; // Position vector of some point in plane

  Plane(Vec3 normal, Vec3 point); // Parametrized triangle constructor
  ~Plane();
};

bool intersect(Ray &ray, Sphere &sph);
bool intersect(Ray &ray, Triangle &tri);
bool intersect(Ray &ray, Plane &plane);
