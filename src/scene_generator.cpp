#include "scene_generator.h"
#include "material.h"
#include "math.h"
#include "mesh.h"
#include "objects.h"
#include <iostream>
#include <memory>

// A cornell box like scene with a glassy ball
void generate_scene1(std::vector<obj_pointer> &shapes)
{
    // sets up the backwall which is a diffuse white rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer back_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(0.9, 0.9, 0.9));
    obj_pointer back_wall_1 = std::make_unique<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), Vec3(-3.5, 2, 0), back_wall_mat);
    obj_pointer back_wall_2 = std::make_unique<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, -2, 0), Vec3(3.5, 2, 0), back_wall_mat);
    back_wall_1->frame.origin.z = -7;
    back_wall_1->frame.lockFrame();
    back_wall_2->frame.origin.z = -7;
    back_wall_2->frame.lockFrame();
    shapes.push_back(std::move(back_wall_1));
    shapes.push_back(std::move(back_wall_2));

    // sets up the frontwall which is a fully black rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer emmisive_ =
        std::make_shared<MaterialEmissive>(Vec3(0, 0, 0), 1);
    obj_pointer front_wall_1 = std::make_unique<Triangle>(
        Vec3(3.5, 2, 0), Vec3(-3.5, -2, 0), Vec3(-3.5, 2, 0), emmisive_);
    obj_pointer front_wall_2 = std::make_unique<Triangle>(
        Vec3(3.5, -2, 0), Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), emmisive_);
    front_wall_1->frame.origin.z = 0;
    front_wall_1->frame.lockFrame();
    front_wall_2->frame.origin.z = 0;
    front_wall_2->frame.lockFrame();
    shapes.push_back(std::move(front_wall_1));
    shapes.push_back(std::move(front_wall_2));

    // setups the right side wall which a diffuse material rectangle consisting
    // of two triangle shapes having a common side
    mat_pointer right_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.9, .1, .1));
    obj_pointer right_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 0, -7), right_wall_mat);
    obj_pointer right_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, 0), Vec3(0, 4, -7), right_wall_mat);
    right_wall_1->frame.origin.x = 3.5;
    right_wall_1->frame.origin.y = -2;
    right_wall_1->frame.lockFrame();
    right_wall_2->frame.origin.x = 3.5;
    right_wall_2->frame.origin.y = -2;
    right_wall_2->frame.lockFrame();
    shapes.push_back(std::move(right_wall_1));
    shapes.push_back(std::move(right_wall_2));

    // setups the left side wall which a diffuse material rectangle consisting
    // of two triangle shapes having a common side
    mat_pointer left_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .9, .1));
    obj_pointer left_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, -7), Vec3(0, 4, -7), left_wall_mat);
    obj_pointer left_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 4, 0), left_wall_mat);
    left_wall_1->frame.origin.x = -3.5;
    left_wall_1->frame.origin.y = -2;
    left_wall_1->frame.lockFrame();
    left_wall_2->frame.origin.x = -3.5;
    left_wall_2->frame.origin.y = -2;
    left_wall_2->frame.lockFrame();
    shapes.push_back(std::move(left_wall_1));
    shapes.push_back(std::move(left_wall_2));

    // setups the top wall which a diffuse material rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer top_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(0.7, 0.7, 0.1));
    obj_pointer top_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 0), Vec3(7, 0, 7), top_wall_mat);
    obj_pointer top_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(0, 0, 7), top_wall_mat);
    top_wall_1->frame.origin.x = -3.5;
    top_wall_1->frame.origin.y = 2;
    top_wall_1->frame.origin.z = -7;
    top_wall_1->frame.lockFrame();
    top_wall_2->frame.origin.x = -3.5;
    top_wall_2->frame.origin.y = 2;
    top_wall_2->frame.origin.z = -7;
    top_wall_2->frame.lockFrame();
    shapes.push_back(std::move(top_wall_1));
    shapes.push_back(std::move(top_wall_2));
    
    // setups the top area light which a emissive rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer top_light_mat =
        std::make_shared<MaterialEmissive>(Vec3(1, 1, 1), 1.4);
    obj_pointer top_light_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(3.5, 0, 0), Vec3(3.5, 0, 3.5), top_light_mat);
    obj_pointer top_light_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(3.5, 0, 3.5), Vec3(0, 0, 3.5), top_light_mat);
    top_light_1->frame.origin.x = -3.5;
    top_light_1->frame.origin.y = 1.9;
    top_light_1->frame.origin.z = -7;
    top_light_1->frame.lockFrame();
    top_light_2->frame.origin.x = -3.5;
    top_light_2->frame.origin.y = 1.9;
    top_light_2->frame.origin.z = -7;
    top_light_2->frame.lockFrame();
    shapes.push_back(std::move(top_light_1));
    shapes.push_back(std::move(top_light_2));

    // setups the bottom wall which a diffuse material rectangle consisting of
    // two triangle shapes having a common side
    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .1, .9));
    obj_pointer bottom_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(7, 0, 0), bottom_wall_mat);
    obj_pointer bottom_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, 7), Vec3(7, 0, 7), bottom_wall_mat);
    bottom_wall_1->frame.origin.x = -3.5;
    bottom_wall_1->frame.origin.y = -2;
    bottom_wall_1->frame.origin.z = -7;
    bottom_wall_1->frame.lockFrame();
    bottom_wall_2->frame.origin.x = -3.5;
    bottom_wall_2->frame.origin.y = -2;
    bottom_wall_2->frame.origin.z = -7;
    bottom_wall_2->frame.lockFrame();
    shapes.push_back(std::move(bottom_wall_1));
    shapes.push_back(std::move(bottom_wall_2));

    mat_pointer glass = std::make_shared<MaterialTransmission>(Vec3(1, 1, 1), 1.5);

    mat_pointer metal = std::make_shared<MaterialMetallic>(Vec3(.8, .8, .9), .7);

    obj_pointer ball =
        std::make_unique<Sphere>(Vec3(0, 0, 0), 2, glass);
    ball->frame.origin.z = -5;
    ball->frame.origin.y = -2;
    ball->frame.lockFrame();
    shapes.push_back(std::move(ball));
    
    obj_pointer ball2 =
        std::make_unique<Sphere>(Vec3(0, 1.2, 0), 0.6, metal);
    ball2->frame.origin.z = -3;
    ball2->frame.origin.x = -2;
    ball2->frame.origin.y = -2;
    ball2->frame.lockFrame();
    shapes.push_back(std::move(ball2));
}

