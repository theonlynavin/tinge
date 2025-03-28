#pragma once

#include "camera.h"
#include "material.h"
#include "objects.h"
#include <vector>

/***********************
 * Static renderer class
 ***********************/
struct Renderer {
    /**********************
     * @brief Static function to render scene implements basic path tracer
     * @param camera The camera to render scene through
     * @param shapes List of shared pointers to the shapes to render
     * @param outfile Filename for output file (.png)
     * @param out_width Width of output file in pixels
     * @param out_height Height of output file in pixels
     * @param env_light Use environment light if true and environment map if
     *false
     **********************/
    static void render(Camera camera, const std::vector<obj_pointer> &shapes,
                       const std::string &outfile, int out_width,
                       int out_height, bool env_light);

    static void env_light();
    static void env_map();
    static Vec3 illuminance(const IntersectionOut &surface, int max_depth,
                            const std::vector<obj_pointer> &shapes,
                            Random &radom_generator);
};
