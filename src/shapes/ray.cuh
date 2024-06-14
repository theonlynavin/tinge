#pragma once
#include "math.cuh"

/// Ray (device only)
struct Ray
{
    /// @param origin position vector from where the ray originates
    /// @param dir normalized direction of the ray
    __device__ __forceinline__ Ray(const glm::vec3& origin, const glm::vec3& dir) 
        : origin(origin), dir(dir), invdir(1/dir.x, 1/dir.y, 1/dir.z)
    {
    }

    /// @brief returns point at distance t from the ray orgin
    /// @param t distance
    /// @return origin + t * dir
    __device__ __forceinline__ glm::vec3 operator()(float t) const
    { 
        return origin + t * dir; 
    }

    glm::vec3 origin;   // Origin
    glm::vec3 dir;      // Direction
    glm::vec3 invdir;   // 1 / dir, precomputed for performance
};

/// HitInfo (stores ray-surface intersection data)
struct HitInfo
{
    float dist = INFINITY;
    glm::vec3 normal = {};
    glm::vec3 point = {};
};