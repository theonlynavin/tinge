#include "camera.h"
#include "material.h"
#include "objects.h"
#include "renderer.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080

int main() {
    std::cout << "Hello there!" << std::endl;
    Camera camera = Camera(2.5, WIDTH, HEIGHT, 1);
    std::shared_ptr<AbstractMaterial> light_emmissive =
        std::make_shared<MaterialEmissive>(Vec3(1, 1, 1));
    std::shared_ptr<AbstractMaterial> diffuse =
        std::make_shared<MaterialDiffuse>(Vec3(.2, .3, .8));
    std::shared_ptr<AbstractMaterial> ground_diff =
        std::make_shared<MaterialDiffuse>(Vec3(.8, .1, .8));
    std::shared_ptr<AbstractMaterial> ground_met =
        std::make_shared<MaterialMetallic>(Vec3(.2, .3, .8), .2);

    Sphere sphere2 = Sphere(Vec3(0, 0, 0), 1, light_emmissive);
    sphere2.frame.origin.z = -2;
    sphere2.frame.lockFrame();

    Sphere sphere1 = Sphere(Vec3(0, 0, 0), 1, ground_met);
    sphere1.frame.origin.x = 3;
    sphere1.frame.origin.y = -1;
    sphere1.frame.origin.z = -4;
    sphere1.frame.lockFrame();

    Sphere sphere3 = Sphere(Vec3(0, 0, 0), 1, diffuse);
    sphere3.frame.origin.x = -3;
    sphere3.frame.origin.y = -1;
    sphere3.frame.origin.z = -4;
    sphere3.frame.lockFrame();
    Triangle light = Triangle(Vec3(-10, 5, -4), Vec3(10, 5, -4),
                              Vec3(0, -10, -4), ground_diff);
    /*Plane light = Plane(Vec3(0, 0, 1), Vec3(0, 0, -3), ground_met);*/
    /*light.frame.rotation.y = M_PI_2;*/
    light.frame.lockFrame();

    /*light.frame.lockFrame();*/

    std::vector<AbstractShape *> shapes = std::vector<AbstractShape *>{
        &sphere1, &sphere2, &sphere3, &light,
        /*&light*/
    };

    auto start = std::chrono::high_resolution_clock::now();
    Renderer::render(camera, shapes, "test.png", WIDTH, HEIGHT, true);
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "\nRendered in: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stop -
                                                                       start)
                     .count()
              << "ms" << std::endl;

    // Example matrix code

    /*Mat4 m;*/
    /*m = Transform::rotate(M_PI_4, M_PI_2, M_PI_2);*/
    /*m = Transform::translate(2, 3, -1) * m;*/
    /**/
    /*// Let's see what m is*/
    /*std::cout << m << std::endl;*/
    /**/
    /*// This should remove the translation component from m*/
    /*std::cout << Transform::translate(-2, -3, 1) * m << std::endl;*/
    /**/
    /*// Lets verify if they are indeed equal*/
    /*std::cout << Transform::rotate(M_PI_4, M_PI_2, M_PI_2) << std::endl;*/
    /**/
    /*// This should be the identity matrix*/
    /*std::cout << m * m.inverse() << std::endl;*/
    /**/
    /*// This is the element in the 3nd row, 4th column of the inverse*/
    /*std::cout << (m * m.inverse())[2][3] << std::endl;*/
    /**/
    /*std::cout << "Bye bye!" << std::endl;*/

    return 0;
}
