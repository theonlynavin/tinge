#include "util.h"

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
