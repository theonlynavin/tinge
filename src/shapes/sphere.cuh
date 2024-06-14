#pragma once
#include "ray.cuh"

class Sphere
{
private:
    const glm::vec3 centre;
    const float radius;
    const float r2;
public:
    inline __host__ __device__ Sphere(const glm::vec3& centre, float radius) : centre(centre), radius(radius), r2(radius*radius) {};
    inline __host__ __device__ ~Sphere() {};
    inline __device__ bool intersect(const Ray& r, HitInfo& info)
    {
        // Vec4 o = trnsf * makeVec4(r.origin.x, r.origin.y, r.origin.z, 1);
        // Vec4 d = trnsf * makeVec4(r.dir.x, r.dir.y, r.dir.z, 0);
        glm::vec3 rorigin = r.origin;// glm::vec3{o.x, o.y, o.z};
        glm::vec3 rdir = r.dir;// glm::vec3{d.x, d.y, d.z};

        glm::vec3 m = rorigin - centre;
        float a = dot(rdir, rdir);
        float b = dot(m, rdir);
        float c = dot(m, m) - r2;
        float discr = b*b - a*c;
        if (discr < 0) return false;
        float inva = 1/a;
        float D = sqrt(discr);
        float t0 = inva * (-b - D);
        float t1 = inva * (-b + D);
        float t;

        if (t0 < 1e-6)
        {
            if (t1 > info.dist || t1 < 1e-6) return true;
            else t = t1;
        }
        else {
            if (t0 > info.dist || t0 < 1e-6) return true;
            else t = t0;
        }
        info.dist = t;
        info.point = r(t);
        info.normal = (rorigin + t * rdir - centre) / radius;

        return true;
    }
};    
