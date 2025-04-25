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
    bool use_env_light = false;
    static Vec3 sky_top_color;
    static Vec3 sky_bottom_color;
                   
    static void env_light();
    static Vec3 env_light_gradient(const Vec3& dir);
    static void env_map(const std::string& envmap_file_path);
    static Vec3 illuminance(const IntersectionOut &surface, int max_depth,
                            const std::vector<obj_pointer> &shapes,
                            Random &radom_generator);

    static void cleanup(); 
};
