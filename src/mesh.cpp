
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
        float h1_ = root->childA->volume.heuristic_intersect(ray);
        float h2_ = root->childA->volume.heuristic_intersect(ray);

        // If both box collisions are close check both else check closer first
        if (abs(h1_ - h2_) < 1e-5) {
            IntersectionOut a, b;
            bool h1 = traverse(root->childA, ray, a);
            bool h2 = traverse(root->childB, ray, b);

            if (h1 && h2) {
                if (a.t < b.t)
                    intsec_out = a;
                else
                    intsec_out = b;
                return true;
            }

            if (h1) {
                intsec_out = a;
                return true;
            }

            if (h2) {
                intsec_out = b;
                return true;
            }

            return false;
        } else if (h1_ > 0 && h1_ < h2_) {
            if (traverse(root->childA, ray, intsec_out))
                return true;
            return traverse(root->childB, ray, intsec_out);
        } else if (h2_ > 0 && h2_ < h1_) {
            if (traverse(root->childB, ray, intsec_out))
                return true;
            return traverse(root->childA, ray, intsec_out);
        }
        return false;
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
