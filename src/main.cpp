#include "objects.h"
#include "util.h"
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>

#define WIDTH 1920
#define HEIGHT 1080

int main() {
    std::cout << "Hello there!" << std::endl;

    // Example vector code

    Vec3 sky_blue = Vec3(0.1f, 0.5f, 0.9f);
    Vec3 sky_white = Vec3(1, 1, 1);

    unsigned char *data = new unsigned char[WIDTH * HEIGHT * 3];

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            int pix = WIDTH * j + i;

            // NDC coordinates
            float u = (float)i / WIDTH;
            float v = 1 - (float)j / HEIGHT;

            // We want the sky to become whiter as we go down
            Vec3 color = mix(sky_white, sky_blue, v);

            // Converting normalized RGB to 8-bit RGB
            data[pix * 3 + 0] = (unsigned char)(255 * color.x);
            data[pix * 3 + 1] = (unsigned char)(255 * color.y);
            data[pix * 3 + 2] = (unsigned char)(255 * color.z);
        }
    }

    stbi_write_png(".//test.png", 1920, 1080, 3, data, 0);
    delete[] data;

    // Example matrix code

    Mat4 m;
    m = Transform::rotate(M_PI_4, M_PI_2, M_PI_2);
    m = Transform::translate(2, 3, -1) * m;

    // Let's see what m is
    std::cout << m << std::endl;

    // This should remove the translation component from m
    std::cout << Transform::translate(-2, -3, 1) * m << std::endl;

    // Lets verify if they are indeed equal
    std::cout << Transform::rotate(M_PI_4, M_PI_2, M_PI_2) << std::endl;

    // This should be the identity matrix
    std::cout << m * m.inverse() << std::endl;

    // This is the element in the 3nd row, 4th column of the inverse
    std::cout << (m * m.inverse())[2][3] << std::endl;

    std::cout << "Bye bye!" << std::endl;

    return 0;
}
