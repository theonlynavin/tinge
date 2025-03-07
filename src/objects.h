#pragma once
#include "camera.h"
#include "frame.h"
#include "math.h"

struct IntersectionOut {
    Vec3 normal;
    float t;
    Vec3 point; // World Space
    bool hit;

    IntersectionOut(Vec3 normal, float t, Vec3 point);
};

struct AbstractShape {
    Frame frame;
    IntersectionOut intersect(const Ray &ray);
    Vec3 get_normal(const Vec3 &point);

  protected:
    // Ray in World space
    virtual bool _intersect(const Ray &ray, IntersectionOut &intsec_out) = 0;

    // Point in World space
    virtual Vec3 _get_normal(const Vec3 &point) = 0;
};

struct Triangle : AbstractShape {
    Vec3 v1, v2, v3; // Position vectors of triangle vertices
    Vec3 n;          // Normal vector of triangle

    Triangle(Vec3 v1, Vec3 v2, Vec3 v3); // Parametrized triangle constructor
    ~Triangle();

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};

struct Sphere : AbstractShape {
    Vec3 c;  // Position vector of sphere centre
    float r; // Radius of sphere

    Sphere(Vec3 centre, float radius); // Parametrized triangle constructor
    ~Sphere();

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};

struct Plane : AbstractShape {
    Vec3 n; // Normal vector of plane
    Vec3 p; // Position vector of some point in plane

    Plane(Vec3 normal, Vec3 point); // Parametrized triangle constructor
    ~Plane();

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};
