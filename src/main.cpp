#include "camera.h"
#include "objects.h"
#include "renderer.h"
#include "scene_generator.h"
#include <chrono>
#include <iostream>
#include <time.h>

#define WIDTH 192*2
#define HEIGHT 108*2

int main() {
    std::cout << "Hello there!" << std::endl;

    Camera camera = Camera(M_PI_2, WIDTH, HEIGHT, 10, 0.1);
    camera.look_at(Vec3(1, 4, 3), Vec3(0, 0, -4));

    std::vector<obj_pointer> shapes;
    // Populate scene
    generate_scene(shapes);

    Renderer::env_map("E:/HDRi/hansaplatz_4k.hdr");

    // Begin timer and start render
    auto start = std::chrono::high_resolution_clock::now();
    Renderer::render(camera, shapes, "test.png", WIDTH, HEIGHT, true);
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "\nRendered in: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stop -
                                                                       start)
                     .count()
              << "ms" << std::endl;

    Renderer::cleanup();
    return 0;
}
