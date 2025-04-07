#include "scene_generator.h"
#include "frame.h"
#include "material.h"
#include "math.h"
#include "obj_loader/OBJ_Loader.h"
#include "objects.h"
#include "util.h"
#include <iostream>
#include <memory>

void generate_scene(std::vector<obj_pointer> &shapes) {

    mat_pointer emmisive = std::make_shared<MaterialEmissive>(Vec3(1, 1, 1));
    obj_pointer back_wall_1 = std::make_shared<Triangle>(
        Vec3(-3.5, 2, 0), Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), emmisive);
    obj_pointer back_wall_2 = std::make_shared<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, -2, 0), Vec3(3.5, 2, 0), emmisive);
    back_wall_1->frame.origin.z = -7;
    back_wall_1->frame.lockFrame();
    back_wall_2->frame.origin.z = -7;
    back_wall_2->frame.lockFrame();
    shapes.push_back(back_wall_1);
    shapes.push_back(back_wall_2);

    mat_pointer right_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.9, .1, .1));
    obj_pointer right_wall_1 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 0, -7), right_wall_mat);
    obj_pointer right_wall_2 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, 0), Vec3(0, 4, -7), right_wall_mat);
    right_wall_1->frame.origin.x = 3.5;
    right_wall_1->frame.origin.y = -2;
    right_wall_1->frame.lockFrame();
    right_wall_2->frame.origin.x = 3.5;
    right_wall_2->frame.origin.y = -2;
    right_wall_2->frame.lockFrame();

    mat_pointer left_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .9, .1));
    obj_pointer left_wall_1 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, -7), Vec3(0, 4, -7), left_wall_mat);
    obj_pointer left_wall_2 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 4, 0), left_wall_mat);
    left_wall_1->frame.origin.x = -3.5;
    left_wall_1->frame.origin.y = -2;
    left_wall_1->frame.lockFrame();
    left_wall_2->frame.origin.x = -3.5;
    left_wall_2->frame.origin.y = -2;
    left_wall_2->frame.lockFrame();

    mat_pointer top_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(1, .7, .1));
    obj_pointer top_wall_1 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 0), Vec3(7, 0, 7), top_wall_mat);
    obj_pointer top_wall_2 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(0, 0, 7), top_wall_mat);
    top_wall_1->frame.origin.x = -3.5;
    top_wall_1->frame.origin.y = 2;
    top_wall_1->frame.origin.z = -7;
    top_wall_1->frame.lockFrame();
    top_wall_2->frame.origin.x = -3.5;
    top_wall_2->frame.origin.y = 2;
    top_wall_2->frame.origin.z = -7;
    top_wall_2->frame.lockFrame();

    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .1, .9));
    obj_pointer bottom_wall_1 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(7, 0, 0), bottom_wall_mat);
    obj_pointer bottom_wall_2 = std::make_shared<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, 7), Vec3(7, 0, 7), bottom_wall_mat);
    bottom_wall_1->frame.origin.x = -3.5;
    bottom_wall_1->frame.origin.y = -2;
    bottom_wall_1->frame.origin.z = -7;
    bottom_wall_1->frame.lockFrame();
    bottom_wall_2->frame.origin.x = -3.5;
    bottom_wall_2->frame.origin.y = -2;
    bottom_wall_2->frame.origin.z = -7;
    bottom_wall_2->frame.lockFrame();

    shapes.push_back(right_wall_1);
    shapes.push_back(right_wall_2);
    shapes.push_back(left_wall_1);
    shapes.push_back(left_wall_2);
    shapes.push_back(top_wall_1);
    shapes.push_back(top_wall_2);
    shapes.push_back(bottom_wall_1);
    shapes.push_back(bottom_wall_2);

    mat_pointer metal = std::make_shared<MaterialMetallic>(Vec3(1, 1, 1), .1);

    // Initialize Loader
    objl::Loader Loader;
    bool loadout = Loader.LoadFile("box.obj");
    objl::Mesh mesh = Loader.LoadedMeshes[0];

    auto common_mesh_transform = [](Frame &obj_frame) {
        obj_frame.origin.y = -20;
        obj_frame.origin.z = -5;
        /*obj_frame.rotation.y = 0.73;*/
        obj_frame.scale.x = 8;
        obj_frame.scale.y = 8;
        obj_frame.scale.z = 8;
        obj_frame.lockFrame();
    };

    for (int i = 0; i < mesh.Indices.size(); i += 3) {
        auto &v1 = mesh.Vertices[mesh.Indices[i]].Position;
        auto &v2 = mesh.Vertices[mesh.Indices[i + 1]].Position;
        auto &v3 = mesh.Vertices[mesh.Indices[i + 2]].Position;
        obj_pointer triangle = std::make_shared<Triangle>(
            Vec3(v1.X, v1.Y, v1.Z), Vec3(v2.X, v2.Y, v2.Z),
            Vec3(v3.X, v3.Y, v3.Z), metal);
        common_mesh_transform(triangle->frame);
        shapes.push_back(triangle);
    }
}