// A cornell box like scene with a glassy ball
void generate_scene_old(std::vector<obj_pointer> &shapes)
{
    // sets up the backwall which is an emissive rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer emmisive =
        std::make_shared<MaterialEmissive>(Vec3(1, 1, 1), 1.5);
    obj_pointer back_wall_1 = std::make_unique<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), Vec3(-3.5, 2, 0), emmisive);
    obj_pointer back_wall_2 = std::make_unique<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, -2, 0), Vec3(3.5, 2, 0), emmisive);
    back_wall_1->frame.origin.z = -7;
    back_wall_1->frame.lockFrame();
    back_wall_2->frame.origin.z = -7;
    back_wall_2->frame.lockFrame();
    shapes.push_back(std::move(back_wall_1));
    shapes.push_back(std::move(back_wall_2));

    // sets up the frontwall which is a fully black rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer emmisive_ =
        std::make_shared<MaterialEmissive>(Vec3(0, 0, 0), 1);
    obj_pointer front_wall_1 = std::make_unique<Triangle>(
        Vec3(3.5, 2, 0), Vec3(-3.5, -2, 0), Vec3(-3.5, 2, 0), emmisive_);
    obj_pointer front_wall_2 = std::make_unique<Triangle>(
        Vec3(3.5, -2, 0), Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), emmisive_);
    front_wall_1->frame.origin.z = 0;
    front_wall_1->frame.lockFrame();
    front_wall_2->frame.origin.z = 0;
    front_wall_2->frame.lockFrame();
    shapes.push_back(std::move(front_wall_1));
    shapes.push_back(std::move(front_wall_2));

    // setups the right side wall which a diffuse material rectangle consisting
    // of two triangle shapes having a common side
    mat_pointer right_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.9, .1, .1));
    obj_pointer right_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 0, -7), right_wall_mat);
    obj_pointer right_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, 0), Vec3(0, 4, -7), right_wall_mat);
    right_wall_1->frame.origin.x = 3.5;
    right_wall_1->frame.origin.y = -2;
    right_wall_1->frame.lockFrame();
    right_wall_2->frame.origin.x = 3.5;
    right_wall_2->frame.origin.y = -2;
    right_wall_2->frame.lockFrame();
    shapes.push_back(std::move(right_wall_1));
    shapes.push_back(std::move(right_wall_2));

    // setups the left side wall which a diffuse material rectangle consisting
    // of two triangle shapes having a common side
    mat_pointer left_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .9, .1));
    obj_pointer left_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, -7), Vec3(0, 4, -7), left_wall_mat);
    obj_pointer left_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 4, 0), left_wall_mat);
    left_wall_1->frame.origin.x = -3.5;
    left_wall_1->frame.origin.y = -2;
    left_wall_1->frame.lockFrame();
    left_wall_2->frame.origin.x = -3.5;
    left_wall_2->frame.origin.y = -2;
    left_wall_2->frame.lockFrame();
    shapes.push_back(std::move(left_wall_1));
    shapes.push_back(std::move(left_wall_2));

    // setups the top wall which a diffuse material rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer top_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(1, .7, .1));
    obj_pointer top_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 0), Vec3(7, 0, 7), top_wall_mat);
    obj_pointer top_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(0, 0, 7), top_wall_mat);
    top_wall_1->frame.origin.x = -3.5;
    top_wall_1->frame.origin.y = 2;
    top_wall_1->frame.origin.z = -7;
    top_wall_1->frame.lockFrame();
    top_wall_2->frame.origin.x = -3.5;
    top_wall_2->frame.origin.y = 2;
    top_wall_2->frame.origin.z = -7;
    top_wall_2->frame.lockFrame();
    shapes.push_back(std::move(top_wall_1));
    shapes.push_back(std::move(top_wall_2));

    // setups the bottom wall which a diffuse material rectangle consisting of
    // two triangle shapes having a common side
    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .1, .9));
    obj_pointer bottom_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(7, 0, 0), bottom_wall_mat);
    obj_pointer bottom_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, 7), Vec3(7, 0, 7), bottom_wall_mat);
    bottom_wall_1->frame.origin.x = -3.5;
    bottom_wall_1->frame.origin.y = -2;
    bottom_wall_1->frame.origin.z = -7;
    bottom_wall_1->frame.lockFrame();
    bottom_wall_2->frame.origin.x = -3.5;
    bottom_wall_2->frame.origin.y = -2;
    bottom_wall_2->frame.origin.z = -7;
    bottom_wall_2->frame.lockFrame();
    shapes.push_back(std::move(bottom_wall_1));
    shapes.push_back(std::move(bottom_wall_2));

    mat_pointer glass = std::make_shared<MaterialTransmission>(Vec3(1, 1, 1), 1.5);

    mat_pointer metal = std::make_shared<MaterialMetallic>(Vec3(.8, .8, .9), .7);

    obj_pointer ball =
        std::make_unique<Sphere>(Vec3(0, 1.2, 0), 1.2, glass);
    ball->frame.origin.z = -5;
    ball->frame.origin.y = -2;
    ball->frame.lockFrame();
    shapes.push_back(std::move(ball));
    
    obj_pointer ball2 =
        std::make_unique<Sphere>(Vec3(0, 1.2, 0), 0.6, metal);
    ball2->frame.origin.z = -3;
    ball2->frame.origin.x = -2;
    ball2->frame.origin.y = -2;
    ball2->frame.lockFrame();
    shapes.push_back(std::move(ball2));
}

