#include "renderer.h"
#include "camera.h"
#include "material.h"
#include "math.h"
#include "util.h"
#include <ctime>
#include <iostream>
#include <mutex>
#include <ostream>
#include <algorithm>
#include <thread>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image/stb_image.h>

Vec3 Renderer::sky_top_color = Vec3(0.1, 0.5, 0.9);
Vec3 Renderer::sky_bottom_color = Vec3(1, 1, 1);

/*********************************************************************************
 *  env_width : width of environment image
 *  env_height : height of env. image
 *  env_channels : no of parameters used to represent a color
 *  env_data : pointer to the array having RGB details of the environment image
 **********************************************************************************/
int env_width, env_height, env_channels;
float *env_data = nullptr;

/*************************************
 * Used to show rendering progress
 *************************************/
std::mutex counter_mutex;
int counter = 0;

/**************************************
 * Mapping to environment
 * @par direction of the shooted ray
 * @return RGB value of the environment
 ****************************************/
Vec3 sample_env_map(const Vec3 &dir) {
    float theta = acos(clamp(dir.y, -1.0f, 1.0f)); // polar angle
    float phi = atan2(dir.z, dir.x);               // azimuth

    if (phi < 0)
        phi += 2 * M_PI; // makes phi>=0 and < 2pi

    float u = phi / (2 * M_PI);
    float v = theta / M_PI;

    int x = clamp(int(u * env_width), 0,
                  env_width - 1); // corresponding U,V coordinates
    int y = clamp(int((1 - v) * env_height), 0, env_height - 1);

    int index = (y * env_width + x) * env_channels; // index in env_data

    return Vec3(env_data[index], env_data[index + 1], env_data[index + 2]);
}

/******************************************************************
 * @brief Uniform gradient from sky blue to sky white
 * @par Direction of ray
 * @return environment light for a particular y-coordinate
 ******************************************************************/
Vec3 Renderer::env_light_gradient(const Vec3 &dir) {
    float t = 0.5f * (dir.y + 1.0f); // [-1, 1] → [0, 1]
    return mix(sky_bottom_color, sky_top_color, t);
}

/****************************************************************************************
 * @brief Takes a chunk of the image
 * @return Gives the pixel value at each point in that width of image.
 * @return If the point is outside the object, mixes
 * white and skyblue based on the height , but if HDR file is accessible then
 *maps to that
 *****************************************************************************************/
void Renderer::render_thread(Camera camera, const std::vector<obj_pointer> &shapes,
                   unsigned char *data, int w1, int w2, int out_width,
                   int out_height, int num_samples, int depth) {
    Random random_generator = Random(time(nullptr));
    float u, v;
    Vec3 sky_blue = Vec3(0.1f, 0.5f, 0.9f);
    Vec3 sky_white = Vec3(1, 1, 1);

    for (int i = w1; i < w2; i++) {
        counter_mutex.lock();
        if ((w2 - i) % (out_width / 100) == 0) {
            counter++;

            if (counter % 10 == 0) {
                std::cout << "==";
                std::flush(std::cout);
            }
        }
        counter_mutex.unlock();

        for (int j = 0; j < out_height; j++) {

            int pix = out_width * j + i;

            Vec3 color(0, 0, 0);

            for (int sample = 0; sample < num_samples; sample++) {

                v = 1 -
                    (float)(j + 2 * random_generator.GenerateUniformFloat() -
                            1) /
                        out_height;
                u = (float)(i + 2 * random_generator.GenerateUniformFloat() -
                            1) /
                    out_width;

                const Ray ray = camera.generate_ray(u, v, random_generator);
                auto hit = closestIntersect(shapes, ray);

                IntersectionOut &details = hit.second;

                if (details.hit == true) {
                    color =
                        color + Renderer::illuminance(details, depth, shapes,
                                                      random_generator);
                } else {
                    if (env_data) {
                        color = color + sample_env_map(ray.direction);
                    } else {
                        color =
                            color + Renderer::env_light_gradient(ray.direction);
                    }
                }
            }

            color = color / float(num_samples);

            color = clamp(color, Vec3(0, 0, 0), Vec3(1, 1, 1));

            // Converting normalized RGB to 8-bit RGB
            data[pix * 3 + 0] = (unsigned char)(255 * pow(color.x, 1 / 1.8));
            data[pix * 3 + 1] = (unsigned char)(255 * pow(color.y, 1 / 1.8));
            data[pix * 3 + 2] = (unsigned char)(255 * pow(color.z, 1 / 1.8));
        }
    }
}


