
#include "mesh.h"
#include "bvh.h"
#include "obj_loader/OBJ_Loader.h"
#include "objects.h"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

Mesh::Mesh(const std::string &fname, mat_pointer material, Vec3 origin,
           Vec3 scale, Vec3 rotation) {
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
    split(root, 1);
}

bool traverse(const std::unique_ptr<BVH_Node> &root, const Ray &ray,
              IntersectionOut &intsec_out) {
    if (!root->volume.intersect(ray))
        return false;
    if (root->childA == nullptr && root->childB == nullptr) {
        /*std::cout << "Testing triangles " << root->triangles.size()*/
        /*          << std::endl;*/
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
        return traverse(root->childA, ray, intsec_out) ||
               traverse(root->childB, ray, intsec_out);
    }
}

bool Mesh::_intersect(const Ray &ray, IntersectionOut &intsec_out) {
    IntersectionOut min_hit;
    min_hit.t = TINGE_INFINITY;
    min_hit.hit = false;
    if (!root->volume.intersect(ray))
        return false;
    bool hit = traverse(root, ray, min_hit);
    intsec_out = min_hit;
    if (hit) {
    }
    return hit;
}

Vec3 Mesh::_get_normal(const Vec3 &point) { return Vec3(0, 0, 0); }
