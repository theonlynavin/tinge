
# Tinge
A minimalistic path tracer

<img alt="Render of our logo" src="./static/Tinge.png">
<br/><br/>

Showcase of our renders

<img alt="Material render 1" src="./showcase/test_5_10.png">
<img alt="Material render 2" src="./showcase/colour_box_1.png">
<img alt="Material render 3" src="./showcase/metal_ball.png">
<img alt="Mesh render 1" src="./showcase/teapot_dark.png">

* Renders 3D scenes using ray tracing.
* Supports spheres, planes, triangles.
* Materials: Diffuse, Emissive, Metallic, Refractive.

## HOW IT WORKS?

Rays are generated from a virtual camera. Each ray is traced into the 3D scene. If it hits an object, its material defines the behavior:

- Diffuse: Equal reflection in all directions 
- Metallic: Emits no light of its own, has probability p to act as diffuse or reflective
- Transmission: Purely transmissive, Schlick's approximation ignored 
- Emissive: Material is considered not to reflect and purely emit
- Dielectric: Reflective and Refractive based on Fresnel's Equations

There are intersection schemes for different shapes, based on which intersection is determined. Further, for more complex shapes, they can be represented as a collection of triangles. The complex shape can be bounded by a box and intersection can be checked for if the ray intersects the bounding box. Further, we also have to take care that we don't accept an intersection that happpens in the backward direction. 

- Plane: Check if 't' (Ray parameter) at point of intersection is positive or not.
- Sphere: Check distance from ray origin to point of intersection.
- Triangle: Möller–Trumbore Algorithm 

The process recurses with new rays (path tracing).
Color contributions accumulate per pixel.
Final image is saved as a png file.


## HOW TO RENDER IMAGES ?

You can create your own 3D models using Blender or any other 3D modelling software and import them into Tinge using the `.obj` format. Follow the steps below:

1. Model in Blender

- Design your 3D object in Blender (e.g., cube, stacked shapes, etc.).
- Assign clear names to objects for easier identification in the `.obj` file.

2. Export as `.obj`

- In Blender, select the object(s) you want to export.
- Go to `File → Export → Wavefront (.obj)`
- Use these recommended export settings:
   - Selection Only** 
   - Include Normals**
   - Objects as OBJ Objects**

- This will generate:
   - `your_model.obj` — contains your model’s vertex positions, normals, and faces.

3. Add the Model to Your Tinge Project

- Place your `.obj` file inside the Tinge folder
- Modify the code in the file scene_generator.cpp to set up the scene that you wish to render


## ENVIRONMENT REQUIREMENTS

- CMake version 3.10 or higher
- A C++17 compatible compiler (e.g., GCC, Clang, or MSVC)
- Operating System: Windows, Linux, or macOS

## BUILDING TINGE

* Create the build directory
```
mkdir build
```

* navigate to the buid directory
```
cd build
```

* Run CMake to configure the project
```
cmake ..
```

* Build the project using make
```
make .
```

* Run the program after the build is completed, the rendered image will be written into the bin folder
