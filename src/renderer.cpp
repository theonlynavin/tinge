#include "renderer.h"
#include "material.h"
#include "math.h"
#include "util.h"
#include <ctime>
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>

void Renderer::render(Camera camera, const std::vector<AbstractShape *> &shapes,
                      const std::string &outfile, int out_width, int out_height,
                      bool env_light) {

    unsigned char *data = new unsigned char[out_width * out_height * 3];
    Random random_generator = Random(time(nullptr));

    /*Vec3 sky_blue = Vec3(0.1f, 0.5f, 0.9f);*/
    /*Vec3 sky_white = Vec3(1, 1, 1);*/

    if (env_light) {
        Renderer::env_light();
    } else {
        Renderer::env_map();
    }

    // NDC coordinates
    float u, v;
    float last_print = 0;
    std::cout << " 0 1 2 3 4 5 6 7 8 9 \n[";
    for (int i = 0; i < out_width; i++) {
        u = (float)i / out_width;
        if (u * 100 - last_print > 10) {
            last_print = u * 100;
            std::cout << "==";
            std::flush(std::cout);
        }

        for (int j = 0; j < out_height; j++) {
            v = 1 - (float)j / out_height;
            int pix = out_width * j + i;

            Ray ray = camera.generate_ray(u, v);
            auto hit = closestIntersect(shapes, ray);

            IntersectionOut &details = hit.second;
            Vec3 color;

            if (details.hit == true) {
                color =
                    Renderer::illuminance(details, 5, shapes, random_generator);
            } else {
                /*color = mix(sky_white, sky_blue, v);*/
                color = Vec3(0, 0, 0);
            }
            // We want the sky to become whiter as we go down

            // Converting normalized RGB to 8-bit RGB
            data[pix * 3 + 0] = (unsigned char)(255 * color.x);
            data[pix * 3 + 1] = (unsigned char)(255 * color.y);
            data[pix * 3 + 2] = (unsigned char)(255 * color.z);
        }
    }
    std::cout << "==]\n";

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
                           const std::vector<AbstractShape *> &shapes,
                           Random &random_generator) {
    Vec3 Le = surface.hit_mat->Le(surface.w0, surface.point);
    Vec3 Li = Vec3(0, 0, 0);

    if (max_depth == 0)
        return Le;

    float V = 2 * M_PI;
    int n = 5;

    for (int i = 0; i < n; i++) {
        Vec3 dir = surface.hit_mat->sample_wi(surface.w0, surface.normal,
                                              random_generator);
        Ray wi = Ray(surface.point, dir);
        auto hit = closestIntersect(shapes, wi);
        IntersectionOut &details = hit.second;
        Vec3 Lr = Vec3(0, 0, 0);

        if (details.hit)
            Lr = illuminance(details, max_depth - 1, shapes, random_generator);
        Vec3 Fr = surface.hit_mat->Fr(wi, surface.w0, surface.normal);

        Li = Li + Vec3(Fr.x * Lr.x, Fr.y * Lr.y, Fr.z * Lr.z) *
                      dot(wi.direction, surface.normal);
    }
    Li = Li / n * V;

    return Le + Li;
}
