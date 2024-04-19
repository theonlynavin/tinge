#include <cuda_runtime.h>
#include <math.h>
#include <iostream>

namespace tinge
{
    /* Vector operations */

    typedef float2 vec2;
    typedef float3 vec3;
    typedef float4 vec4;

    typedef float scalar;

    /* Vector addition */

    __host__ __device__ static inline vec2 operator+(const vec2& a, const vec2& b)
    {
        return vec2{a.x + b.x, a.y + b.y};
    }

    __host__ __device__ static inline vec3 operator+(const vec3& a, const vec3& b)
    {
        return vec3{a.x + b.x, a.y + b.y, a.z + b.z};
    }

    __host__ __device__ static inline vec4 operator+(const vec4& a, const vec4& b)
    {
        return vec4{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    }

    __host__ __device__ static inline vec2 operator+(scalar a, const vec2& b)
    {
        return vec2{a + b.x, a + b.y};
    }

    __host__ __device__ static inline vec3 operator+(scalar a, const vec3& b)
    {
        return vec3{a + b.x, a + b.y, a + b.z};
    }

    __host__ __device__ static inline vec4 operator+(scalar a, const vec4& b)
    {
        return vec4{a + b.x, a + b.y, a + b.z, a + b.w};
    }

    __host__ __device__ static inline vec2 operator+(const vec2& a, scalar b)
    {
        return vec2{a.x + b, a.y + b};
    }

    __host__ __device__ static inline vec3 operator+(const vec3& a, scalar b)
    {
        return vec3{a.x + b, a.y + b, a.z + b};
    }

    __host__ __device__ static inline vec4 operator+(const vec4& a, scalar b)
    {
        return vec4{a.x + b, a.y + b, a.z + b, a.w + b};
    }

    /* Vector subtraction and negation */ 

    __host__ __device__ static inline vec2 operator-(const vec2& a, const vec2& b)
    {
        return vec2{a.x - b.x, a.y - b.y};
    }

    __host__ __device__ static inline vec3 operator-(const vec3& a, const vec3& b)
    {
        return vec3{a.x - b.x, a.y - b.y, a.z - b.z};
    }

    __host__ __device__ static inline vec4 operator-(const vec4& a, const vec4& b)
    {
        return vec4{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    }

    __host__ __device__ static inline vec2 operator-(scalar a, const vec2& b)
    {
        return vec2{a - b.x, a - b.y};
    }

    __host__ __device__ static inline vec3 operator-(scalar a, const vec3& b)
    {
        return vec3{a - b.x, a - b.y, a - b.z};
    }

    __host__ __device__ static inline vec4 operator-(scalar a, const vec4& b)
    {
        return vec4{a - b.x, a - b.y, a - b.z, a - b.w};
    }

    __host__ __device__ static inline vec2 operator-(const vec2& a, scalar b)
    {
        return vec2{a.x - b, a.y - b};
    }

    __host__ __device__ static inline vec3 operator-(const vec3& a, scalar b)
    {
        return vec3{a.x - b, a.y - b, a.z - b};
    }

    __host__ __device__ static inline vec4 operator-(const vec4& a, scalar b)
    {
        return vec4{a.x - b, a.y - b, a.z - b, a.w - b};
    }

    __host__ __device__ static inline vec2 operator-(const vec2& a)
    {
        return vec2{-a.x, -a.y};
    }

    __host__ __device__ static inline vec3 operator-(const vec3& a)
    {
        return vec3{-a.x, -a.y, -a.z};
    }

    __host__ __device__ static inline vec4 operator-(const vec4& a)
    {
        return vec4{-a.x, -a.y, -a.z, -a.w};
    }

    /* Vector component-wise multiplication */

    __host__ __device__ static inline vec2 operator*(const vec2& a, const vec2& b)
    {
        return vec2{a.x * b.x, a.y * b.y};
    }

    __host__ __device__ static inline vec3 operator*(const vec3& a, const vec3& b)
    {
        return vec3{a.x * b.x, a.y * b.y, a.z * b.z};
    }

    __host__ __device__ static inline vec4 operator*(const vec4& a, const vec4& b)
    {
        return vec4{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    __host__ __device__ static inline vec2 operator*(scalar a, const vec2& b)
    {
        return vec2{a * b.x, a * b.y};
    }

    __host__ __device__ static inline vec3 operator*(scalar a, const vec3& b)
    {
        return vec3{a * b.x, a * b.y, a * b.z};
    }

    __host__ __device__ static inline vec4 operator*(scalar a, const vec4& b)
    {
        return vec4{a * b.x, a * b.y, a * b.z, a * b.w};
    }

    __host__ __device__ static inline vec2 operator*(const vec2& a, scalar b)
    {
        return vec2{a.x * b, a.y * b};
    }

    __host__ __device__ static inline vec3 operator*(const vec3& a, scalar b)
    {
        return vec3{a.x * b, a.y * b, a.z * b};
    }

    __host__ __device__ static inline vec4 operator*(const vec4& a, scalar b)
    {
        return vec4{a.x * b, a.y * b, a.z * b, a.w * b};
    }

    /* Vector component-wise division */

    __host__ __device__ static inline vec2 operator/(const vec2& a, const vec2& b)
    {
        return vec2{a.x / b.x, a.y / b.y};
    }

    __host__ __device__ static inline vec3 operator/(const vec3& a, const vec3& b)
    {
        return vec3{a.x / b.x, a.y / b.y, a.z / b.z};
    }

    __host__ __device__ static inline vec4 operator/(const vec4& a, const vec4& b)
    {
        return vec4{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
    }

    __host__ __device__ static inline vec2 operator/(scalar a, const vec2& b)
    {
        return vec2{a / b.x, a / b.y};
    }

    __host__ __device__ static inline vec3 operator/(scalar a, const vec3& b)
    {
        return vec3{a / b.x, a / b.y, a / b.z};
    }

    __host__ __device__ static inline vec4 operator/(scalar a, const vec4& b)
    {
        return vec4{a / b.x, a / b.y, a / b.z, a / b.w};
    }

    __host__ __device__ static inline vec2 operator/(const vec2& a, scalar b)
    {
        return vec2{a.x / b, a.y / b};
    }

    __host__ __device__ static inline vec3 operator/(const vec3& a, scalar b)
    {
        return vec3{a.x / b, a.y / b, a.z / b};
    }

    __host__ __device__ static inline vec4 operator/(const vec4& a, scalar b)
    {
        return vec4{a.x / b, a.y / b, a.z / b, a.w / b};
    }

    /* Vector functions */

    __host__ __device__ static inline scalar dot(const vec2& a, const vec2& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    __host__ __device__ static inline scalar dot(const vec3& a, const vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    __host__ __device__ static inline scalar dot(const vec4& a, const vec4& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    __host__ __device__ static inline scalar length(const vec2& a)
    {
        return sqrt(a.x * a.x + a.y * a.y);
    }

    __host__ __device__ static inline scalar length(const vec3& a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    __host__ __device__ static inline scalar length(const vec4& a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
    }

    __host__ __device__ static inline scalar length_sqr(const vec2& a)
    {
        return a.x * a.x + a.y * a.y;
    }

    __host__ __device__ static inline scalar length_sqr(const vec3& a)
    {
        return a.x * a.x + a.y * a.y + a.z * a.z;
    }

    __host__ __device__ static inline scalar length_sqr(const vec4& a)
    {
        return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
    }

    __host__ __device__ static inline vec2 normalize(const vec2& a)
    {
        scalar invlen = 1 / length(a);
        return a * invlen;
    }

    __host__ __device__ static inline vec3 normalize(const vec3& a)
    {
        scalar invlen = 1 / length(a);
        return a * invlen;
    }

    __host__ __device__ static inline vec4 normalize(const vec4& a)
    {
        scalar invlen = 1 / length(a);
        return a * invlen;
    }

    /* Matrix operations */

    struct matrix3
    {
        __host__ __device__ float3 m[3];
    };

    struct matrix4
    {
        __host__ __device__ float4 m[4];
    };
    
    __host__ __device__ static inline matrix3 transpose(const matrix3& m)
    {
        matrix3 transpose;
        transpose.m[0].x = m.m[0].x;
        transpose.m[0].y = m.m[1].x;
        transpose.m[0].z = m.m[2].x;
        transpose.m[1].x = m.m[0].y;
        transpose.m[1].y = m.m[1].y;
        transpose.m[1].z = m.m[2].y;
        transpose.m[2].x = m.m[0].z;
        transpose.m[2].y = m.m[1].z;
        transpose.m[2].z = m.m[2].z;
        return transpose;
    }

    __host__ __device__ static inline matrix4 transpose(const matrix4& m)
    {
        matrix4 transpose;
        transpose.m[0].x = m.m[0].x;
        transpose.m[0].y = m.m[1].x;
        transpose.m[0].z = m.m[2].x;
        transpose.m[0].w = m.m[3].x;
        transpose.m[1].x = m.m[0].y;
        transpose.m[1].y = m.m[1].y;
        transpose.m[1].z = m.m[2].y;
        transpose.m[1].w = m.m[3].y;
        transpose.m[2].x = m.m[0].z;
        transpose.m[2].y = m.m[1].z;
        transpose.m[2].z = m.m[2].z;
        transpose.m[2].w = m.m[3].z;
        transpose.m[3].x = m.m[0].w;
        transpose.m[3].y = m.m[1].w;
        transpose.m[3].z = m.m[2].w;
        transpose.m[3].w = m.m[3].w;
        return transpose;
    }

    __host__ __device__ static inline vec3 operator*(const vec3& a, const matrix3& b)
    {
        return vec3
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z
        };
    }

    __host__ __device__ static inline vec3 operator*(const matrix3& a, const vec3& b)
    {
        return vec3
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z
        };
    }

    __host__ __device__ static inline vec4 operator*(const vec4& a, const matrix4& b)
    {
        return vec4
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x + a.w * b.m[3].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y + a.w * b.m[3].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z + a.w * b.m[3].z,
            a.x * b.m[0].w + a.y * b.m[1].w + a.z * b.m[2].w + a.w * b.m[3].w
        };
    }

    __host__ __device__ static inline vec4 operator*(const matrix4& a, const vec4& b)
    {
        return vec4
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z + a.m[0].w * b.w,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z + a.m[1].w * b.w,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z + a.m[2].w * b.w,
            a.m[3].x * b.x + a.m[3].y * b.y + a.m[3].z * b.z + a.m[3].w * b.w
        };
    }

    /* Output to stream */

    __host__ static inline std::ostream& operator<< (std::ostream& stream, const vec2& v)
    {
        stream << "(" << v.x << ", " << v.y << ")";

        return stream;
    }

    __host__ static inline std::ostream& operator<< (std::ostream& stream, const vec3& v)
    {
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";

        return stream;
    }

    __host__ static inline std::ostream& operator<< (std::ostream& stream, const vec4& v)
    {
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";

        return stream;
    }

    __host__ static inline std::ostream& operator<< (std::ostream& stream, const matrix3& m)
    {
        stream << "[" << m.m[0].x << ", " << m.m[0].y << ", " << m.m[0].z << "]\n";
        stream << "[" << m.m[1].x << ", " << m.m[1].y << ", " << m.m[1].z << "]\n";
        stream << "[" << m.m[2].x << ", " << m.m[2].y << ", " << m.m[2].z << "]";

        return stream;
    }

    __host__ static inline std::ostream& operator<< (std::ostream& stream, const matrix4& m)
    {
        stream << "[" << m.m[0].x << ", " << m.m[0].y << ", " << m.m[0].z << ", " << m.m[0].w << "]\n";
        stream << "[" << m.m[1].x << ", " << m.m[1].y << ", " << m.m[1].z << ", " << m.m[1].w << "]\n";
        stream << "[" << m.m[2].x << ", " << m.m[2].y << ", " << m.m[2].z << ", " << m.m[2].w << "]\n";
        stream << "[" << m.m[3].x << ", " << m.m[3].y << ", " << m.m[3].z << ", " << m.m[3].w << "]";

        return stream;
    }
}