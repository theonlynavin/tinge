#include "bvh.h"
#include "math.h"
#include "obj_loader/OBJ_Loader.h"
#include "objects.h"
#include "util.h"
#include <string>

Vec3 min_v_P(Vec3 m, float x, float y, float z) {
    return Vec3(m.x > x ? x : m.x, m.y > y ? y : m.y, m.z > z ? z : m.z);
}

Vec3 max_v_P(Vec3 m, float x, float y, float z) {
    return Vec3(m.x < x ? x : m.x, m.y < y ? y : m.y, m.z < z ? z : m.z);
}

BVH_Box::BVH_Box(const std::string &fname, mat_pointer material, Vec3 origin,
                 Vec3 scale, Vec3 rotation) {
    type = BVH_Volume;
    // Initialize Loader
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(fname);
    objl::Mesh mesh = Loader.LoadedMeshes[0];
    triangles.reserve(mesh.Indices.size());

    for (int i = 0; i < mesh.Indices.size(); i += 3) {
        auto &v1 = mesh.Vertices[mesh.Indices[i]].Position;
        auto &v2 = mesh.Vertices[mesh.Indices[i + 1]].Position;
        auto &v3 = mesh.Vertices[mesh.Indices[i + 2]].Position;
        obj_pointer triangle = std::make_unique<Triangle>(
            Vec3(v1.X, v1.Y, v1.Z), Vec3(v2.X, v2.Y, v2.Z),
            Vec3(v3.X, v3.Y, v3.Z), material);
        triangle->frame.origin = origin;
        triangle->frame.rotation = rotation;
        triangle->frame.scale = scale;
        triangle->frame.lockFrame();

        triangles.push_back(std::move(triangle));
    }

    auto &v = mesh.Vertices[0].Position;

    min = Vec3(v.X, v.Y, v.Z);
    max = Vec3(v.X, v.Y, v.Z);
    for (int i = 0; i < mesh.Vertices.size(); i++) {
        auto &v1 = mesh.Vertices[i].Position;
        min = min_v_P(min, v1.X, v1.Y, v1.Z);
        max = max_v_P(max, v1.X, v1.Y, v1.Z);
    }

    min = triangles[0]->frame.frameToWorld * min - Vec3(0.1, 0.1, 0.1);
    max = triangles[0]->frame.frameToWorld * max + Vec3(0.1, 0.1, 0.1);
    std::cout << min << max << std::endl;
}

BVH_Box::~BVH_Box() {}
bool BVH_Box::_intersect(const Ray &ray, IntersectionOut &intersect_out) {
    float tmin = (min.x - ray.origin.x) / ray.direction.x;
    float tmax = (max.x - ray.origin.x) / ray.direction.x;

    if (tmin > tmax) {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }

    float tymin = (min.y - ray.origin.y) / ray.direction.y;
    float tymax = (max.y - ray.origin.y) / ray.direction.y;

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

    float tzmin = (min.z - ray.origin.z) / ray.direction.z;
    float tzmax = (max.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) {
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    auto hit = closestIntersect(triangles, ray);
    intersect_out = hit.second;
    return intersect_out.hit;
}

Vec3 BVH_Box::_get_normal(const Vec3 &point) { return Vec3(0, 0, 0); }
