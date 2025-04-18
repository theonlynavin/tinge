#include "renderer.h"
#include "camera.h"
#include "material.h"
#include "math.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <thread>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define SCENE_VIEW 0
#include <stb_image/stb_image_write.h>

std::mutex counter_mutex;
int counter = 0;

void render_thread(Camera camera, const std::vector<obj_pointer> &shapes,
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
                    color = color + mix(sky_white, sky_blue, v);
                    // color = color + Vec3(0, 0, 0);
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

void Renderer::render(Camera camera, const std::vector<obj_pointer> &shapes,
                      const std::string &outfile, int out_width, int out_height,
                      bool env_light) {

    unsigned char *data = new unsigned char[out_width * out_height * 3];
    Random random_generator = Random(time(nullptr));

    if (env_light) {
        Renderer::env_light();
    } else {
        Renderer::env_map();
    }

    // NDC coordinates
    float u, v;
    std::cout << " 0 1 2 3 4 5 6 7 8 9 \n[";

    // Create 10 threads to run concurrently
    std::vector<std::thread> threads;
    int N = 10;
    threads.reserve(N);
    int num_samples = 5, depth = 4;

    // Each thread renders 1/10th width of scene
    for (int i = 0; i < N; i++) {
        threads.emplace_back(
            std::thread(render_thread, camera, std::ref(shapes), data,
                        i * out_width / N, (i + 1) * out_width / N, out_width,
                        out_height, num_samples, depth));
    }
    for (int i = 0; i < N; i++) {
        threads[i].join();
    }

    std::cout << "]\n";

    // Write data
    stbi_write_png(outfile.data(), out_width, out_height, 3, data, 0);
    delete[] data;
}

void Renderer::env_light() {
    // TODO: Implement
}

void Renderer::env_map() {
    // TODO: Implement
}

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

    // Calculate luminance of hit point else assume no light
    if (details.hit) {
        Li = illuminance(details, max_depth - 1, shapes, random_generator);
    } else {
        Li = Vec3(0.1f, 0.5f, 0.9f);
    }

    Vec3 Lr = Fr * Li;

    // Return monte-carlo sample
    return Le + Lr;
}
