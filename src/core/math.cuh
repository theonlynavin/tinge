#pragma once
#include <math.h>
#include <iostream>

namespace Tinge
{
    /* Vector operations */

    typedef float2 Vec2;
    typedef float3 Vec3;
    typedef float4 Vec4;

    typedef float Float;

    __host__ __device__ static __forceinline__ Vec2 makeVec2(Float x)
    {
        return Vec2{x, x};
    }

    __host__ __device__ static __forceinline__ Vec2 makeVec2(Float x, Float y)
    {
        return Vec2{x, y};
    }

    __host__ __device__ static __forceinline__ Vec3 makeVec3(Float x)
    {
        return Vec3{x, x, x};
    }

    __host__ __device__ static __forceinline__ Vec3 makeVec3(Float x, Float y, Float z)
    {
        return Vec3{x, y, z};
    }

    __host__ __device__ static __forceinline__ Vec4 makeVec4(Float x)
    {
        return Vec4{x, x, x, x};
    }

    __host__ __device__ static __forceinline__ Vec4 makeVec4(Float x, Float y, Float z, Float w)
    {
        return Vec4{x, y, z, w};
    }

    /* Vector addition */

    __host__ __device__ static __forceinline__ Vec2 operator+(const Vec2& a, const Vec2& b)
    {
        return Vec2{a.x + b.x, a.y + b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator+(const Vec3& a, const Vec3& b)
    {
        return Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator+(const Vec4& a, const Vec4& b)
    {
        return Vec4{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator+(Float a, const Vec2& b)
    {
        return Vec2{a + b.x, a + b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator+(Float a, const Vec3& b)
    {
        return Vec3{a + b.x, a + b.y, a + b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator+(Float a, const Vec4& b)
    {
        return Vec4{a + b.x, a + b.y, a + b.z, a + b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator+(const Vec2& a, Float b)
    {
        return Vec2{a.x + b, a.y + b};
    }

    __host__ __device__ static __forceinline__ Vec3 operator+(const Vec3& a, Float b)
    {
        return Vec3{a.x + b, a.y + b, a.z + b};
    }

    __host__ __device__ static __forceinline__ Vec4 operator+(const Vec4& a, Float b)
    {
        return Vec4{a.x + b, a.y + b, a.z + b, a.w + b};
    }

    /* Vector subtraction and negation */ 

    __host__ __device__ static __forceinline__ Vec2 operator-(const Vec2& a, const Vec2& b)
    {
        return Vec2{a.x - b.x, a.y - b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator-(const Vec3& a, const Vec3& b)
    {
        return Vec3{a.x - b.x, a.y - b.y, a.z - b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator-(const Vec4& a, const Vec4& b)
    {
        return Vec4{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator-(Float a, const Vec2& b)
    {
        return Vec2{a - b.x, a - b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator-(Float a, const Vec3& b)
    {
        return Vec3{a - b.x, a - b.y, a - b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator-(Float a, const Vec4& b)
    {
        return Vec4{a - b.x, a - b.y, a - b.z, a - b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator-(const Vec2& a, Float b)
    {
        return Vec2{a.x - b, a.y - b};
    }

    __host__ __device__ static __forceinline__ Vec3 operator-(const Vec3& a, Float b)
    {
        return Vec3{a.x - b, a.y - b, a.z - b};
    }

    __host__ __device__ static __forceinline__ Vec4 operator-(const Vec4& a, Float b)
    {
        return Vec4{a.x - b, a.y - b, a.z - b, a.w - b};
    }

    __host__ __device__ static __forceinline__ Vec2 operator-(const Vec2& a)
    {
        return Vec2{-a.x, -a.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator-(const Vec3& a)
    {
        return Vec3{-a.x, -a.y, -a.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator-(const Vec4& a)
    {
        return Vec4{-a.x, -a.y, -a.z, -a.w};
    }

    /* Vector component-wise multiplication */

    __host__ __device__ static __forceinline__ Vec2 operator*(const Vec2& a, const Vec2& b)
    {
        return Vec2{a.x * b.x, a.y * b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator*(const Vec3& a, const Vec3& b)
    {
        return Vec3{a.x * b.x, a.y * b.y, a.z * b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator*(const Vec4& a, const Vec4& b)
    {
        return Vec4{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator*(Float a, const Vec2& b)
    {
        return Vec2{a * b.x, a * b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator*(Float a, const Vec3& b)
    {
        return Vec3{a * b.x, a * b.y, a * b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator*(Float a, const Vec4& b)
    {
        return Vec4{a * b.x, a * b.y, a * b.z, a * b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator*(const Vec2& a, Float b)
    {
        return Vec2{a.x * b, a.y * b};
    }

    __host__ __device__ static __forceinline__ Vec3 operator*(const Vec3& a, Float b)
    {
        return Vec3{a.x * b, a.y * b, a.z * b};
    }

    __host__ __device__ static __forceinline__ Vec4 operator*(const Vec4& a, Float b)
    {
        return Vec4{a.x * b, a.y * b, a.z * b, a.w * b};
    }

    /* Vector component-wise division */

    __host__ __device__ static __forceinline__ Vec2 operator/(const Vec2& a, const Vec2& b)
    {
        return Vec2{a.x / b.x, a.y / b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator/(const Vec3& a, const Vec3& b)
    {
        return Vec3{a.x / b.x, a.y / b.y, a.z / b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator/(const Vec4& a, const Vec4& b)
    {
        return Vec4{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator/(Float a, const Vec2& b)
    {
        return Vec2{a / b.x, a / b.y};
    }

    __host__ __device__ static __forceinline__ Vec3 operator/(Float a, const Vec3& b)
    {
        return Vec3{a / b.x, a / b.y, a / b.z};
    }

    __host__ __device__ static __forceinline__ Vec4 operator/(Float a, const Vec4& b)
    {
        return Vec4{a / b.x, a / b.y, a / b.z, a / b.w};
    }

    __host__ __device__ static __forceinline__ Vec2 operator/(const Vec2& a, Float b)
    {
        return Vec2{a.x / b, a.y / b};
    }

    __host__ __device__ static __forceinline__ Vec3 operator/(const Vec3& a, Float b)
    {
        return Vec3{a.x / b, a.y / b, a.z / b};
    }

    __host__ __device__ static __forceinline__ Vec4 operator/(const Vec4& a, Float b)
    {
        return Vec4{a.x / b, a.y / b, a.z / b, a.w / b};
    }

    /* Vector functions */

    __host__ __device__ static __forceinline__ Float dot(const Vec2& a, const Vec2& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    __host__ __device__ static __forceinline__ Float dot(const Vec3& a, const Vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    __host__ __device__ static __forceinline__ Float dot(const Vec4& a, const Vec4& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    __host__ __device__ static __forceinline__ Float length(const Vec2& a)
    {
        return sqrt(a.x * a.x + a.y * a.y);
    }

    __host__ __device__ static __forceinline__ Float length(const Vec3& a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    __host__ __device__ static __forceinline__ Float length(const Vec4& a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
    }

    __host__ __device__ static __forceinline__ Float lengthSqr(const Vec2& a)
    {
        return a.x * a.x + a.y * a.y;
    }

    __host__ __device__ static __forceinline__ Float lengthSqr(const Vec3& a)
    {
        return a.x * a.x + a.y * a.y + a.z * a.z;
    }

    __host__ __device__ static __forceinline__ Float lengthSqr(const Vec4& a)
    {
        return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
    }

    __host__ __device__ static __forceinline__ Vec2 normalize(const Vec2& a)
    {
        Float invlen = 1 / length(a);
        return a * invlen;
    }

    __host__ __device__ static __forceinline__ Vec3 normalize(const Vec3& a)
    {
        Float invlen = 1 / length(a);
        return a * invlen;
    }

    __host__ __device__ static __forceinline__ Vec4 normalize(const Vec4& a)
    {
        Float invlen = 1 / length(a);
        return a * invlen;
    }

    /* Quaternion */

    typedef float4 Quaternion;

    __host__ __device__ static __forceinline__ Quaternion conjugate(const Quaternion& q)
    {
        return Quaternion{-q.x, -q.y, -q.z, q.w};
    }

    __host__ __device__ static __forceinline__ Quaternion axisAngle(const Vec3& axis, Float angle)
    {
        Float halfAngle = 0.5 * angle;
        Float sha = sin(halfAngle);

        return Quaternion{axis.x * sha, axis.y * sha, axis.z * sha, cos(halfAngle)};
    }

    __host__ __device__ static __forceinline__ Quaternion eulerAngles(Float u, Float v, Float w)
    {
        Float u2 = 0.5 * u, v2 = 0.5 * v, w2 = 0.5 * w;
        Float su2 = sin(u2), sv2 = sin(v2), sw2 = sin(w2);
        Float cu2 = cos(u2), cv2 = cos(v2), cw2 = cos(w2);

        return Quaternion{
        su2 * cv2 * cw2 - cu2 * sv2 * sw2,
        cu2 * sv2 * cw2 + su2 * cv2 * sw2,
        cu2 * cv2 * sw2 - su2 * sv2 * cw2,
        cu2 * cv2 * cw2 + su2 * sv2 * sw2};
    }

    /* Matrix operations */

    struct Matrix3
    {
        Vec3 m[3] = {Vec3{1, 0, 0}, 
                    Vec3{0, 1, 0}, 
                    Vec3{0, 0, 1}};    // rows of the matrix
    };

    struct Matrix4
    {
        Vec4 m[4] = {Vec4{1, 0, 0, 0}, 
                    Vec4{0, 1, 0, 0}, 
                    Vec4{0, 0, 1, 0}, 
                    Vec4{0, 0, 0, 1}};    // rows of the matrix
    };
    
    __host__ __device__ static __forceinline__ Matrix3 transpose(const Matrix3& m)
    {
        Matrix3 transpose;
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

    __host__ __device__ static __forceinline__ Matrix4 transpose(const Matrix4& m)
    {
        Matrix4 transpose;
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


    // Fast inverse for a 4x4 matrix
    // Thanks to https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix/44446912#44446912
    __host__ __device__ static __forceinline__ Matrix4 inverse(const Matrix4& m)
    {
        Float A2323 = m.m[2].z * m.m[3].w - m.m[2].w * m.m[3].z;
        Float A1323 = m.m[2].y * m.m[3].w - m.m[2].w * m.m[3].y;
        Float A1223 = m.m[2].y * m.m[3].z - m.m[2].z * m.m[3].y;
        Float A0323 = m.m[2].x * m.m[3].w - m.m[2].w * m.m[3].x;
        Float A0223 = m.m[2].x * m.m[3].z - m.m[2].z * m.m[3].x;
        Float A0123 = m.m[2].x * m.m[3].y - m.m[2].y * m.m[3].x;
        Float A2313 = m.m[1].z * m.m[3].w - m.m[1].w * m.m[3].z;
        Float A1313 = m.m[1].y * m.m[3].w - m.m[1].w * m.m[3].y;
        Float A1213 = m.m[1].y * m.m[3].z - m.m[1].z * m.m[3].y;
        Float A2312 = m.m[1].z * m.m[2].w - m.m[1].w * m.m[2].z;
        Float A1312 = m.m[1].y * m.m[2].w - m.m[1].w * m.m[2].y;
        Float A1212 = m.m[1].y * m.m[2].z - m.m[1].z * m.m[2].y;
        Float A0313 = m.m[1].x * m.m[3].w - m.m[1].w * m.m[3].x;
        Float A0213 = m.m[1].x * m.m[3].z - m.m[1].z * m.m[3].x;
        Float A0312 = m.m[1].x * m.m[2].w - m.m[1].w * m.m[2].x;
        Float A0212 = m.m[1].x * m.m[2].z - m.m[1].z * m.m[2].x;
        Float A0113 = m.m[1].x * m.m[3].y - m.m[1].y * m.m[3].x;
        Float A0112 = m.m[1].x * m.m[2].y - m.m[1].y * m.m[2].x;

        Float det = m.m[0].x * ( m.m[1].y * A2323 - m.m[1].z * A1323 + m.m[1].w * A1223 )
            - m.m[0].y * ( m.m[1].x * A2323 - m.m[1].z * A0323 + m.m[1].w * A0223 )
            + m.m[0].z * ( m.m[1].x * A1323 - m.m[1].y * A0323 + m.m[1].w * A0123 )
            - m.m[0].w * ( m.m[1].x * A1223 - m.m[1].y * A0223 + m.m[1].z * A0123 );
        det = 1 / det;

        Matrix4 im;
        im.m[0].x = det *   ( m.m[1].y * A2323 - m.m[1].z * A1323 + m.m[1].w * A1223 );
        im.m[0].y = det * - ( m.m[0].y * A2323 - m.m[0].z * A1323 + m.m[0].w * A1223 );
        im.m[0].z = det *   ( m.m[0].y * A2313 - m.m[0].z * A1313 + m.m[0].w * A1213 );
        im.m[0].w = det * - ( m.m[0].y * A2312 - m.m[0].z * A1312 + m.m[0].w * A1212 );
        im.m[1].x = det * - ( m.m[1].x * A2323 - m.m[1].z * A0323 + m.m[1].w * A0223 );
        im.m[1].y = det *   ( m.m[0].x * A2323 - m.m[0].z * A0323 + m.m[0].w * A0223 );
        im.m[1].z = det * - ( m.m[0].x * A2313 - m.m[0].z * A0313 + m.m[0].w * A0213 );
        im.m[1].w = det *   ( m.m[0].x * A2312 - m.m[0].z * A0312 + m.m[0].w * A0212 );
        im.m[2].x = det *   ( m.m[1].x * A1323 - m.m[1].y * A0323 + m.m[1].w * A0123 );
        im.m[2].y = det * - ( m.m[0].x * A1323 - m.m[0].y * A0323 + m.m[0].w * A0123 );
        im.m[2].z = det *   ( m.m[0].x * A1313 - m.m[0].y * A0313 + m.m[0].w * A0113 );
        im.m[2].w = det * - ( m.m[0].x * A1312 - m.m[0].y * A0312 + m.m[0].w * A0112 );
        im.m[3].x = det * - ( m.m[1].x * A1223 - m.m[1].y * A0223 + m.m[1].z * A0123 );
        im.m[3].y = det *   ( m.m[0].x * A1223 - m.m[0].y * A0223 + m.m[0].z * A0123 );
        im.m[3].z = det * - ( m.m[0].x * A1213 - m.m[0].y * A0213 + m.m[0].z * A0113 );
        im.m[3].w = det *   ( m.m[0].x * A1212 - m.m[0].y * A0212 + m.m[0].z * A0112 );

        return im;
    }

    /* Matrix addition */

    __host__ __device__ static __forceinline__ Matrix3 operator+(const Matrix3& a, const Matrix3& b)
    {
        Matrix3 m;

        m.m[0] = a.m[0] + b.m[0];
        m.m[1] = a.m[1] + b.m[1];
        m.m[2] = a.m[2] + b.m[2];

        return m;
    }

    __host__ __device__ static __forceinline__ Matrix4 operator+(const Matrix4& a, const Matrix4& b)
    {
        Matrix4 m;

        m.m[0] = a.m[0] + b.m[0];
        m.m[1] = a.m[1] + b.m[1];
        m.m[2] = a.m[2] + b.m[2];
        m.m[3] = a.m[3] + b.m[3];

        return m;
    }

    /* Matrix subtraction */

    __host__ __device__ static __forceinline__ Matrix3 operator-(const Matrix3& a, const Matrix3& b)
    {
        Matrix3 m;

        m.m[0] = a.m[0] - b.m[0];
        m.m[1] = a.m[1] - b.m[1];
        m.m[2] = a.m[2] - b.m[2];

        return m;
    }

    __host__ __device__ static __forceinline__ Matrix4 operator-(const Matrix4& a, const Matrix4& b)
    {
        Matrix4 m;

        m.m[0] = a.m[0] - b.m[0];
        m.m[1] = a.m[1] - b.m[1];
        m.m[2] = a.m[2] - b.m[2];
        m.m[3] = a.m[3] - b.m[3];

        return m;
    }

    /* Matrix multiplication */

    __host__ __device__ static __forceinline__ Matrix3 operator*(const Matrix3& a, const Matrix3& b)
    {
        Matrix3 m;

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

    __host__ __device__ static __forceinline__ Matrix4 operator*(const Matrix4& a, const Matrix4& b)
    {
        Matrix4 m;

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

    __host__ __device__ static __forceinline__ Matrix3 operator*(const Matrix3& a, Float b)
    {
        Matrix3 m = a;

        m.m[0] = m.m[0] * b;
        m.m[1] = m.m[1] * b;
        m.m[2] = m.m[2] * b;

        return m;
    }

    __host__ __device__ static __forceinline__ Matrix4 operator*(const Matrix4& a, Float b)
    {
        Matrix4 m = a;

        m.m[0] = m.m[0] * b;
        m.m[1] = m.m[1] * b;
        m.m[2] = m.m[2] * b;
        m.m[3] = m.m[3] * b;

        return m;
    }

    __host__ __device__ static __forceinline__ Matrix3 operator/(const Matrix3& a, Float b)
    {
        Matrix3 m = a;

        m.m[0] = m.m[0] / b;
        m.m[1] = m.m[1] / b;
        m.m[2] = m.m[2] / b;

        return m;
    }

    __host__ __device__ static __forceinline__ Matrix4 operator/(const Matrix4& a, Float b)
    {
        Matrix4 m = a;

        m.m[0] = m.m[0] / b;
        m.m[1] = m.m[1] / b;
        m.m[2] = m.m[2] / b;
        m.m[3] = m.m[3] / b;

        return m;
    }

    __host__ __device__ static __forceinline__ Matrix3 operator*(Float a, const Matrix3& b)
    {
        Matrix3 m = b;

        m.m[0] = m.m[0] * a;
        m.m[1] = m.m[1] * a;
        m.m[2] = m.m[2] * a;

        return m;
    }

    __host__ __device__ static __forceinline__ Matrix4 operator*(Float a, const Matrix4& b)
    {
        Matrix4 m = b;

        m.m[0] = m.m[0] * a;
        m.m[1] = m.m[1] * a;
        m.m[2] = m.m[2] * a;
        m.m[3] = m.m[3] * a;

        return m;
    }

    __host__ __device__ static __forceinline__ Vec3 operator*(const Vec3& a, const Matrix3& b)
    {
        return Vec3
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z
        };
    }

    __host__ __device__ static __forceinline__ Vec3 operator*(const Matrix3& a, const Vec3& b)
    {
        return Vec3
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z
        };
    }

    __host__ __device__ static __forceinline__ Vec4 operator*(const Vec4& a, const Matrix4& b)
    {
        return Vec4
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x + a.w * b.m[3].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y + a.w * b.m[3].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z + a.w * b.m[3].z,
            a.x * b.m[0].w + a.y * b.m[1].w + a.z * b.m[2].w + a.w * b.m[3].w
        };
    }

    __host__ __device__ static __forceinline__ Vec3 operator*(const Vec3& a, const Matrix4& b)
    {
        return Vec3
        {
            a.x * b.m[0].x + a.y * b.m[1].x + a.z * b.m[2].x + b.m[3].x,
            a.x * b.m[0].y + a.y * b.m[1].y + a.z * b.m[2].y + b.m[3].y,
            a.x * b.m[0].z + a.y * b.m[1].z + a.z * b.m[2].z + b.m[3].z,
        };
    }

    __host__ __device__ static __forceinline__ Vec4 operator*(const Matrix4& a, const Vec4& b)
    {
        return Vec4
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z + a.m[0].w * b.w,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z + a.m[1].w * b.w,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z + a.m[2].w * b.w,
            a.m[3].x * b.x + a.m[3].y * b.y + a.m[3].z * b.z + a.m[3].w * b.w
        };
    }

    __host__ __device__ static __forceinline__ Vec3 operator*(const Matrix4& a, const Vec3& b)
    {
        return Vec3
        {
            a.m[0].x * b.x + a.m[0].y * b.y + a.m[0].z * b.z,
            a.m[1].x * b.x + a.m[1].y * b.y + a.m[1].z * b.z,
            a.m[2].x * b.x + a.m[2].y * b.y + a.m[2].z * b.z
        };
    }

    /* Transformation functions */

    __host__ __device__ static __forceinline__ Matrix4 makeIdentity()
    {
        Matrix4 m;
        m.m[0].x = 1;
        m.m[1].y = 1;
        m.m[2].z = 1;
        m.m[3].w = 1;
        return m;
    }

    __host__ __device__ static __forceinline__ Matrix4 makeRotation(const Quaternion& q)
    {
        Matrix4 m;
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

    __host__ __device__ static __forceinline__ Matrix4 makeScale(const Vec3& scale)
    {
        Matrix4 m;
        m.m[0].x = scale.x;
        m.m[1].y = scale.y;
        m.m[2].z = scale.z;
        m.m[3].w = 1;
        return m;
    }

    __host__ __device__ static __forceinline__ Matrix4 makeTranslation(const Vec3& translation)
    {
        Matrix4 m;
        m.m[0].w = translation.x;
        m.m[1].w = translation.y;
        m.m[2].w = translation.z;
        m.m[3].w = 1;
        return m;
    }


    __host__ __device__ static __forceinline__ Matrix4 makeTransformation(const Vec3& translation, const Quaternion& rotation, const Vec3& scale)
    {
        return  makeTranslation(translation) * makeRotation(rotation) * makeScale(scale);
    }

    /* Math utils */

    template <typename T>
    __host__ __device__ static __forceinline__ T mix(const T& a, const T& b, Float t)
    {
        return a * (1 - t) + b * t;
    }

    /* Output to stream */

    __host__ static __forceinline__ std::ostream& operator<< (std::ostream& stream, const Vec2& v)
    {
        stream << "(" << v.x << ", " << v.y << ")";

        return stream;
    }

    __host__ static __forceinline__ std::ostream& operator<< (std::ostream& stream, const Vec3& v)
    {
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";

        return stream;
    }

    __host__ static __forceinline__ std::ostream& operator<< (std::ostream& stream, const Vec4& v)
    {
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";

        return stream;
    }

    __host__ static __forceinline__ std::ostream& operator<< (std::ostream& stream, const Matrix3& m)
    {
        stream << "[" << m.m[0].x << ", " << m.m[0].y << ", " << m.m[0].z << "]\n";
        stream << "[" << m.m[1].x << ", " << m.m[1].y << ", " << m.m[1].z << "]\n";
        stream << "[" << m.m[2].x << ", " << m.m[2].y << ", " << m.m[2].z << "]";

        return stream;
    }

    __host__ static __forceinline__ std::ostream& operator<< (std::ostream& stream, const Matrix4& m)
    {
        stream << "[" << m.m[0].x << ", " << m.m[0].y << ", " << m.m[0].z << ", " << m.m[0].w << "]\n";
        stream << "[" << m.m[1].x << ", " << m.m[1].y << ", " << m.m[1].z << ", " << m.m[1].w << "]\n";
        stream << "[" << m.m[2].x << ", " << m.m[2].y << ", " << m.m[2].z << ", " << m.m[2].w << "]\n";
        stream << "[" << m.m[3].x << ", " << m.m[3].y << ", " << m.m[3].z << ", " << m.m[3].w << "]";

        return stream;
    }
}