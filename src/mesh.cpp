
#include "mesh.h"
#include "bvh.h"
#include "obj_loader/OBJ_Loader.h"
#include "objects.h"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

Mesh::Mesh(const std::string &fname, mat_pointer material, Vec3 origin,
           Vec3 scale, Vec3 rotation, int bvh_height) {
    type = MeshObject;
    root = std::make_unique<BVH_Node>();
    this->material = material;

    objl::Loader Loader;
    bool loadout = Loader.LoadFile("teapot.obj");
    Frame f;
    f.origin = origin;
    f.rotation = rotation;
    f.scale = scale;
    f.lockFrame();

    for (const auto &loaded_mesh : Loader.LoadedMeshes) {
        /*objl::Mesh loaded_mesh = Loader.LoadedMeshes[0];*/
        for (int i = 0; i < loaded_mesh.Indices.size(); i += 3) {
            auto &v1 = loaded_mesh.Vertices[loaded_mesh.Indices[i]].Position;
            auto &v2 =
                loaded_mesh.Vertices[loaded_mesh.Indices[i + 1]].Position;
            auto &v3 =
                loaded_mesh.Vertices[loaded_mesh.Indices[i + 2]].Position;
            std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>(
                f.frameToWorld * Vec3(v1.X, v1.Y, v1.Z),
                f.frameToWorld * Vec3(v2.X, v2.Y, v2.Z),
                f.frameToWorld * Vec3(v3.X, v3.Y, v3.Z), material);
            triangle->type = MeshTriangle;

            root->volume.expand(triangle->centre);
            root->triangles.push_back(std::move(triangle));
        }
    }

    std::cout << root->volume.min << root->volume.max << std::endl;
    split(root, bvh_height);
}

bool traverse(const std::unique_ptr<BVH_Node> &root, const Ray &ray,
              IntersectionOut &intsec_out) {
    if (!root->volume.intersect(ray))
        return false;
    if (root->childA == nullptr && root->childB == nullptr) {
        for (const auto &i : root->triangles) {
            IntersectionOut ans = i->intersect(ray);
            if (ans.hit) {
                if (ans.t < intsec_out.t) {
                    intsec_out = ans;
                }
            }
        }

        return intsec_out.hit;
    } else {
        /*IntersectionOut intsec_out_copy = intsec_out;*/
        float h1_ = root->childA->volume.heuristic_intersect(ray);
        float h2_ = root->childB->volume.heuristic_intersect(ray);

        if (h1_ < 0) {
            // If ray misses child A
            // And ray misses child B
            if (h2_ < 0)
                return false;
            // Check child B
            return traverse(root->childB, ray, intsec_out);
        } else {
            // If ray hits child A
            // And ray misses child B then just check child A
            if (h2_ < 0)
                return traverse(root->childA, ray, intsec_out);

            // If ray hits A and B but A's box is closer
            // check A first if it passes through check B
            if (h1_ < h2_) {
                if (traverse(root->childA, ray, intsec_out))
                    return true;
                return traverse(root->childB, ray, intsec_out);
            } else {
                if (traverse(root->childB, ray, intsec_out))
                    return true;
                return traverse(root->childA, ray, intsec_out);
            }
        }
    }
}

bool Mesh::_intersect(const Ray &ray, IntersectionOut &intsec_out) {
    IntersectionOut min_hit;
    min_hit.t = TINGE_INFINITY;
    min_hit.hit = false;
    bool hit = traverse(root, ray, min_hit);
    if (hit) {
        intsec_out = min_hit;
        return true;
    }
    return false;
}

Vec3 Mesh::_get_normal(const Vec3 &point) { return Vec3(0, 0, 0); }
