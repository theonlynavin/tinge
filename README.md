
# Tinge
A minimalistic path tracer

<img alt="Render of our logo" src="./static/Tinge.png">
<br/><br/>

Showcase of our renders

<img alt="Material render 1" src="./showcase/test_5_10.png">
<img alt="Material render 2" src="./showcase/colour_box_1.png">
<img alt="Material render 3" src="./showcase/metal_ball.png">

* Renders 3D scenes using ray tracing.
* Supports spheres, planes, triangles.
* Materials: Diffuse, Emissive, Metallic, Refractive.

## HOW IT WORKS?

Rays are generated from a virtual camera. Each ray is traced into the 3D scene. If it hits an object, its material defines the behavior:

    -Diffuse: scattered reflection

    -Metallic: specular reflection

    -Transmission: refracted rays

    -Emissive: light emission

The process recurses with new rays (path tracing).

Color contributions accumulate per pixel.

Final image is saved as test.png.


## HOW TO RENDER IMAGES ?

You can create your own 3D models using **Blender** and import them into Tinge using the `.obj` format. Follow the steps below:

1. Model in Blender

- Design your 3D object in Blender (e.g., cube, stacked shapes, etc.).
- Assign clear names to objects for easier identification in the `.obj` file.

2. Export as `.obj`

In Blender:

1. Select the object(s) you want to export.
2. Go to `File → Export → Wavefront (.obj)`
3. Use these recommended export settings:
   - Selection Only** 
   - Include Normals**
   - Objects as OBJ Objects**

This will generate:
- `your_model.obj` — contains your model’s vertex positions, normals, and faces.

---

3. Add the Model to Your Tinge Project

Place your `.obj` file inside the Tinge folder


## ENVIRONMENT REQUIREMENTS

- **CMake** version 3.10 or higher
- A C++17 compatible compiler (e.g., GCC, Clang, or MSVC)
- Operating System: Windows, Linux, or macOS

* Create the build directory 
mkdir build

* navigate to the buid directory
cd build

* Run CMake to configure the project
cmake ..

* Build the project using make
make

* run the program after the build is completed

* image will be written into the bin folder

*******************************************************************************/