/***************************************************
 * @brief Applies a simple 3x3 median filter to the image.
 * Useful for removing salt-and-pepper noise while preserving edges.
 *
 * @param data Pointer to RGB image buffer
 * @param width Image width
 * @param height Image height
 ***************************************************/
void median_filter(unsigned char* data, int width, int height) {
    unsigned char* temp = new unsigned char[width * height * 3];

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            unsigned char r_vals[9], g_vals[9], b_vals[9];
            int idx = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int ix = x + kx;
                    int iy = y + ky;
                    int i = (iy * width + ix) * 3;
                    r_vals[idx] = data[i + 0];
                    g_vals[idx] = data[i + 1];
                    b_vals[idx] = data[i + 2];
                    ++idx;
                }
            }

            std::sort(r_vals, r_vals + 9);
            std::sort(g_vals, g_vals + 9);
            std::sort(b_vals, b_vals + 9);

            int id = (y * width + x) * 3;
            temp[id + 0] = r_vals[4]; // median
            temp[id + 1] = g_vals[4];
            temp[id + 2] = b_vals[4];
        }
    }

    // Copy filtered data back
    for (int i = 0; i < width * height * 3; ++i)
        data[i] = temp[i];

    delete[] temp;
}


/***************************************************
 * @brief Applies a simple 3x3 Median Filter to the image.
 * Used for optional denoising of Monte Carlo noise.
 * Using Gaussian blur because noise is uniform, it smooths out the noise without much blurring of the edges
 *
 * @param data Pointer to RGB image buffer
 * @param width Image width
 * @param height Image height
 ***************************************************/
void gaussian_blur(unsigned char* data, int width, int height) {
    float kernel[3][3] = {
        {1/16.f, 2/16.f, 1/16.f},
        {2/16.f, 4/16.f, 2/16.f},
        {1/16.f, 2/16.f, 1/16.f}
    };

    unsigned char* temp = new unsigned char[width * height * 3];

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            float r = 0, g = 0, b = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int ix = x + kx;
                    int iy = y + ky;
                    int idx = (iy * width + ix) * 3;
                    float weight = kernel[ky + 1][kx + 1];
                    r += data[idx + 0] * weight;
                    g += data[idx + 1] * weight;
                    b += data[idx + 2] * weight;
                }
            }
            int id = (y * width + x) * 3;
            temp[id + 0] = static_cast<unsigned char>(r);
            temp[id + 1] = static_cast<unsigned char>(g);
            temp[id + 2] = static_cast<unsigned char>(b);
        }
    }

    // Copy blurred data back
    for (int i = 0; i < width * height * 3; ++i)
        data[i] = temp[i];

    delete[] temp;
}


/************************************************************************************
 * @brief Takes values of pixels from all the chunks (here,10)
 * @return Joins all of them to give the pixel values of all the points of the
 *image.
 ***********************************************************************************/
