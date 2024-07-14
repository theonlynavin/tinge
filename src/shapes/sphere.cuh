#pragma once
#include "ray.cuh"

class Sphere
{
private:
    const glm::vec3 centre;
    const float radius;
    const float radius2;
public:
    inline __host__ __device__ Sphere(const glm::vec3& centre, float radius) 
    : centre(centre), radius(radius), radius2(radius*radius) 
    {
    };

    inline __host__ __device__ ~Sphere() {};
    inline __device__ bool intersect(const Ray& r, HitInfo& info)
    {
        glm::vec3 m = r.origin - centre;
        float a = dot(r.dir, r.dir);
        float b = dot(m, r.dir);
        float c = dot(m, m) - radius2;
        float discr = b*b - a*c;
        if (discr < 0) return false;
        float inva = 1/a;
        float D = sqrtf(discr);
        float t0 = inva * (-b - D);
        float t1 = inva * (-b + D);
        float t;

        if (t0 < TINGE_EPSILON)
        {
            if (t1 > info.dist || t1 < TINGE_EPSILON) return true;
            else t = t1;
        }
        else {
            if (t0 > info.dist || t0 < TINGE_EPSILON) return true;
            else t = t0;
        }

        info.dist = t;

        return true;
    }
};    
