#ifndef TINGE_UTIL_H
#define TINGE_UTIL_H

#include "core.h"
#include <math.h>
#include <iostream>

namespace tinge
{
    /* Vector operations */

    typedef float2 vec2;
    typedef float3 vec3;
    typedef float4 vec4;

    typedef float scalar;

    __host__ __device__ static inline vec2 make_vec2(scalar x)
    {
        return vec2{x, x};
    }

    __host__ __device__ static inline vec2 make_vec2(scalar x, scalar y)
    {
        return vec2{x, y};
    }

    __host__ __device__ static inline vec3 make_vec3(scalar x)
    {
        return vec3{x, x, x};
    }

    __host__ __device__ static inline vec3 make_vec3(scalar x, scalar y, scalar z)
    {
        return vec3{x, y, z};
    }

    __host__ __device__ static inline vec4 make_vec4(scalar x)
    {
        return vec4{x, x, x, x};
    }

    __host__ __device__ static inline vec4 make_vec4(scalar x, scalar y, scalar z, scalar w)
    {
        return vec4{x, y, z, w};
    }

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

    /* Quaternion */

    typedef float4 quatn;

    __host__ __device__ static inline quatn conjugate(const quatn& q)
    {
        return quatn{-q.x, -q.y, -q.z, q.w};
    }

    __host__ __device__ static inline quatn axis_angle(const vec3& axis, scalar angle)
    {
        scalar halfAngle = 0.5 * angle;
        scalar sha = sin(halfAngle);

        return quatn{axis.x * sha, axis.y * sha, axis.z * sha, cos(halfAngle)};
    }

    __host__ __device__ static inline quatn euler_angles(scalar u, scalar v, scalar w)
    {
        scalar u2 = 0.5 * u, v2 = 0.5 * v, w2 = 0.5 * w;
        scalar su2 = sin(u2), sv2 = sin(v2), sw2 = sin(w2);
        scalar cu2 = cos(u2), cv2 = cos(v2), cw2 = cos(w2);

        return quatn{
        su2 * cv2 * cw2 - cu2 * sv2 * sw2,
        cu2 * sv2 * cw2 + su2 * cv2 * sw2,
        cu2 * cv2 * sw2 - su2 * sv2 * cw2,
        cu2 * cv2 * cw2 + su2 * sv2 * sw2};
    }

    /* Matrix operations */

    struct mat3
    {
        float3 m[3] = {float3{1, 0, 0}, 
                    float3{0, 1, 0}, 
                    float3{0, 0, 1}};    // rows of the matrix
    };

    struct mat4
    {
        float4 m[4] = {float4{1, 0, 0, 0}, 
                    float4{0, 1, 0, 0}, 
                    float4{0, 0, 1, 0}, 
                    float4{0, 0, 0, 1}};    // rows of the matrix
    };
    
