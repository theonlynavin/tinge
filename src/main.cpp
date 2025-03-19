#include "camera.h"
#include "objects.h"
#include "renderer.h"
#include "util.h"
#include <iostream>

#define WIDTH 1920
#define HEIGHT 1080

int main() {
    std::cout << "Hello there!" << std::endl;
    Camera camera = Camera(2.5, WIDTH, HEIGHT, 1);
    // Example vector code
    Sphere sphere2 = Sphere(Vec3(0, 0, -2), 1);
    sphere2.frame.scale.y = 2;
    sphere2.frame.lockFrame();

    MaterialDiffuse diffuse;
    sphere2.material = &diffuse;

    Sphere sphere1 = Sphere(Vec3(0, 2, -5), 1);
    sphere1.frame.scale.x = 2;
    sphere1.frame.origin.x = 1;
    sphere1.frame.rotation.y = M_PI_4;
    sphere1.frame.lockFrame();

    std::vector<AbstractShape *> shapes =
        std::vector<AbstractShape *>{&sphere1, &sphere2};

    Renderer::render(camera, shapes, "test.png", WIDTH, HEIGHT);

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
