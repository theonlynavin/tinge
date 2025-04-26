#pragma once
#include "math.h"
struct Frame {
  public:
    Vec3 scale;     // Axes scaling
    Vec3 rotation;  // Euler angles 
    Vec3 origin;    // Position
    Mat4 frameToWorld, worldToFrame;

    Frame();

    /**************************************************************
    * @brief Computes the frameToWorld and worldToFrame matrices 
    * @note MUST be called if any changes are made to scale, origin, rotation
    *************************************************************/
    void lockFrame();
};
