#include "objects.h"
#include "math.h"

// TODO: Return point
// FIX: make intsec out struct prolly
//
//

IntersectionOut::IntersectionOut(Vec3 normal, float t, Vec3 point)
    : normal(normal), t(t), point(point), hit(false) {};

IntersectionOut AbstractShape::intersect(const Ray &ray) {
    Ray frame_ray = this->frame.convertToFrame(ray);
    IntersectionOut intsec_out(Vec3(0, 0, 0), 0, Vec3(0, 0, 0));
    this->_intersect(frame_ray, intsec_out);
    return intsec_out;
}

Vec3 AbstractShape::get_normal(const Vec3 &point) {
    Vec3 frame_point = this->frame.frameToWorld & point;
    Vec3 frame_normal = this->_get_normal(frame_point);
    return transpose(frame.worldToFrame) & frame_normal;
}

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3) : v1(v1), v2(v2), v3(v3) {
    n = cross(v1 - v2, v2 - v3);
    n = n.normalized();
};
Triangle::~Triangle() {}

bool Triangle::_intersect(const Ray &ray) {
    float d = dot(ray.direction, this->n);

    if (is_zero(d))
        return false;

    float a[3]; // Barycentric coordinates

    Vec3 e1 = this->v2 - this->v1;
    Vec3 e2 = this->v3 - this->v1;
    Vec3 lhs = ray.origin - this->v1;

    Vec3 c1 = cross(e1, ray.direction);
    Vec3 c2 = cross(e2, ray.direction);

    a[1] = dot(lhs, c2) / dot(e1, c2);
    a[2] = dot(lhs, c1) / dot(c1, e2);

    a[0] = 1 - a[1] - a[2];

    if (!(a[0] > 0 && a[1] > 0 && a[2] > 0))
        return false;
    Vec3 intersection_point =
        this->v1 * a[0] + this->v2 * a[1] + this->v3 * a[2];

    // Assuming normalized direction
    float lambda = dot(intersection_point - ray.origin, ray.direction);

    return lambda > 0;
}

Vec3 Triangle::_get_normal(const Vec3 &point) { return this->n; }

Sphere::Sphere(Vec3 centre, float radius) : c(centre), r(radius) {};
Sphere::~Sphere() {};

bool Sphere::_intersect(const Ray &ray) {
    float b = (dot(ray.direction, ray.origin - this->c));
    float c =
        dot(ray.origin - this->c, ray.origin - this->c) - this->r * this->r;
    if (b * b - c < 0) {
        return false;
    }
    float factor = sqrt(b * b - c);
    return b < factor;
}

Vec3 Sphere::_get_normal(const Vec3 &point) {
    Vec3 ret = point - this->c;
    return normalize(ret);
}
Plane::Plane(Vec3 normal, Vec3 point) : n(normal), p(point) {};
Plane::~Plane() {};
bool Plane::_intersect(const Ray &ray) {
    float d = dot(ray.direction, this->n);
    if (d < 0) {
        return false;
    }
    float t = (dot(this->p - ray.origin, this->n)) / d;
    return t > 0;
}
Vec3 Plane::_get_normal(const Vec3 &point) { return this->n; }
