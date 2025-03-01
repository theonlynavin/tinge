#pragma once

#include <iostream>

#define _USE_MATH_DEFINES
#define TINGE_EPSILON 1e-8f
#include <cmath>

// A three dimensional vector
struct Vec3
{
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Returns the L-2 norm of the vector
    inline float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Returns a normalized version of the vector
    inline Vec3 normalized() const
    {
        float len = length();
        return (len > 0) ? Vec3(x / len, y / len, z / len) : Vec3();
    }
};

// A four dimensional vector
struct Vec4
{
    float x, y, z, w;

    Vec4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}

    // Returns the L-2 norm of the vector
    inline float length() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    // Returns a normalized version of the vector
    inline Vec4 normalized() const
    {
        float len = length();
        return (len > 0) ? Vec4(x / len, y / len, z / len, w / len) : Vec4();
    }
};

// Negation operators

inline Vec3 operator-(const Vec3 &v) { return Vec3(-v.x, -v.y, -v.z); }
inline Vec4 operator-(const Vec4 &v) { return Vec4(-v.x, -v.y, -v.z, -v.w); }

// Standard vector arithmetic and comparision

inline Vec3 operator+(const Vec3 &a, const Vec3 &b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vec3 operator-(const Vec3 &a, const Vec3 &b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec3 operator*(const Vec3 &a, float scalar) { return Vec3(a.x * scalar, a.y * scalar, a.z * scalar); }
inline Vec3 operator/(const Vec3 &a, float scalar) { return (scalar != 0) ? Vec3(a.x / scalar, a.y / scalar, a.z / scalar) : Vec3(); }
inline bool operator==(const Vec3 &a, const Vec3 &b) { return (a.x == b.x && a.y == b.y && a.z == b.z); }

inline Vec4 operator+(const Vec4 &a, const Vec4 &b) { return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline Vec4 operator-(const Vec4 &a, const Vec4 &b) { return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline Vec4 operator*(const Vec4 &a, float scalar) { return Vec4(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar); }
inline Vec4 operator/(const Vec4 &a, float scalar) { return (scalar != 0) ? Vec4(a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar) : Vec4(); }
inline bool operator==(const Vec4 &a, const Vec4 &b) { return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w); }

// Dot product of two vectors
inline static float dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product of two vectors
inline static Vec3 cross(const Vec3 &a, const Vec3 &b)
{
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}

// Dot product of two vectors
inline static float dot(const Vec4 &a, const Vec4 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Normalizes a vector and returns it
inline static Vec3 normalize(Vec3 &v)
{
    v = v.normalized();
    return v;
}

// Normalizes a vector and returns it
inline static Vec4 normalize(Vec4 &v)
{
    v = v.normalized();
    return v.normalized();
}

struct Mat3
{
    float m[3][3]{};

    Mat3() : m{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} {}

    inline float *operator[](int i) { return m[i]; }

    const float *operator[](int i) const { return m[i]; }
    
    // Transpose of the matrix
    inline Mat3 transpose() const
    {
        Mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[j][i] = m[i][j];
        return result;
    }

    // Inverse of the matrix
    Mat3 inverse() const
    {
        // Calculate the determinant
        float det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

        if (det < TINGE_EPSILON)
        {
            throw std::runtime_error("Matrix is singular, cannot find inverse.");
        }

        // Inverse of the matrix
        Mat3 inv;
        inv.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) / det;
        inv.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) / det;
        inv.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;
        inv.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) / det;
        inv.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
        inv.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) / det;
        inv.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) / det;
        inv.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) / det;
        inv.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det;

        return inv;
    }
};

struct Mat4
{
    float m[4][4]{};

    Mat4() : m{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} {}

    inline float *operator[](int i) { return m[i]; }

    const float *operator[](int i) const { return m[i]; }

    // Transpose of the matrix
    Mat4 transpose() const
    {
        Mat4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.m[j][i] = m[i][j];
        return result;
    }

    // Inverse of the matrix
    // Credit to https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix for the painful work
    Mat4 inverse() const
    {
        float A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
        float A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
        float A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
        float A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
        float A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
        float A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
        float A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
        float A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
        float A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
        float A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
        float A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
        float A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        float A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
        float A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
        float A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
        float A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
        float A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
        float A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

        // Calculate the determinant
        float det = m[0][0] * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223) - m[0][1] * (m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223) + m[0][2] * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123) - m[0][3] * (m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);

        if (det < TINGE_EPSILON)
        {
            throw std::runtime_error("Matrix is singular, cannot find inverse.");
        }

        // Inverse of the matrix
        Mat4 inv;
        float invdet = 1 / det;
        inv.m[0][0] = invdet * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223);
        inv.m[0][1] = invdet * -(m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223);
        inv.m[0][2] = invdet * (m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213);
        inv.m[0][3] = invdet * -(m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212);
        inv.m[1][0] = invdet * -(m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223);
        inv.m[1][1] = invdet * (m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223);
        inv.m[1][2] = invdet * -(m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213);
        inv.m[1][3] = invdet * (m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212);
        inv.m[2][0] = invdet * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123);
        inv.m[2][1] = invdet * -(m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123);
        inv.m[2][2] = invdet * (m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113);
        inv.m[2][3] = invdet * -(m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112);
        inv.m[3][0] = invdet * -(m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);
        inv.m[3][1] = invdet * (m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123);
        inv.m[3][2] = invdet * -(m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113);
        inv.m[3][3] = invdet * (m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112);

        return inv;
    };
};

// Inverse and transpose utilities for convenience

