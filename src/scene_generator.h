#pragma once

#include "objects.h"
#include <vector>

enum Scene
{
    CORNELL,
    TEAPOT,
    MONKEY
};

void generate_scene(Camera& cam, std::vector<obj_pointer> &shapes, Scene kind);
