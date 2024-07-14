#pragma once
#include "math.cuh"
#include "ray.cuh"

/// Vertex (device only)
struct Vertex
{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

/// Triangle (device only)
class Triangle
{
private:
    int mId;    // material index
public:
    __device__ Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) : v1(v1), v2(v2), v3(v3) {}
    
    __device__ Triangle(const Triangle& other) : v1(other.v1), v2(other.v2), v3(other.v3) {}

    ~Triangle() = default;

    Vertex v1;  // vertex 1
    Vertex v2;  // vertex 2
    Vertex v3;  // vertex 3

    /// @brief 
    /// @return 
    constexpr __device__ __forceinline__ float getSurfaceArea() const {
        return  glm::cross(v1.position - v2.position, v1.position - v3.position).length();
    }

    /// @brief calculates the surface normal at the specified point
    /// @param xyz xyz coordintaes of the point
    /// @return the surface normal
    __device__ __forceinline__ glm::vec3 getNormal(const glm::vec3& xyz) const {
        const glm::vec3 n = glm::cross(v1.position - v2.position, v1.position - v3.position);
        const float inv_n2 = 1 / dot(n, n);
        const glm::vec3 na = glm::cross(v3.position - v2.position, xyz - v2.position);
        const glm::vec3 nb = glm::cross(v1.position - v3.position, xyz - v3.position);
        return getNormal(glm::dot(n, na) * inv_n2, glm::dot(n, nb) * inv_n2);
    }

    /// @brief calculates the surface normal at the specified point
    /// @param u uv coordinatees of the point
    /// @param v uv coordinatees of the point
    /// @return the surface normal
    __device__ __forceinline__ glm::vec3 getNormal(float u, float v) const {
        return u * v1.normal + v * v2.normal + (1 - u - v) * v3.normal;
    }


    /// @brief calculates the texture coordinates at the specified point
    /// @param xyz xyz coordintaes of the point
    /// @return the texture coordinates
    __device__ __forceinline__ glm::vec2 getTexCoord(const glm::vec3& xyz) const {
        const glm::vec3 n = glm::cross(v1.position - v2.position, v1.position - v3.position);
        const float inv_n2 = 1 / dot(n, n);
        const glm::vec3 na = glm::cross(v3.position - v2.position, xyz - v2.position);
        const glm::vec3 nb = glm::cross(v1.position - v3.position, xyz - v3.position);
        return getTexCoord(glm::dot(n, na) * inv_n2, glm::dot(n, nb) * inv_n2);
    }

    /// @brief calculates the texture coordinates at the specified point
    /// @param u uv coordinatees of the point
    /// @param v uv coordinatees of the point
    /// @return the texture coordinates
    __device__ __forceinline__ glm::vec2 getTexCoord(float u, float v) const {
        return u * v1.texcoord + v * v2.texcoord + (1 - u - v) * v3.texcoord;
    }

    __device__ void getMaterial()
    {
        /// TODO: Add this
    }
        
    /// @brief Ray-Triangle intersection using the Möller-Trumbore algorithm
    /// @param r Ray
    /// @param hit Intersection information
    __forceinline__ __device__ bool intersect(const Ray& r, HitInfo& hit) const {

        glm::vec3 e1 = v2.position - v1.position;
        glm::vec3 e2 = v3.position - v1.position;
        glm::vec3 rxe2 = glm::cross(r.dir, e2);
        float det = glm::dot(e1, rxe2);

        if (det > -TINGE_EPSILON && det < TINGE_EPSILON) // ray is parallel to the triangle
            return false;

        float inv_det = 1 / det;
        glm::vec3 s = r.origin - v1.position;
        float u = inv_det * glm::dot(s, rxe2);

        if (u < 0 || u > 1)     // intersection outside triangle
            return false; 

        glm::vec3 sxe1 = glm::cross(s, e1);
        float v = inv_det * glm::dot(r.dir, sxe1);

        if (v < 0 || u + v > 1) // intersection outside triangle
            return false;

        float t = inv_det * dot(e2, sxe1);
        if (t < TINGE_EPSILON || t > hit.dist)  // out of view
            return false;

        hit.dist = t;
        hit.hit = this;
        hit.u = u, hit.v = v;
        return true;
    }
};
