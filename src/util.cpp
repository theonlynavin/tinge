#include "util.h"

inline static float mix(float v1, float v2, float t) {
  return v1 * (1 - t) + v2 * t;
}

inline static Vec3 mix(const Vec3 &v1, const Vec3 &v2, float t) {
  return v1 * (1 - t) + v2 * t;
}

inline static Vec4 mix(const Vec4 &v1, const Vec4 &v2, float t) {
  return v1 * (1 - t) + v2 * t;
}

inline static float clamp(float v, float v_min, float v_max) {
  return v < v_min ? v_min : (v > v_max ? v_max : v);
}

inline static Vec3 clamp(const Vec3 &v, const Vec3 &v_min, const Vec3 &v_max) {
  return Vec3(clamp(v.x, v_min.x, v_max.x), clamp(v.y, v_min.y, v_max.y),
              clamp(v.z, v_min.z, v_max.z));
}
inline static Vec4 clamp(const Vec4 &v, const Vec4 &v_min, const Vec4 &v_max) {
  return Vec4(clamp(v.x, v_min.x, v_max.x), clamp(v.y, v_min.y, v_max.y),
              clamp(v.z, v_min.z, v_max.z), clamp(v.w, v_min.w, v_max.w));
}

std::ostream &operator<<(std::ostream &os, const Vec3 &vector) {
  os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Vec4 &vector) {
  os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", "
     << vector.w << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Mat3 &matrix) {
  for (int i = 0; i < 3; ++i) {
    os << "[ ";
    for (int j = 0; j < 3; ++j) {
      os << matrix.m[i][j] << " ";
    }
    os << "]\n";
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const Mat4 &matrix) {
  for (int i = 0; i < 4; ++i) {
    os << "[ ";
    for (int j = 0; j < 4; ++j) {
      os << matrix.m[i][j] << " ";
    }
    os << "]\n";
  }
  return os;
}
