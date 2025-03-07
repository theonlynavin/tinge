#pragma once
#include "math.h"
struct Frame {
  public:
    Vec3 scale;
    Vec3 rotation;
    Vec3 origin;
    Mat4 frameToWorld, worldToFrame;

    Frame();

    void lockFrame();
};
