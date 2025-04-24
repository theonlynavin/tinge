#pragma once

#include "math.h"
#include "objects.h"
#include <memory>
#include <vector>

/***********************************
 * BVH bounding box class
 ***********************************/
struct BVH_Volume {
    Vec3 min = Vec3(TINGE_INFINITY, TINGE_INFINITY,
                    TINGE_INFINITY); /**< Min corner of bounding box*/
    Vec3 max = -Vec3(TINGE_INFINITY, TINGE_INFINITY,
                     TINGE_INFINITY); /**< Max corner of bounding box*/
    Vec3 centre;                      /**< Cenre of bounding box*/

    /***************************************************
     * @brief Expanding volume to accomodate point
     * @param point Point to include
     ***************************************************/
    void expand(const Vec3 &point);

    /***************************************************
     * @brief Check boolean intersection with volume
     * @param ray Ray to check
     * @return Ray hit bool
     ***************************************************/
    const bool intersect(const Ray &ray) const;

    /***************************************************
     * @brief Get minimum length to intersect cube
     * @param ray Ray to check
     * @return Distance to cube
     ***************************************************/
    const float heuristic_intersect(const Ray &ray) const;
};

/***********************************
 * BVH node class
 ***********************************/
struct BVH_Node {
    struct BVH_Volume volume;                   /**< Bounding volume*/
    std::unique_ptr<BVH_Node> childA = nullptr; /**< Child A*/
    std::unique_ptr<BVH_Node> childB = nullptr; /**< Child B*/
    std::vector<std::unique_ptr<Triangle>>
        triangles; /**< Triangles in node; empty if node is not a leaf*/
};

/***************************************************
 * @brief Splits BVH node into tree of height max_depth
 * @param root Root of BVH tree
 * @param max_depth Height of final tree
 ***************************************************/
void split(std::unique_ptr<BVH_Node> &root, int max_depth);