// A open scene with a teapot and a glassy box
void generate_scene2(std::vector<obj_pointer> &shapes)
{
    // sets up a metallic teapot
    mat_pointer mesh_mat =
        std::make_shared<MaterialMetallic>(Vec3(.8, .8, .9), .7);
    obj_pointer bbox =
        std::make_unique<Mesh>("assets/teapot.obj", mesh_mat, Vec3(0, -1.7, -2),
                               2 * Vec3(0.01, 0.01, 0.01), Vec3(), 10);
    shapes.push_back(std::move(bbox));

    // setups the bottom wall which a diffuse material rectangle consisting of
    // two triangle shapes having a common side
    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .1, .9));
    obj_pointer bottom_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(7, 0, 0), bottom_wall_mat);
    obj_pointer bottom_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, 7), Vec3(7, 0, 7), bottom_wall_mat);
    bottom_wall_1->frame.origin.x = -3.5;
    bottom_wall_1->frame.origin.y = -2;
    bottom_wall_1->frame.origin.z = -7;
    bottom_wall_1->frame.lockFrame();
    bottom_wall_2->frame.origin.x = -3.5;
    bottom_wall_2->frame.origin.y = -2;
    bottom_wall_2->frame.origin.z = -7;
    bottom_wall_2->frame.lockFrame();
    shapes.push_back(std::move(bottom_wall_1));
    shapes.push_back(std::move(bottom_wall_2));

    mat_pointer glass = std::make_shared<MaterialTransmission>(Vec3(1, 1, 1), 1.5);
    mat_pointer metal_ball =
        std::make_shared<MaterialMetallic>(Vec3(.6, .6, .6), 0);
    obj_pointer ball =
        std::make_unique<Sphere>(Vec3(0, 1.2, 0), 1.2, glass);
    ball->frame.origin.z = -5;
    ball->frame.origin.y = -2;
    ball->frame.lockFrame();
    shapes.push_back(std::move(ball));

    mat_pointer light_ball =
        std::make_shared<MaterialEmissive>(Vec3(.9, .9, .1), 4);
    obj_pointer lball1 =
        std::make_unique<Sphere>(Vec3(0, 0, 0), 0.6, light_ball);
    lball1->frame.origin.z = -5;
    lball1->frame.origin.y = 1.5;
    lball1->frame.origin.x = 1;
    lball1->frame.lockFrame();
    shapes.push_back(std::move(lball1));

    obj_pointer lball2 =
        std::make_unique<Sphere>(Vec3(0, 0, 0), 0.6, light_ball);
    lball2->frame.origin.z = -5;
    lball2->frame.origin.y = -0.3;
    lball2->frame.origin.x = -3;
    lball2->frame.lockFrame();
    shapes.push_back(std::move(lball2));

    obj_pointer lball3 =
        std::make_unique<Sphere>(Vec3(0, 0, 0), 0.3, light_ball);
    lball3->frame.origin.z = -4;
    lball3->frame.origin.y = -1.6;
    lball3->frame.origin.x = 2.3;
    lball3->frame.lockFrame();
    shapes.push_back(std::move(lball3));
}

