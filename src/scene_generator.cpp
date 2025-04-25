#include "scene_generator.h"
#include "material.h"
#include "math.h"
#include "objects.h"
#include <memory>

void generate_scene(std::vector<obj_pointer> &shapes) {
  
    //sets up the backwall which is an emissive rectangle consisting of two triangle shapes having a common side
    mat_pointer emmisive = std::make_shared<MaterialEmissive>(Vec3(1, 1, 1), 1.8);
    obj_pointer back_wall_1 = std::make_shared<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), Vec3(-3.5, 2, 0), emmisive);
    obj_pointer back_wall_2 = std::make_shared<Triangle>(
        Vec3(-3.5, -2, 0), Vec3(3.5, -2, 0), Vec3(3.5, 2, 0), emmisive);
    back_wall_1->frame.origin.z = -7;
    back_wall_1->frame.lockFrame();
    back_wall_2->frame.origin.z = -7;
    back_wall_2->frame.lockFrame();
  
    shapes.push_back(back_wall_1);
    shapes.push_back(back_wall_2);

    mat_pointer emmisive_ = std::make_shared<MaterialEmissive>(Vec3(0, 0, 0), 1);
    obj_pointer front_wall_1 = std::make_shared<Triangle>(
        Vec3(3.5, 2, 0), Vec3(-3.5, -2, 0), Vec3(-3.5, 2, 0), emmisive_);
    obj_pointer front_wall_2 = std::make_shared<Triangle>(
        Vec3(3.5, -2, 0), Vec3(-3.5, -2, 0), Vec3(3.5, 2, 0), emmisive_);
    front_wall_1->frame.origin.z = 0;
    front_wall_1->frame.lockFrame();
    front_wall_2->frame.origin.z = 0;
    front_wall_2->frame.lockFrame();
    //shapes.push_back(front_wall_1);
    //shapes.push_back(front_wall_2);

    //setups the right side wall which a diffuse material rectangle consisting of two triangle shapes having a common side
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
    shapes.push_back(right_wall_1);
    shapes.push_back(right_wall_2);

    //setups the left side wall which a diffuse material rectangle consisting of two triangle shapes having a common side
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
    shapes.push_back(left_wall_1);
    shapes.push_back(left_wall_2);

    //setups the top wall which a diffuse material rectangle consisting of two triangle shapes having a common side
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
    //shapes.push_back(top_wall_1);
    //shapes.push_back(top_wall_2);
  
    //setups the bottom wall which a diffuse material rectangle consisting of two triangle shapes having a common side
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
    shapes.push_back(bottom_wall_1);
    shapes.push_back(bottom_wall_2);
  
    mat_pointer glass = std::make_shared<MaterialDielectric>(Vec3(1, 1, 1), Vec3(1, 1, 1), 1.5, 0);

    mat_pointer plastic = std::make_shared<MaterialDielectric>(Vec3(0.8, 0.2, 0.3), Vec3(0.8, 0.2, 0.3), 1.2, 0.2);

    
    mat_pointer metal_ball =
       std::make_shared<MaterialMetallic>(Vec3(.6, .6, .6), 0);
    obj_pointer ball =
        std::make_shared<Sphere>(Vec3(0, 1.2, 0), 1.2, glass);
    ball->frame.origin.z = -3;
    ball->frame.origin.y = -2;
    ball->frame.lockFrame();
    shapes.push_back(ball);
  
    //setups the sphere which is transmissive
    obj_pointer sphere = std::make_shared<Sphere>(
        Vec3(0,0,-5), 0.6, glass);
    
    //shapes.push_back(sphere);

    mat_pointer light_ball =
        std::make_shared<MaterialEmissive>(Vec3(.9, .9, .1), 4);
    obj_pointer lball1 =
        std::make_shared<Sphere>(Vec3(0, 0, 0), 0.6, light_ball);
    lball1->frame.origin.z = -5;
    lball1->frame.origin.y = 1.5;
    lball1->frame.origin.x = 1;
    lball1->frame.lockFrame();
    shapes.push_back(lball1);

    obj_pointer lball2 =
        std::make_shared<Sphere>(Vec3(0, 0, 0), 0.6, light_ball);
    lball2->frame.origin.z = -5;
    lball2->frame.origin.y = -0.3;
    lball2->frame.origin.x = -3;
    lball2->frame.lockFrame();
    shapes.push_back(lball2);

    obj_pointer lball3 =
        std::make_shared<Sphere>(Vec3(0, 0, 0), 0.3, light_ball);
    lball3->frame.origin.z = -4;
    lball3->frame.origin.y = -1.6;
    lball3->frame.origin.x = 2.3;
    lball3->frame.lockFrame();
    shapes.push_back(lball3);
}



