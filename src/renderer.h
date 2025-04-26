#pragma once

#include "camera.h"
#include "material.h"
#include "objects.h"
#include <vector>

/***********************
 * Static renderer class
 ***********************/
class Renderer {
public:
    /**********************
     * @brief Static function to render scene using a basic path tracer
     * @param camera The camera to render scene through
     * @param shapes List of shared pointers to the shapes to render
     * @param outfile Filename for output file (.png)
     * @param out_width Width of output file in pixels
     * @param out_height Height of output file in pixels
     * @param num_spp Number of samples for Monte Carlo Estimator
     * @param env_light Use environment light if true and environment map if
     *false
     **********************/
    static void render(Camera camera, const std::vector<obj_pointer> &shapes,
                       const std::string &outfile, int out_width,
                       int out_height, int num_spp, bool env_light, bool denoise);
    
    /**********************************************************************************
     * @brief Sets the sky color (if not using image based lighting)
     * @param sky_top_color Azimuth color
     * @param sky_bottom_color Horizon color
     **********************************************************************************/
    static void env_light(Vec3 sky_top_color, Vec3 sky_bottom_color);

    /**********************************************************************************
     * @brief Loads the HDR file and stores it internally
     * @param envmap_file_path Environment file path
     **********************************************************************************/
    static void env_map(const std::string& envmap_file_path);
    
    /**********************************************************************************
     * @brief Frees up allocated memory
    **********************************************************************************/
    static void cleanup(); 

private:
    static void render_thread(Camera camera, const std::vector<obj_pointer> &shapes,
                              unsigned char *data, int w1, int w2, int out_width,
                              int out_height, int num_samples, int depth);
    static Vec3 env_light_gradient(const Vec3& dir);
    static Vec3 illuminance(const IntersectionOut &surface, int max_depth,
                            const std::vector<obj_pointer> &shapes,
                            Random &radom_generator);
                            
    static Vec3 sky_top_color;
    static Vec3 sky_bottom_color;
};
