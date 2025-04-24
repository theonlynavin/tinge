#include "bvh.h"
#include "math.h"
#include <memory>

Vec3 min_v_P(Vec3 m, float x, float y, float z) {
    return Vec3(m.x > x ? x : m.x, m.y > y ? y : m.y, m.z > z ? z : m.z);
}

Vec3 max_v_P(Vec3 m, float x, float y, float z) {
    return Vec3(m.x < x ? x : m.x, m.y < y ? y : m.y, m.z < z ? z : m.z);
}

void BVH_Volume::expand(const Vec3 &point) {
    max = max_v_P(max, point.x, point.y, point.z);
    min = min_v_P(min, point.x, point.y, point.z);
    centre = (max + min) / 2;
}

const float BVH_Volume::heuristic_intersect(const Ray &ray) const {
    float tmin = (min.x - ray.origin.x) * ray.inv_dir.x;
    float tmax = (max.x - ray.origin.x) * ray.inv_dir.x;

    if (tmin > tmax) {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }

    float tymin = (min.y - ray.origin.y) * ray.inv_dir.y;
    float tymax = (max.y - ray.origin.y) * ray.inv_dir.y;

    if (tymin > tymax) {
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    if ((tmin > tymax) || (tymin > tmax))
        return -1;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - ray.origin.z) * ray.inv_dir.z;
    float tzmax = (max.z - ray.origin.z) * ray.inv_dir.z;

    if (tzmin > tzmax) {
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return -1;

    if (tzmin > tmin)
        tmin = tzmin;
    return tmin;
}

const bool BVH_Volume::intersect(const Ray &ray) const {
    float tmin = (min.x - ray.origin.x) * ray.inv_dir.x;
    float tmax = (max.x - ray.origin.x) * ray.inv_dir.x;

    if (tmin > tmax) {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }

    float tymin = (min.y - ray.origin.y) * ray.inv_dir.y;
    float tymax = (max.y - ray.origin.y) * ray.inv_dir.y;

    if (tymin > tymax) {
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - ray.origin.z) * ray.inv_dir.z;
    float tzmax = (max.z - ray.origin.z) * ray.inv_dir.z;

    if (tzmin > tzmax) {
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    return tmin > 0;
}

void split(std::unique_ptr<BVH_Node> &root, int max_depth) {

    if (!max_depth)
        return;
    std::unique_ptr<BVH_Node> childA = std::make_unique<BVH_Node>();
    std::unique_ptr<BVH_Node> childB = std::make_unique<BVH_Node>();

    int N = root->triangles.size();

    Vec3 side_lengths = root->volume.max - root->volume.min;
    int longest = 0;

    // Find longest side and split it
    // TODO: Try surface area heuristic for splitting
    if (side_lengths.x > side_lengths.y) {
        if (side_lengths.z > side_lengths.x)
            longest = 2;
        else
            longest = 0;
    } else {
        if (side_lengths.z > side_lengths.y)
            longest = 2;
        else
            longest = 1;
    }

    for (int i = 0; i < N; i++) {
        float w1, w2;

        switch (longest) {
        case 0: {
            w1 = root->triangles[i]->centre.x;
            w2 = root->volume.centre.x;
            break;
        }
        case 1: {
            w1 = root->triangles[i]->centre.y;
            w2 = root->volume.centre.y;
            break;
        }
        case 2: {
            w1 = root->triangles[i]->centre.z;
            w2 = root->volume.centre.z;
            break;
        }
        };
        // c1 is strict side check, c2 is hand wavey heuristic check
        // to see if triangle is part of both sides of split
        bool c1 = w1 < w2;
        bool c2 = abs(w1 - w2) < root->triangles[i]->h;

        if (c2) {
            // If both sides copy triangle and give to both children
            std::unique_ptr<Triangle> copy_tr =
                std::make_unique<Triangle>(*root->triangles[i]);
            childA->volume.expand(root->triangles[i]->centre);
            childA->triangles.push_back(std::move(root->triangles[i]));
            childB->volume.expand(copy_tr->centre);
            childB->triangles.push_back(std::move(copy_tr));
        } else if (c1) {
            childA->volume.expand(root->triangles[i]->centre);
            childA->triangles.push_back(std::move(root->triangles[i]));
        } else {
            childB->volume.expand(root->triangles[i]->centre);
            childB->triangles.push_back(std::move(root->triangles[i]));
        }
    }

    root->childA = std::move(childA);
    root->childB = std::move(childB);
    split(root->childA, max_depth - 1);
    split(root->childB, max_depth - 1);
}
