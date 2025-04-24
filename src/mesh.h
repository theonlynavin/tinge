#pragma once
#include "bvh.h"
#include "material.h"
#include "objects.h"
#include <memory>

/***********************************
 * Mesh Class
 ***********************************/
struct Mesh : AbstractShape {
    std::unique_ptr<BVH_Node> root; /**< Root node for mesh's BVH */

    /******************************************
     * @brief Parametrized mesh constructor
     * @param fname Path to .obj file
     * @param material Material of mesh
     * @param origin Origin of frame
     * @param scale Scale of frame
     * @param rotation Rotation of frame
     ******************************************/
    Mesh(const std::string &fname, mat_pointer material, Vec3 origin,
         Vec3 scale, Vec3 rotation);

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};
