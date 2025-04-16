#pragma once

#include "material.h"
#include "objects.h"
#include <vector>

struct BVH_Box : AbstractShape {
    std::vector<obj_pointer> triangles;
    Vec3 min, max;

    BVH_Box(const std::string &fname, mat_pointer material, Vec3 origin,
            Vec3 scale, Vec3 rotation);
    ~BVH_Box();

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intersect_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};
