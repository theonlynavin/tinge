#include "renderer.h"
#include "util.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>

void Renderer::render(Camera camera, const std::vector<AbstractShape *> &shapes,
                      const std::string &outfile, int out_width, int out_height,
                      bool env_light) {

    unsigned char *data = new unsigned char[out_width * out_height * 3];

    Vec3 sky_blue = Vec3(0.1f, 0.5f, 0.9f);
    Vec3 sky_white = Vec3(1, 1, 1);

    if (env_light) {
        Renderer::env_light();
    } else {
        Renderer::env_map();
    }

    for (int i = 0; i < out_width; i++) {
        for (int j = 0; j < out_height; j++) {
            int pix = out_width * j + i;

            // NDC coordinates
            float u = (float)i / out_width;
            float v = 1 - (float)j / out_height;

            Ray ray = camera.generate_ray(u, v);
            auto hit = closestIntersect(shapes, ray);

            IntersectionOut details = hit.second;
            Vec3 color;

            if (details.hit == true) {
                color.x = abs(details.normal.x);
                color.y = abs(details.normal.y);
                color.z = abs(details.normal.z);
            } else {
                color = mix(sky_white, sky_blue, v);
            }
            // We want the sky to become whiter as we go down

            // Converting normalized RGB to 8-bit RGB
            data[pix * 3 + 0] = (unsigned char)(255 * color.x);
            data[pix * 3 + 1] = (unsigned char)(255 * color.y);
            data[pix * 3 + 2] = (unsigned char)(255 * color.z);
        }
    }

    stbi_write_png(outfile.data(), out_width, out_height, 3, data, 0);
    delete[] data;
}

void Renderer::env_light() {
    // TODO: Implement
}

void Renderer::env_map() {
    // TODO: Implement
}
