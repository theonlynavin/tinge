#pragma once

#include "camera.h"
#include "objects.h"
#include <vector>

/***********************
 * Static renderer class
 ***********************/
struct Renderer {
    /**********************
     * @brief Static function to render scene implements basic path tracer
     * @param camera The camera to render scene through
     * @param shapes List of shapes to render
     * @param outfile Filename for output file (.png)
     * @param out_width Width of output file in pixels
     * @param out_height Height of output file in pixels
     **********************/
    static void render(Camera camera,
                       const std::vector<AbstractShape *> &shapes,
                       const std::string &outfile, int out_width,
                       int out_height);
};
