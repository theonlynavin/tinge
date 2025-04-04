#include "objects.h"
#include "material.h"
#include "math.h"
#include <memory>

IntersectionOut::IntersectionOut()
    : normal(Vec3(0, 0, 0)), point(Vec3(0, 0, 0)), hit(false),
      t(TINGE_INFINITY) {}

IntersectionOut AbstractShape::intersect(const Ray &ray) {
    Ray frame_ray = ray;
    frame_ray.origin = this->frame.worldToFrame * frame_ray.origin;
    frame_ray.direction = this->frame.worldToFrame & frame_ray.direction;

    frame_ray.direction = normalize(frame_ray.direction);
    IntersectionOut intsec_out;
    bool hit = this->_intersect(frame_ray, intsec_out);
    intsec_out.hit = hit;
    if (!hit)
        return intsec_out;
    intsec_out.normal = transpose(frame.worldToFrame) & intsec_out.normal;
    intsec_out.normal = normalize(intsec_out.normal);
    intsec_out.point = frame.frameToWorld * intsec_out.point;
    intsec_out.hit_mat = material;
    intsec_out.w0 = ray;
    intsec_out.w0.direction = normalize(intsec_out.w0.direction);
    return intsec_out;
}

Vec3 AbstractShape::get_normal(const Vec3 &point) {
    Vec3 frame_point = this->frame.frameToWorld & point;
    Vec3 frame_normal = this->_get_normal(frame_point);
    return transpose(frame.worldToFrame) & frame_normal;
}

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, mat_pointer mat)
    : v1(v1), v2(v2), v3(v3) {
    n = cross(v1 - v2, v2 - v3);
    n = n.normalized();
    material = mat;
};
Triangle::~Triangle() {}

bool Triangle::_intersect(const Ray &ray, IntersectionOut &intersect_out) {
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
    intersect_out.normal = this->n;
    intersect_out.t = lambda;
    intersect_out.point = intersection_point;
    return lambda > 0;
}

Vec3 Triangle::_get_normal(const Vec3 &point) { return this->n; }

Sphere::Sphere(Vec3 centre, float radius, std::shared_ptr<AbstractMaterial> mat)
    : c(centre), r(radius) {
    material = mat;
};
Sphere::~Sphere() {};

bool Sphere::_intersect(const Ray &ray, IntersectionOut &intersect_out) {
    Vec3 L = this->c - ray.origin;
    float tca = dot(L, ray.direction);

    if (tca < 0)
        return false;

    float d2 = dot(L, L) - tca * tca;

    if (d2 < 0 || r * r < d2)
        return false;

    float t0 = tca - sqrt(r * r - d2);
    intersect_out.point = ray.at(t0);
    intersect_out.normal = intersect_out.point - c;
    intersect_out.t = t0;

    return true;
}

Vec3 Sphere::_get_normal(const Vec3 &point) {
    Vec3 ret = point - this->c;
    return normalize(ret);
}
Plane::Plane(Vec3 normal, Vec3 point, mat_pointer mat) : n(normal), p(point) {
    material = mat;
};
Plane::~Plane() {};

bool Plane::_intersect(const Ray &ray, IntersectionOut &intersect_out) {
    float d = dot(ray.direction, this->n);
    if (dot(p - ray.origin, ray.direction) < 0) {
        return false;
    }
    float t = (dot(this->p - ray.origin, this->n)) / d;

    if (t < 0)
        return false;
    intersect_out.t = t;
    intersect_out.normal = this->n;

    intersect_out.point = ray.at(t);
    return true;
}
Vec3 Plane::_get_normal(const Vec3 &point) { return this->n; }

std::pair<obj_pointer, IntersectionOut>
closestIntersect(const std::vector<obj_pointer> &v, const Ray &ray) {
    IntersectionOut min_hit;
    min_hit.t = TINGE_INFINITY;
    obj_pointer min_shape = NULL;
    for (int i = 0; i < v.size(); i++) {
        IntersectionOut ans = v[i]->intersect(ray);
        if (ans.hit) {
            if (ans.t < min_hit.t) {
                min_hit = ans;
                min_shape = v[i];
            }
        }
    }

    return std::pair<obj_pointer, IntersectionOut>(min_shape, min_hit);
}
