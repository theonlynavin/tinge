#pragma once
#include "bvh.h"
#include "material.h"
#include "objects.h"
#include <memory>

struct Mesh : AbstractShape {
    std::unique_ptr<BVH_Node> root;

    Mesh(const std::string &fname, mat_pointer material, Vec3 origin,
         Vec3 scale, Vec3 rotation);

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};
