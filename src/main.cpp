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
    Camera camera = Camera(2.5, WIDTH, HEIGHT, 2, 0.02);
    std::vector<obj_pointer> shapes;
    // Populate scene
    generate_scene(shapes);

    // Begin timer and start render
    auto start = std::chrono::high_resolution_clock::now();
    Renderer::render(camera, shapes, "test.png", WIDTH, HEIGHT, true);
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "\nRendered in: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stop -
                                                                       start)
                     .count()
              << "ms" << std::endl;

    return 0;
}
