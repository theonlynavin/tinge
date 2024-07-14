#pragma once

#define GLM_FORCE_INLINE
#define GLM_FORCE_SWIZZLE

#ifdef TINGE_DEBUG
    #define GLM_ENABLE_EXPERIMENTAL
    #include <glm/gtx/string_cast.hpp>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/color_space.hpp>

#define TINGE_EPSILON 1e-6f