#pragma once

#include "math.h"
#include "objects.h"
#include <memory>
#include <vector>

struct BVH_Volume {
    Vec3 min = Vec3(TINGE_INFINITY, TINGE_INFINITY, TINGE_INFINITY),
         max = -Vec3(TINGE_INFINITY, TINGE_INFINITY, TINGE_INFINITY), centre;
    void expand(const Vec3 &point);
    const bool intersect(const Ray &ray) const;
};

struct BVH_Node {
    struct BVH_Volume volume;
    std::unique_ptr<BVH_Node> childA = nullptr;
    std::unique_ptr<BVH_Node> childB = nullptr;
    std::vector<std::unique_ptr<Triangle>> triangles;
};

void split(std::unique_ptr<BVH_Node> &root, int max_depth);
