#include "triangle.cuh"
#include "handle.cuh"
#include "array.cuh"

class Mesh
{
private:
    Array<Triangle> triangles;
    int numTriangles;
public:
    __device__ Mesh(const Array<Vertex>& vertices, const Array<int>& indices) 
        : numTriangles(indices.count() / 3)
    {
        triangles.reserve(numTriangles);
        for (size_t i = 0; i < numTriangles; i++)
        {
            triangles[i] = Triangle(
                    vertices[indices[3*i + 0]], 
                    vertices[indices[3*i + 1]], 
                    vertices[indices[3*i + 2]]
            );
        }
    }

    __device__ ~Mesh() = default;

    /// @brief Ray-Mesh intersection
    /// @param r Ray
    /// @param hit Intersection information
    __forceinline__ __device__ bool intersect(const Ray& r, HitInfo& hit) {
        bool rayHit = false;
        for (int i = 0; i < numTriangles; i++) {
            rayHit |= triangles[i].intersect(r, hit);
        }
        return rayHit;
    }
};