    __host__ __device__ static inline mat3 transpose(const mat3& m)
    {
        mat3 transpose;
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

    __host__ __device__ static inline mat4 transpose(const mat4& m)
    {
        mat4 transpose;
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

    /* Matrix addition */

    __host__ __device__ static inline mat3 operator+(const mat3& a, const mat3& b)
    {
        mat3 m;

        m.m[0] = a.m[0] + b.m[0];
        m.m[1] = a.m[1] + b.m[1];
        m.m[2] = a.m[2] + b.m[2];

        return m;
    }

    __host__ __device__ static inline mat4 operator+(const mat4& a, const mat4& b)
    {
        mat4 m;

        m.m[0] = a.m[0] + b.m[0];
        m.m[1] = a.m[1] + b.m[1];
        m.m[2] = a.m[2] + b.m[2];
        m.m[3] = a.m[3] + b.m[3];

        return m;
    }

    /* Matrix subtraction */

    __host__ __device__ static inline mat3 operator-(const mat3& a, const mat3& b)
    {
        mat3 m;

        m.m[0] = a.m[0] - b.m[0];
        m.m[1] = a.m[1] - b.m[1];
        m.m[2] = a.m[2] - b.m[2];

        return m;
    }

    __host__ __device__ static inline mat4 operator-(const mat4& a, const mat4& b)
    {
        mat4 m;

        m.m[0] = a.m[0] - b.m[0];
        m.m[1] = a.m[1] - b.m[1];
        m.m[2] = a.m[2] - b.m[2];
        m.m[3] = a.m[3] - b.m[3];

        return m;
    }

    /* Matrix multiplication */

    __host__ __device__ static inline mat3 operator*(const mat3& a, const mat3& b)
    {
        mat3 m;

        m.m[0].x = a.m[0].x * b.m[0].x + a.m[0].y * b.m[1].x + a.m[0].z * b.m[2].x;
        m.m[0].y = a.m[0].x * b.m[0].y + a.m[0].y * b.m[1].y + a.m[0].z * b.m[2].y;
        m.m[0].z = a.m[0].x * b.m[0].z + a.m[0].y * b.m[1].z + a.m[0].z * b.m[2].z;

        m.m[1].x = a.m[1].x * b.m[0].x + a.m[1].y * b.m[1].x + a.m[1].z * b.m[2].x;
        m.m[1].y = a.m[1].x * b.m[0].y + a.m[1].y * b.m[1].y + a.m[1].z * b.m[2].y;
        m.m[1].z = a.m[1].x * b.m[0].z + a.m[1].y * b.m[1].z + a.m[1].z * b.m[2].z;

        m.m[0].x = a.m[2].x * b.m[0].x + a.m[1].y * b.m[1].x + a.m[2].z * b.m[2].x;
        m.m[0].y = a.m[2].x * b.m[0].y + a.m[1].y * b.m[1].y + a.m[2].z * b.m[2].y;
        m.m[0].z = a.m[2].x * b.m[0].z + a.m[1].y * b.m[1].z + a.m[2].z * b.m[2].z;

        return m;
        
    }

    __host__ __device__ static inline mat4 operator*(const mat4& a, const mat4& b)
    {
        mat4 m;

        m.m[0].x = a.m[0].x * b.m[0].x + a.m[0].y * b.m[1].x + a.m[0].z * b.m[2].x + a.m[0].w * b.m[3].x;
        m.m[0].y = a.m[0].x * b.m[0].y + a.m[0].y * b.m[1].y + a.m[0].z * b.m[2].y + a.m[0].w * b.m[3].y;
        m.m[0].z = a.m[0].x * b.m[0].z + a.m[0].y * b.m[1].z + a.m[0].z * b.m[2].z + a.m[0].w * b.m[3].z;
        m.m[0].w = a.m[0].x * b.m[0].w + a.m[0].y * b.m[1].w + a.m[0].z * b.m[2].w + a.m[0].w * b.m[3].w;
        
        m.m[1].x = a.m[1].x * b.m[0].x + a.m[1].y * b.m[1].x + a.m[1].z * b.m[2].x + a.m[1].w * b.m[3].x;
        m.m[1].y = a.m[1].x * b.m[0].y + a.m[1].y * b.m[1].y + a.m[1].z * b.m[2].y + a.m[1].w * b.m[3].y;
        m.m[1].z = a.m[1].x * b.m[0].z + a.m[1].y * b.m[1].z + a.m[1].z * b.m[2].z + a.m[1].w * b.m[3].z;
        m.m[1].w = a.m[1].x * b.m[0].w + a.m[1].y * b.m[1].w + a.m[1].z * b.m[2].w + a.m[1].w * b.m[3].w;

        m.m[2].x = a.m[2].x * b.m[0].x + a.m[2].y * b.m[1].x + a.m[2].z * b.m[2].x + a.m[2].w * b.m[3].x;
        m.m[2].y = a.m[2].x * b.m[0].y + a.m[2].y * b.m[1].y + a.m[2].z * b.m[2].y + a.m[2].w * b.m[3].y;
        m.m[2].z = a.m[2].x * b.m[0].z + a.m[2].y * b.m[1].z + a.m[2].z * b.m[2].z + a.m[2].w * b.m[3].z;
        m.m[2].w = a.m[2].x * b.m[0].w + a.m[2].y * b.m[1].w + a.m[2].z * b.m[2].w + a.m[2].w * b.m[3].w;

        m.m[3].x = a.m[3].x * b.m[0].x + a.m[3].y * b.m[1].x + a.m[3].z * b.m[2].x + a.m[3].w * b.m[3].x;
        m.m[3].y = a.m[3].x * b.m[0].y + a.m[3].y * b.m[1].y + a.m[3].z * b.m[2].y + a.m[3].w * b.m[3].y;
        m.m[3].z = a.m[3].x * b.m[0].z + a.m[3].y * b.m[1].z + a.m[3].z * b.m[2].z + a.m[3].w * b.m[3].z;
        m.m[3].w = a.m[3].x * b.m[0].w + a.m[3].y * b.m[1].w + a.m[3].z * b.m[2].w + a.m[3].w * b.m[3].w;

        return m;
        
    }

    __host__ __device__ static inline mat3 operator*(const mat3& a, scalar b)
    {
        mat3 m = a;

        m.m[0] = m.m[0] * b;
        m.m[1] = m.m[1] * b;
        m.m[2] = m.m[2] * b;

        return m;
    }

    __host__ __device__ static inline mat4 operator*(const mat4& a, scalar b)
    {
        mat4 m = a;

        m.m[0] = m.m[0] * b;
        m.m[1] = m.m[1] * b;
        m.m[2] = m.m[2] * b;
        m.m[3] = m.m[3] * b;

        return m;
    }

    __host__ __device__ static inline mat3 operator/(const mat3& a, scalar b)
    {
        mat3 m = a;

        m.m[0] = m.m[0] / b;
        m.m[1] = m.m[1] / b;
        m.m[2] = m.m[2] / b;

        return m;
    }

    __host__ __device__ static inline mat4 operator/(const mat4& a, scalar b)
    {
        mat4 m = a;

        m.m[0] = m.m[0] / b;
        m.m[1] = m.m[1] / b;
        m.m[2] = m.m[2] / b;
        m.m[3] = m.m[3] / b;

        return m;
    }

    __host__ __device__ static inline mat3 operator*(scalar a, const mat3& b)
    {
        mat3 m = b;

        m.m[0] = m.m[0] * a;
        m.m[1] = m.m[1] * a;
        m.m[2] = m.m[2] * a;

        return m;
    }

    __host__ __device__ static inline mat4 operator*(scalar a, const mat4& b)
    {
        mat4 m = b;

        m.m[0] = m.m[0] * a;
        m.m[1] = m.m[1] * a;
        m.m[2] = m.m[2] * a;
        m.m[3] = m.m[3] * a;

        return m;
    }

    __host__ __device__ static inline vec3 operator*(const vec3& a, const mat3& b)
    {
        return vec3
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z
        };
    }

    __host__ __device__ static inline vec3 operator*(const mat3& a, const vec3& b)
    {
        return vec3
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z
        };
    }

