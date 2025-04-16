#include "scene_generator.h"
#include "bvh.h"
#include "material.h"
#include "math.h"
#include "objects.h"
#include <memory>

void generate_scene(std::vector<obj_pointer> &shapes) {

    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialMetallic>(Vec3(.8, .8, .8), .6);
    obj_pointer bbox = std::make_shared<BVH_Box>(
        "teapot.obj", bottom_wall_mat, Vec3(0, -2, -5), Vec3(0.02, 0.02, 0.02),
        Vec3());
    shapes.push_back(bbox);
}