inline static Mat3 inverse(const Mat3 &m) { return m.inverse(); }

inline static Mat4 inverse(const Mat4 &m) { return m.inverse(); }

inline static Mat3 transpose(const Mat3 &m) { return m.transpose(); }

inline static Mat4 transpose(const Mat4 &m) { return m.transpose(); }

// Negation operators

inline Mat3 operator-(const Mat3 &m)
{
    Mat3 result;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            result.m[i][j] = -m.m[i][j];
    return result;
}

inline Mat4 operator-(const Mat4 &m)
{
    Mat4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            result.m[i][j] = -m.m[i][j];
    return result;
}

// Standard arithmetic and comparision operators

inline Mat3 operator+(const Mat3 &a, const Mat3 &b)
{
    Mat3 result;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            result.m[i][j] = a.m[i][j] + b.m[i][j];
    return result;
}

inline Mat3 operator-(const Mat3 &a, const Mat3 &b)
{
    Mat3 result;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            result.m[i][j] = a.m[i][j] - b.m[i][j];
    return result;
}

inline Mat3 operator*(const Mat3 &a, const Mat3 &b)
{
    Mat3 result;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            result.m[i][j] = 0;
            for (int k = 0; k < 3; ++k)
                result.m[i][j] += a.m[i][k] * b.m[k][j];
        }
    return result;
}

inline Vec3 operator*(const Mat3 &a, const Vec3 &b)
{
    Vec3 result;
    result.x = a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z;
    result.y = a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z;
    result.z = a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z;
    return result;
}

inline Mat4 operator+(const Mat4 &a, const Mat4 &b)
{
    Mat4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            result.m[i][j] = a.m[i][j] + b.m[i][j];
    return result;
}

inline Mat4 operator-(const Mat4 &a, const Mat4 &b)
{
    Mat4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            result.m[i][j] = a.m[i][j] - b.m[i][j];
    return result;
}

inline Mat4 operator*(const Mat4 &a, const Mat4 &b)
{
    Mat4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k)
                result.m[i][j] += a.m[i][k] * b.m[k][j];
        }
    return result;
}

inline Vec3 operator*(const Mat4 &a, const Vec3 &b)
{
    Vec3 result;
    result.x = a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z + a.m[0][3];
    result.y = a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z + a.m[1][3];
    result.z = a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z + a.m[2][3];
    return result;
}

inline Vec4 operator*(const Mat4 &a, const Vec4 &b)
{
    Vec4 result;
    result.x = a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z + a.m[0][3] * b.w;
    result.y = a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z + a.m[1][3] * b.w;
    result.z = a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z + a.m[2][3] * b.w;
    result.w = a.m[3][0] * b.x + a.m[3][1] * b.y + a.m[3][2] * b.z + a.m[3][3] * b.w;
    return result;
}

// Frame transformation system
class Transform
{
public:
    /// @brief Returns a scaling transformation matrix
    /// @param sx Scaling in local x direction
    /// @param sy Scaling in local y direction
    /// @param sz Scaling in local z direction
    inline static Mat4 scale(float sx, float sy, float sz)
    {
        Mat4 result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;
        result.m[3][3] = 1;
        return result;
    }

    /// @brief Returns a scaling transformation matrix
    /// @param s Scaling vector
    inline static Mat4 scale(const Vec3 &s)
    {
        Mat4 result;
        result.m[0][0] = s.x;
        result.m[1][1] = s.y;
        result.m[2][2] = s.z;
        result.m[3][3] = 1;
        return result;
    }

    /// @brief Returns a translational transformation matrix
    /// @param tx Position in local x direction
    /// @param ty Position in local y direction
    /// @param tz Position in local z direction
    inline static Mat4 translate(float tx, float ty, float tz)
    {
        Mat4 result;
        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;
        return result;
    }

    /// @brief Returns a translational transformation matrix
    /// @param t Translation vector
    inline static Mat4 translate(const Vec3 &t)
    {
        Mat4 result;
        result.m[0][3] = t.x;
        result.m[1][3] = t.y;
        result.m[2][3] = t.z;
        return result;
    }

    /// @brief Returns a rotational transformation matrix
    /// @param roll Euler angle about z
    /// @param pitch Euler angle about x
    /// @param yaw Euler angle about y
    inline static Mat4 rotate(float roll, float pitch, float yaw)
    {
        Mat4 result;

        float cosRoll = cos(roll);
        float sinRoll = sin(roll);
        float cosPitch = cos(pitch);
        float sinPitch = sin(pitch);
        float cosYaw = cos(yaw);
        float sinYaw = sin(yaw);

        result.m[0][0] = cosYaw * cosPitch;
        result.m[0][1] = cosYaw * sinPitch * sinRoll - sinYaw * cosRoll;
        result.m[0][2] = cosYaw * sinPitch * cosRoll + sinYaw * sinRoll;
        result.m[0][3] = 0.0f;

        result.m[1][0] = sinYaw * cosPitch;
        result.m[1][1] = sinYaw * sinPitch * sinRoll + cosYaw * cosRoll;
        result.m[1][2] = sinYaw * sinPitch * cosRoll - cosYaw * sinRoll;
        result.m[1][3] = 0.0f;

        result.m[2][0] = -sinPitch;
        result.m[2][1] = cosPitch * sinRoll;
        result.m[2][2] = cosPitch * cosRoll;
        result.m[2][3] = 0.0f;

        result.m[3][0] = 0.0f;
        result.m[3][1] = 0.0f;
        result.m[3][2] = 0.0f;
        result.m[3][3] = 1.0f;

        return result;
    }
};