// A open scene with a teapot and a glassy box
void generate_scene3(std::vector<obj_pointer> &shapes)
{
    // sets up a metallic teapot
    mat_pointer mesh_mat =
        std::make_shared<MaterialTransmission>(Vec3(.8, .7, .9), 1.4);
    obj_pointer bbox =
        std::make_unique<Mesh>("assets/monkey.obj", mesh_mat, Vec3(0, 0, 0),
                               Vec3(0.6, 0.6, 0.6), Vec3(-M_PI_4, M_PI_4, 0), 10);
    shapes.push_back(std::move(bbox));

    // setups the bottom wall which a diffuse material rectangle consisting of
    // two triangle shapes having a common side
    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.7, .7, .7));
    obj_pointer bottom_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(7, 0, 0), bottom_wall_mat);
    obj_pointer bottom_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, 7), Vec3(7, 0, 7), bottom_wall_mat);
    bottom_wall_1->frame.origin.x = -3.5;
    bottom_wall_1->frame.origin.y = -2;
    bottom_wall_1->frame.origin.z = -7;
    bottom_wall_1->frame.lockFrame();
    bottom_wall_2->frame.origin.x = -3.5;
    bottom_wall_2->frame.origin.y = -2;
    bottom_wall_2->frame.origin.z = -7;
    bottom_wall_2->frame.lockFrame();
    shapes.push_back(std::move(bottom_wall_1));
    shapes.push_back(std::move(bottom_wall_2));

    mat_pointer glass = std::make_shared<MaterialMetallic>(Vec3(1, 1, 1), 0.1);
    mat_pointer metal_ball =
        std::make_shared<MaterialMetallic>(Vec3(.6, .6, .6), 0);
    obj_pointer ball =
        std::make_unique<Sphere>(Vec3(0, 1.2, 0), 1.2, glass);
    ball->frame.scale.x = 2;
    ball->frame.origin.z = -5;
    ball->frame.origin.y = -2;
    ball->frame.lockFrame();
    shapes.push_back(std::move(ball));

    mat_pointer light_ball =
        std::make_shared<MaterialEmissive>(Vec3(.9, .9, .1), 4);
    obj_pointer lball1 =
        std::make_unique<Sphere>(Vec3(0, 0, 0), 0.6, light_ball);
    lball1->frame.origin.z = -5;
    lball1->frame.origin.y = 1.5;
    lball1->frame.origin.x = 1;
    lball1->frame.lockFrame();
    shapes.push_back(std::move(lball1));

    obj_pointer lball2 =
        std::make_unique<Sphere>(Vec3(0, 0, 0), 0.6, light_ball);
    lball2->frame.origin.z = -5;
    lball2->frame.origin.y = -0.3;
    lball2->frame.origin.x = -3;
    lball2->frame.lockFrame();
    shapes.push_back(std::move(lball2));

    obj_pointer lball3 =
        std::make_unique<Sphere>(Vec3(0, 0, 0), 0.3, light_ball);
    lball3->frame.origin.z = -4;
    lball3->frame.origin.y = -1.6;
    lball3->frame.origin.x = 2.3;
    lball3->frame.lockFrame();
    shapes.push_back(std::move(lball3));
}

