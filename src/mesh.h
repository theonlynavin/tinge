#pragma once
#include "camera.h"
#include "frame.h"
#include "material.h"
#include "math.h"
#include "objects.h"
#include <memory>
#include <utility>
#include <vector>

struct Mesh : AbstractShape {
    std::vector <Triangle> triangle_array; /**<Array of triangles that make up the object*/
    int last_hit_index = -1; /**<Index of closest triangle hit by ray */

    /******************************************
     * @brief Parametrized mesh constructor
     * @param triangle_array Array of triangles that make up the object
     ******************************************/
    Mesh(std::vector <Triangle> triangle_array); // Parametrized mesh constructor 
    ~Mesh();

    protected:
        bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
        Vec3 _get_normal(const Vec3 &point) override; 
};

