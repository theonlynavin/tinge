#include "camera.h"
#include "objects.h"
#include "renderer.h"
#include "scene_generator.h"
#include <chrono>
#include <iostream>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080

int main() {
    std::cout << "Hello there!" << std::endl;

    // Set up the camera
    Camera camera = Camera(M_PI_2, WIDTH, HEIGHT, 10, 0);
    camera.look_at(Vec3(4, 3, 4)/2, Vec3(0, 0, -3));
    
    // Populate scene
    std::vector<obj_pointer> shapes;
    generate_scene(shapes, CORNELL);

    // Load the environment map
    Renderer::env_map("assets/paul_lobe_haus_8k.hdr");

    // Begin timer and start render
    auto start = std::chrono::high_resolution_clock::now();
    Renderer::render(camera, shapes, "test.png", WIDTH, HEIGHT, 200, true, false);
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "\nRendered in: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stop -
                                                                       start)
                     .count()
              << "ms" << std::endl;

    Renderer::cleanup();
    return 0;
}