// The old color box scene
void generate_scene4(std::vector<obj_pointer> &shapes)
{
    // sets up the backwall which is an emissive rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer emmisive =
        std::make_shared<MaterialEmissive>(Vec3(1, 1, 1), 1.5);
    obj_pointer back_wall_1 = std::make_unique<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), Vec3(-3.5, 2, 0), emmisive);
    obj_pointer back_wall_2 = std::make_unique<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, -2, 0), Vec3(3.5, 2, 0), emmisive);
    back_wall_1->frame.origin.z = -7;
    back_wall_1->frame.lockFrame();
    back_wall_2->frame.origin.z = -7;
    back_wall_2->frame.lockFrame();
    shapes.push_back(std::move(back_wall_1));
    shapes.push_back(std::move(back_wall_2));

    // sets up the frontwall which is a fully black rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer emmisive_ =
        std::make_shared<MaterialEmissive>(Vec3(0, 0, 0), 1);
    obj_pointer front_wall_1 = std::make_unique<Triangle>(
        Vec3(3.5, 2, 0), Vec3(-3.5, -2, 0), Vec3(-3.5, 2, 0), emmisive_);
    obj_pointer front_wall_2 = std::make_unique<Triangle>(
        Vec3(3.5, -2, 0), Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), emmisive_);
    front_wall_1->frame.origin.z = 0;
    front_wall_1->frame.lockFrame();
    front_wall_2->frame.origin.z = 0;
    front_wall_2->frame.lockFrame();
    shapes.push_back(std::move(front_wall_1));
    shapes.push_back(std::move(front_wall_2));

    // setups the right side wall which a diffuse material rectangle consisting
    // of two triangle shapes having a common side
    mat_pointer right_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.9, .1, .1));
    obj_pointer right_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 0, -7), right_wall_mat);
    obj_pointer right_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, 0), Vec3(0, 4, -7), right_wall_mat);
    right_wall_1->frame.origin.x = 3.5;
    right_wall_1->frame.origin.y = -2;
    right_wall_1->frame.lockFrame();
    right_wall_2->frame.origin.x = 3.5;
    right_wall_2->frame.origin.y = -2;
    right_wall_2->frame.lockFrame();
    shapes.push_back(std::move(right_wall_1));
    shapes.push_back(std::move(right_wall_2));

    // setups the left side wall which a diffuse material rectangle consisting
    // of two triangle shapes having a common side
    mat_pointer left_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .9, .1));
    obj_pointer left_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, -7), Vec3(0, 4, -7), left_wall_mat);
    obj_pointer left_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 4, -7), Vec3(0, 4, 0), left_wall_mat);
    left_wall_1->frame.origin.x = -3.5;
    left_wall_1->frame.origin.y = -2;
    left_wall_1->frame.lockFrame();
    left_wall_2->frame.origin.x = -3.5;
    left_wall_2->frame.origin.y = -2;
    left_wall_2->frame.lockFrame();
    shapes.push_back(std::move(left_wall_1));
    shapes.push_back(std::move(left_wall_2));

    // setups the top wall which a diffuse material rectangle consisting of two
    // triangle shapes having a common side
    mat_pointer top_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(1, .7, .1));
    obj_pointer top_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 0), Vec3(7, 0, 7), top_wall_mat);
    obj_pointer top_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(0, 0, 7), top_wall_mat);
    top_wall_1->frame.origin.x = -3.5;
    top_wall_1->frame.origin.y = 2;
    top_wall_1->frame.origin.z = -7;
    top_wall_1->frame.lockFrame();
    top_wall_2->frame.origin.x = -3.5;
    top_wall_2->frame.origin.y = 2;
    top_wall_2->frame.origin.z = -7;
    top_wall_2->frame.lockFrame();
    shapes.push_back(std::move(top_wall_1));
    shapes.push_back(std::move(top_wall_2));

    // setups the bottom wall which a diffuse material rectangle consisting of
    // two triangle shapes having a common side
    mat_pointer bottom_wall_mat =
        std::make_shared<MaterialDiffuse>(Vec3(.1, .1, .9));
    obj_pointer bottom_wall_1 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(7, 0, 7), Vec3(7, 0, 0), bottom_wall_mat);
    obj_pointer bottom_wall_2 = std::make_unique<Triangle>(
        Vec3(0, 0, 0), Vec3(0, 0, 7), Vec3(7, 0, 7), bottom_wall_mat);
    bottom_wall_1->frame.origin.x = -3.5;
    bottom_wall_1->frame.origin.y = -2;
    bottom_wall_1->frame.origin.z = -7;
    bottom_wall_1->frame.lockFrame();
    bottom_wall_2->frame.origin.x = -3.5;
    bottom_wall_2->frame.origin.y = -2;
    bottom_wall_2->frame.origin.z = -7;
    bottom_wall_2->frame.lockFrame();
    shapes.push_back(std::move(bottom_wall_1));
    shapes.push_back(std::move(bottom_wall_2));

    mat_pointer metal = std::make_shared<MaterialMetallic>(Vec3(.8, .8, .9), .07);
    obj_pointer ball =
        std::make_unique<Sphere>(Vec3(0, 1.2, 0), 1.8, metal);
    ball->frame.origin.z = -5;
    ball->frame.origin.y = -2;
    ball->frame.lockFrame();
    shapes.push_back(std::move(ball));
}

void generate_scene(Camera& cam, std::vector<obj_pointer> &shapes, Scene scene)
{
    if (scene == Scene::CORNELL)
    {
        cam.look_at(Vec3(0, 0.3, -0.1), Vec3(0, 0, -3));
        generate_scene1(shapes);
    }
    else if (scene == Scene::TEAPOT)
    {
        cam.look_at(Vec3(1, 1.5, 2), Vec3(0, 0, -3));
        generate_scene2(shapes);
    }
    else if (scene == Scene::MONKEY)
    {
        cam.look_at(Vec3(1, 1.5, 3), Vec3(0, 0, 0));
        generate_scene3(shapes);
    }
    else if (scene == Scene::COLOR_BOX)
    {
        cam.look_at(Vec3(0, 0.3, -0.1), Vec3(0, 0, -3));
        generate_scene4(shapes);
    }
    std::cout << "[Tinge] Scene Generation complete" << std::endl;
}
