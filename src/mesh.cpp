#include "objects.h"
#include "material.h"
#include "math.h"
#include "mesh.h"
#include <iostream>
#include <memory>

Mesh::Mesh(std::vector <Triangle> triangle_array)
    : triangle_array(triangle_array) {
};
Mesh::~Mesh(){}

bool Mesh::_intersect(const Ray &ray, IntersectionOut &intersect_out){
    float closest_t = TINGE_INFINITY;
    last_hit_index = -1; 
    for (int i = 0; i < triangle_array.size(); i++){
        intersect_out = triangle_array[i].intersect(ray);
        if (intersect_out.t < closest_t){
            closest_t = intersect_out.t;
            last_hit_index = i;
        }
    }
    
}

Vec3 Mesh::_get_normal(const Vec3 &point){
    Vec3 normal = triangle_array[last_hit_index].n;
    return normalize(normal);
}
