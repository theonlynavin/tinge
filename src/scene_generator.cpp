#include "scene_generator.h"
#include "material.h"
#include "math.h"
#include "mesh.h"
#include "objects.h"
#include <iostream>
#include <memory>

void generate_scene(std::vector<obj_pointer> &shapes) {

    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialMetallic>(Vec3(.8, .8, .8), .6);
    obj_pointer bbox =
        std::make_unique<Mesh>("teapot.obj", bottom_wall_mat, Vec3(0, -2, -5),
                               Vec3(0.01, 0.01, 0.01), Vec3());
    shapes.push_back(std::move(bbox));

    obj_pointer tri = std::make_unique<Triangle>(
        Vec3(-0.717622, -1.99976, -5.47744), Vec3(0.821608, -1.99976, -5.47744),
        Vec3(0.821608, 0, -5.47744), bottom_wall_mat);
    /*shapes.push_back(std::move(tri));*/

    std::cout << "Scene Generation complete" << std::endl;
}
