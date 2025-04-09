#pragma once
#include "camera.h"
#include "frame.h"
#include "material.h"
#include "math.h"
#include <memory>
#include <utility>
#include <vector>

/**************************************************************
 * Encapsulation class for output of intersection routine
 ***************************************************************/
struct IntersectionOut {
    bool hit;    /**< Check if the ray hit*/
    Vec3 normal; /**< Normal vector at point of intersection */
    float t;     /**< Distance traversed by light ray */
    Vec3 point;  /**< Point of intersection of the light ray*/
    Ray w0;
    mat_pointer hit_mat;
    IntersectionOut();
};

/********************************************
 * Abstract class for all implemented shapes
 ********************************************/
struct AbstractShape {
    Frame frame; /**< Frame of the object*/
    mat_pointer material;
    /***************************************************
     * @brief Common intersection routine for all shapes
     * @param ray Light ray to check in world space
     * @return IntersectionOut class with output data
     ***************************************************/
    IntersectionOut intersect(const Ray &ray);
    Vec3 get_normal(const Vec3 &point);

  protected:
    /************************************************************************
     * @brief Shape wise intersection routine to  be overridden by all shapes
     * @param ray Light ray to check in frame space
     * @return Did ray hit
     ************************************************************************/
    virtual bool _intersect(const Ray &ray, IntersectionOut &intsec_out) = 0;

    // Point in World space
    virtual Vec3 _get_normal(const Vec3 &point) = 0;
};

using obj_pointer = std::shared_ptr<AbstractShape>;

struct Triangle : AbstractShape {
    Vec3 v1, v2, v3; /**< Position vectors of triangle vertices*/
    Vec3 n;          /**< Normal vector of triangle*/

    /******************************************
     * @brief Parametrized triangle constructor
     * @param v1 1st vertex of the triangle
     * @param v2 2nd vertex of the triangle
     * @param v3 3rd vertex of the triangle
     ******************************************/
    Triangle(Vec3 v1, Vec3 v2, Vec3 v3, mat_pointer mat);
    ~Triangle();

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};

struct Sphere : AbstractShape {
    Vec3 c;  /**< Position vector of the sphere's centre */
    float r; /**< Radius of sphere */

    /************************************************
     * @brief Parametrized sphere constructor
     * @param centre Centre of the sphere
     * @param radius Radius of the sphere
     ***********************************************/
    Sphere(Vec3 centre, float radius,
           mat_pointer mat); // Parametrized Sphere constructor
    ~Sphere();

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};

struct Plane : AbstractShape {
    Vec3 n; /**< Normal vector of plane*/
    Vec3 p; /**< Position vector of some point in plane*/

    /************************************************************
     * @brief Parametrized sphere constructor
     * @param normal Normal of the sphere
     * @param point A point on the plane of the sphere
     ***********************************************************/
    Plane(Vec3 normal, Vec3 point,
          mat_pointer mat); // Parametrized triangle constructor
    ~Plane();

  protected:
    bool _intersect(const Ray &ray, IntersectionOut &intsec_out) override;
    Vec3 _get_normal(const Vec3 &point) override;
};

/******************************************************
 * @brief Find closest shape that intersects the ray
 * @param v Vector of the objects to check
 * @param ray Ray to check with
 ******************************************************/
std::pair<obj_pointer, IntersectionOut>
closestIntersect(const std::vector<obj_pointer> &v, const Ray &ray);
