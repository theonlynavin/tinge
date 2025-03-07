#include "objects.h"
#include "util.h"
#include <iostream>
#include"camera.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>

#define WIDTH 1920
#define HEIGHT 1080

int main() {
    std::cout << "Hello there!" << std::endl;
    Camera camera = Camera(2.5, WIDTH, HEIGHT, 1);
    // Example vector code
    Sphere sphere2 = Sphere(Vec3(0, 0, -2), 1);
    sphere2.frame.scale.y = 2;
    sphere2.frame.lockFrame();
    
    Sphere sphere1 = Sphere(Vec3(0, 2, -5), 1);
    sphere1.frame.scale.x = 2;
    sphere1.frame.origin.x = 1;
    sphere1.frame.rotation.y = M_PI_4;
    sphere1.frame.lockFrame();

    Vec3 sky_blue = Vec3(0.1f, 0.5f, 0.9f);
    Vec3 sky_white = Vec3(1, 1, 1);

    std::vector<AbstractShape *> shapes =  std::vector<AbstractShape *>{ &sphere1, &sphere2 };

    unsigned char *data = new unsigned char[WIDTH * HEIGHT * 3];

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            int pix = WIDTH * j + i;

            // NDC coordinates
            float u = (float)i / WIDTH;
            float v = 1 - (float)j / HEIGHT;

            Ray ray = camera.generate_ray(u, v);
            auto hit = closestIntersect(shapes, ray);

            IntersectionOut details = hit.second;
            Vec3 color;

            if (details.hit == true)
            {
                color.x = abs(details.normal.x);
                color.y = abs(details.normal.y);
                color.z = abs(details.normal.z);
            }
            else
            { 
                color = mix(sky_white, sky_blue, v);
            }
            // We want the sky to become whiter as we go down

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
