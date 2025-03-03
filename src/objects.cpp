#include "objects.h"
#include "math.h"

// TODO: Return point
// FIX: make intsec out struct prolly

Plane::Plane(Vec3 normal, Vec3 point) : n(normal), p(point) {};
Plane::~Plane() {};

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3) : v1(v1), v2(v2), v3(v3) {
  n = cross(v1 - v2, v2 - v3);
  n = n.normalized();
};
Triangle::~Triangle() {};

Sphere::Sphere(Vec3 centre, float radius) : c(centre), r(radius) {};
Sphere::~Sphere() {};

bool intersect(Ray &ray, Sphere &sph) {
  float b = 2 * (dot(ray.direction, ray.origin - sph.c));
  float c = dot(ray.origin - sph.c, ray.origin - sph.c) - sph.r * sph.r;

  float del = b * b - 4 * c;

  return del > 0;
}

bool intersect(Ray &ray, Plane &plane) {
  float d = dot(ray.direction, plane.n);

  return !is_zero(d);
}

bool intersect(Ray &ray, Triangle &tri) {
  float d = dot(ray.direction, tri.n);

  if (is_zero(d))
    return false;

  float a[3]; // Barycentric coordinates

  Vec3 e1 = tri.v2 - tri.v1;
  Vec3 e2 = tri.v3 - tri.v1;
  Vec3 lhs = ray.origin - tri.v1;

  Vec3 c1 = cross(e1, ray.direction);
  Vec3 c2 = cross(e2, ray.direction);

  a[1] = dot(lhs, c2) / dot(e1, c2);
  a[2] = dot(lhs, c1) / dot(c1, e2);

  a[0] = 1 - a[1] - a[2];

  // FIXME: Gives true for ray extending both directions
  return (a[0] > 0 && a[1] > 0 && a[2] > 0);
}
