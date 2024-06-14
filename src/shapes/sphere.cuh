#pragma once
#include "math.cuh"
#include "ray.cuh"

namespace Tinge
{
    class Sphere
    {
    private:
        const Vec3 centre;
        const Float radius;
        const Float r2;
    public:
        inline __host__ __device__ Sphere(const Vec3& centre, Float radius) : centre(centre), radius(radius), r2(radius*radius) {};
        inline __host__ __device__ ~Sphere() {};
        inline __device__ bool intersect(const Ray& r, const Matrix4& trnsf, HitInfo& info)
        {
           // Vec4 o = trnsf * makeVec4(r.origin.x, r.origin.y, r.origin.z, 1);
           // Vec4 d = trnsf * makeVec4(r.dir.x, r.dir.y, r.dir.z, 0);
            Vec3 rorigin = r.origin;// Vec3{o.x, o.y, o.z};
            Vec3 rdir = r.dir;// Vec3{d.x, d.y, d.z};

            Vec3 m = rorigin - centre;
            Float a = dot(rdir, rdir);
            Float b = dot(m, rdir);
            Float c = dot(m, m) - r2;
            Float discr = b*b - a*c;
            if (discr < 0) return false;
            Float inva = 1/a;
            Float D = sqrt(discr);
            Float t0 = inva * (-b - D);
            Float t1 = inva * (-b + D);
            Float t;

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
} // namespace Tinge
