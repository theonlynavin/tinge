#pragma once
#include "math.cuh"

namespace Tinge
{
    class Ray
    {
    public:
        __device__ inline Ray(const Vec3& origin, const Vec3& dir) // dir must be normalized
            : origin(origin), dir(dir), invdir(1/dir)
        {
        }

        __device__ inline Vec3 operator()(Float t) const
        { 
            return origin + t * dir; 
        }

        Vec3 origin, dir, invdir;
    };

    struct HitInfo
    {
        Float dist = INFINITY;
        Vec3 normal = {};
        Vec3 point = {};
    };
    
    
} // namespace Tinge