void Renderer::render(Camera camera, const std::vector<obj_pointer> &shapes,
                      const std::string &outfile, int out_width, int out_height, int num_samples,
                      bool env_light, bool denoise) {

    unsigned char *data = new unsigned char[out_width * out_height * 3];
    Random random_generator = Random(time(nullptr));

    // NDC coordinates
    float u, v;
    std::cout << "[Renderer] Starting render!\n";
    std::cout << "Thread status:\n";
    std::cout << " 0 1 2 3 4 5 6 7 8 9 \n[";

    // Create 10 threads to run concurrently
    std::vector<std::thread> threads;
    int N = 10;
    threads.reserve(N);
  
    int depth = 8;

    // Each thread renders 1/10th width of scene
    for (int i = 0; i < N; i++) {
        threads.emplace_back(
            std::thread(render_thread, camera, std::ref(shapes), data,
                        i * out_width / N, (i + 1) * out_width / N, out_width,
                        out_height, num_samples, depth));
    }
    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    std::cout << "]\n";

    if (denoise)
        median_filter(data, out_width, out_height);

    // Write data
    stbi_write_png(outfile.data(), out_width, out_height, 3, data, 0);
    delete[] data;
}

/**********************************************************************************
 * @brief Sets the sky color (if not using image based lighting)
 * @par Azimuth color
 * @par Horizon color
**********************************************************************************/
void Renderer::env_light(Vec3 sky_top_color, Vec3 sky_bottom_color) 
{
    Renderer::sky_top_color = sky_top_color;
    Renderer::sky_bottom_color = sky_bottom_color;
}

/**********************************************************************************
 * @brief Loads the HDR file and stores it in env_data as float* array
 * @par Environment file path
 * Also initiates the env_depth , env_height and env_channels( here 3 for RGB )
 **********************************************************************************/
void Renderer::env_map(const std::string &envmap_file_path) {
    stbi_set_flip_vertically_on_load(true);
    // std::cout << stbi_is_hdr(envmap_file_path.data()) << "\n";
    env_data = stbi_loadf(envmap_file_path.c_str(), &env_width, &env_height,
                          &env_channels, 0);

    if (env_data == nullptr) {
        std::cerr << "Failed to load HDR environment map\n";
        exit(1);
    }
}

/********************************************************************************
 * @return Gives Lr (additional light) by approximating over all the directions
 * @return Gives Le (light emitted by the object)
 * @return Adds Lr and Le to give all the light that reaches the eye
 ********************************************************************************/
Vec3 Renderer::illuminance(const IntersectionOut &surface, int max_depth,
                           const std::vector<obj_pointer> &shapes,
                           Random &random_generator) {
    Vec3 Le = surface.hit_mat->Le(surface.w0, surface.point);

    // If max_depth has been reached give material emission colour
    if (max_depth == 0)
        return Le;

    // Else pick random vector according to material
    // TODO: Implement BRDF
    Ray wi = surface.hit_mat->sample_wi(surface.w0, surface.point,
                                        surface.normal, random_generator);
    if (wi.direction == Vec3(0, 0, 0))
        return Le;

    auto hit = closestIntersect(shapes, wi);
    IntersectionOut &details = hit.second;

    Vec3 Li = Vec3(0, 0, 0);
    Vec3 Fr = surface.hit_mat->Fr(wi, surface.w0, surface.normal);

    // Russian Roulette threshold
    // TODO: Try using approximated variance to calculate
    //
    // Use larger number of samples to remove "sparkles"
    float p = clamp(std::max(Fr.x, std::max(Fr.y, Fr.z)), 0.01, 1);

    if (random_generator.GenerateUniformFloat() > p)
        return Vec3(0,0,0);

    // Calculate luminance of hit point else assume no light
    if (details.hit) {
        // Darker light -> More chance of skipping
        Li = illuminance(details, max_depth - 1, shapes, random_generator);
    } else {
        if (env_data) {
            Li = sample_env_map(wi.direction);
        } else {
            Li = env_light_gradient(wi.direction);
        }
    }

    Vec3 Lr = Fr * Li / p;

    // Return monte-carlo sample
    return Le + Lr;
}

/**************************************************
 * @brief Free up the space given to env_data file
 **************************************************/
void Renderer::cleanup() {
    if (env_data != nullptr) {
        stbi_image_free(env_data);
        env_data = nullptr;

        // Optional: Reset metadata
        env_width = 0;
        env_height = 0;
        env_channels = 0;

        std::cout << "[Renderer] Environment map data cleaned up.\n";
    }
}
