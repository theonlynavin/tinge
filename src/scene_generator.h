#pragma once

#include "objects.h"
#include <vector>

enum struct Scene
{
    CORNELL,
    TEAPOT,
    MONKEY,
    COLOR_BOX
};

void generate_scene(Camera& cam, std::vector<obj_pointer> &shapes, Scene kind);