    __host__ __device__ static inline vec4 operator*(const vec4& a, const mat4& b)
    {
        return vec4
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x + a.w * b.m[3].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y + a.w * b.m[3].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z + a.w * b.m[3].z,
            a.x * b.m[0].w + a.y * b.m[1].w + a.z * b.m[2].w + a.w * b.m[3].w
        };
    }

    __host__ __device__ static inline vec3 operator*(const vec3& a, const mat4& b)
    {
        return vec3
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x + b.m[3].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y + b.m[3].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z + b.m[3].z,
        };
    }

    __host__ __device__ static inline vec4 operator*(const mat4& a, const vec4& b)
    {
        return vec4
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z + a.m[0].w * b.w,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z + a.m[1].w * b.w,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z + a.m[2].w * b.w,
            a.m[3].x * b.x + a.m[3].y * b.y + a.m[3].z * b.z + a.m[3].w * b.w
        };
    }

    __host__ __device__ static inline vec3 operator*(const mat4& a, const vec3& b)
    {
        return vec3
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z + a.m[0].w,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z + a.m[1].w,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z + a.m[2].w
        };
    }

    /* Transformation functions */

    __host__ __device__ static inline mat4 make_identity()
    {
        mat4 m;
        m.m[0].x = 1;
        m.m[1].y = 1;
        m.m[2].z = 1;
        m.m[3].w = 1;
        return m;
    }

    __host__ __device__ static inline mat4 make_rotation(const quatn& q)
    {
        mat4 m;
        m.m[0].x = 1 - 2*q.y*q.y - 2*q.z*q.z;
        m.m[0].y = 2*q.x*q.y - 2*q.w*q.z;
        m.m[0].z = 2*q.x*q.z + 2*q.w*q.y;

        m.m[1].x = 2*q.x*q.y + 2*q.w*q.z;
        m.m[1].y = 1 - 2*q.x*q.x - 2*q.z*q.z;
        m.m[1].z = 2*q.y*q.z - 2*q.w*q.x;

        m.m[2].x = 2*q.x*q.z - 2*q.w*q.y;
        m.m[2].y = 2*q.y*q.z + 2*q.w*q.x;
        m.m[2].z = 1 - 2*q.x*q.x - 2*q.y*q.y;

        m.m[3].w = 1;

        return m;
    }

    __host__ __device__ static inline mat4 make_scale(const vec3& scale)
    {
        mat4 m;
        m.m[0].x = scale.x;
        m.m[1].y = scale.y;
        m.m[2].z = scale.z;
        m.m[3].w = 1;
        return m;
    }

    __host__ __device__ static inline mat4 make_translation(const vec3& translation)
    {
        mat4 m;
        m.m[0].w = translation.x;
        m.m[1].w = translation.y;
        m.m[2].w = translation.z;
        m.m[3].w = 1;
        return m;
    }


    __host__ __device__ static inline mat4 make_transformation(const vec3& translation, const quatn& rotation, const vec3& scale)
    {
        return  make_translation(translation) * make_rotation(rotation) * make_scale(scale);
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

    __host__ static inline std::ostream& operator<< (std::ostream& stream, const mat3& m)
    {
        stream << "[" << m.m[0].x << ", " << m.m[0].y << ", " << m.m[0].z << "]\n";
        stream << "[" << m.m[1].x << ", " << m.m[1].y << ", " << m.m[1].z << "]\n";
        stream << "[" << m.m[2].x << ", " << m.m[2].y << ", " << m.m[2].z << "]";

        return stream;
    }

    __host__ static inline std::ostream& operator<< (std::ostream& stream, const mat4& m)
    {
        stream << "[" << m.m[0].x << ", " << m.m[0].y << ", " << m.m[0].z << ", " << m.m[0].w << "]\n";
        stream << "[" << m.m[1].x << ", " << m.m[1].y << ", " << m.m[1].z << ", " << m.m[1].w << "]\n";
        stream << "[" << m.m[2].x << ", " << m.m[2].y << ", " << m.m[2].z << ", " << m.m[2].w << "]\n";
        stream << "[" << m.m[3].x << ", " << m.m[3].y << ", " << m.m[3].z << ", " << m.m[3].w << "]";

        return stream;
    }
}

#endif