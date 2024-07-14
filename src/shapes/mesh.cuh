#include "triangle.cuh"
#include "handle.cuh"
#include "array.cuh"

class Mesh
{
private:
    Array<Triangle> m_world, m_local;
    int numTriangles;
public:
    __device__ Mesh(const Array<Vertex>& vertices, const Array<unsigned int>& indices) 
        : numTriangles(indices.count() / 3)
    {
        m_local.reserve(numTriangles);
        m_world.reserve(numTriangles);
        for (size_t i = 0; i < numTriangles; i++)
        {
            Triangle tri = Triangle(
                    vertices[indices[3*i + 0]], 
                    vertices[indices[3*i + 1]], 
                    vertices[indices[3*i + 2]]
            );
            m_local[i] = tri;
            m_world[i] = tri;
        }
    }

    __device__ ~Mesh() = default;

    /// @brief Ray-Mesh intersection
    /// @param r Ray
    /// @param hit Intersection information
    __forceinline__ __device__ bool intersect(const Ray& r, HitInfo& hit) const {
        bool rayHit = false;
        for (int i = 0; i < numTriangles; i++) {
            rayHit |= m_world[i].intersect(r, hit);
        }
        return rayHit;
    }

    /// @brief Applies the given transformation to the mesh
    /// @param transformation Transformation Matrix
    __forceinline__ __device__ void apply(const glm::mat4& transformation)
    {
        glm::mat3 normalTransformation = glm::transpose(glm::inverse(glm::mat3(transformation)));

        for (size_t i = 0; i < numTriangles; i++)
        {
            m_world[i].v1.position = (transformation * glm::vec4(m_local[i].v1.position, 1)).xyz();
            m_world[i].v1.normal = normalTransformation * m_local[i].v1.normal;

            m_world[i].v2.position = (transformation * glm::vec4(m_local[i].v2.position, 1)).xyz();
            m_world[i].v2.normal = normalTransformation * m_local[i].v2.normal;

            m_world[i].v3.position = (transformation * glm::vec4(m_local[i].v3.position, 1)).xyz();
            m_world[i].v3.normal = normalTransformation * m_local[i].v3.normal;
        }        
    }

    /// @return The mesh data in local-space
    __forceinline__ __device__ constexpr const Array<Triangle>& localTris() const
    {
        return m_local;
    }

    /// @return The mesh data in world-space
    __forceinline__ __device__ constexpr const Array<Triangle>& worldTris() const
    {
        return m_world;
    }
};
