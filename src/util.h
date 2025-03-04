#pragma once
#include "math.h"
#include <iostream>

/// @brief Returns a linear mix of v1 and v2
/// @param t Mix parameter
/// @return v1 * (1 - t) + v2 * t
inline static float mix(float v1, float v2, float t) {
  return v1 * (1 - t) + v2 * t;
}

/// @brief Returns a linear mix of v1 and v2
/// @param t Mix parameter
/// @return v1 * (1 - t) + v2 * t
inline static Vec3 mix(const Vec3 &v1, const Vec3 &v2, float t) {
  return v1 * (1 - t) + v2 * t;
}

/// @brief Returns a linear mix of v1 and v2
/// @param t Mix parameter
/// @return v1 * (1 - t) + v2 * t
inline static Vec4 mix(const Vec4 &v1, const Vec4 &v2, float t) {
  return v1 * (1 - t) + v2 * t;
}

/// @brief Returns v clamped to the range [v_min, v_max]
/// @param v The value to be clamped
/// @param v_min Minimum saturation
/// @param v_max Maximum saturation
inline static float clamp(float v, float v_min, float v_max) {
  return v < v_min ? v_min : (v > v_max ? v_max : v);
}

/// @brief Returns v clamped to the range [v_min, v_max] (component-wise)
/// @param v The vector to be clamped component-wise
/// @param v_min Minimum saturation components
/// @param v_max Maximum saturation components
inline static Vec3 clamp(const Vec3 &v, const Vec3 &v_min, const Vec3 &v_max) {
  return Vec3(clamp(v.x, v_min.x, v_max.x), clamp(v.y, v_min.y, v_max.y),
              clamp(v.z, v_min.z, v_max.z));
}
/// @brief Returns v clamped to the range [v_min, v_max] (component-wise)
/// @param v The vector to be clamped component-wise
/// @param v_min Minimum saturation components
/// @param v_max Maximum saturation components
inline static Vec4 clamp(const Vec4 &v, const Vec4 &v_min, const Vec4 &v_max) {
  return Vec4(clamp(v.x, v_min.x, v_max.x), clamp(v.y, v_min.y, v_max.y),
              clamp(v.z, v_min.z, v_max.z), clamp(v.w, v_min.w, v_max.w));
}

// Utility operator overloading for printing vectors and matrices onto a stream

std::ostream &operator<<(std::ostream &os, const Vec3 &vector);

std::ostream &operator<<(std::ostream &os, const Vec4 &vector);

std::ostream &operator<<(std::ostream &os, const Mat3 &matrix);

std::ostream &operator<<(std::ostream &os, const Mat4 &matrix);
