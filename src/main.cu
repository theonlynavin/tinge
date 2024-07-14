#include <iostream>

#define TINGE_DEBUG
#include "handle.cuh"
#include "triangle.cuh"
#include "mesh.cuh"
#include "array.cuh"
#include "objl/OBJ_Loader.h"

#include <glfw/glfw3.h>
#include <cuda_gl_interop.h>


__global__ void initializeMesh(Mesh* mesh, objl::Vertex* vertices, size_t numVertices, unsigned int* indices, size_t numIndices)
{   
    if (threadIdx.x == 0 && blockIdx.x == 0) 
    {        
        Array<Vertex> v;
        v.reserve(numVertices);

        for (size_t i = 0; i < numVertices; i++)
        {
            const objl::Vertex& vertex = vertices[i];

            v[i].position = glm::vec3(vertex.Position.X, vertex.Position.Y, vertex.Position.Z);
            v[i].texcoord = glm::vec2(vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y);
            v[i].normal = glm::vec3(vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z);
        }

        *mesh = Mesh(v, Array<unsigned int>(indices, numIndices));
    }
}

__global__ void updateObjects()
{
    
}

__global__ void renderImage(cudaSurfaceObject_t surface, int width, int height, Mesh* m, float t) 
{
    const float ar = float(width)/float(height);
    constexpr float scale = 0.7;
    constexpr glm::vec3 blue = glm::vec3{0.5, 0.7, 0.9};
    constexpr glm::vec3 white = glm::vec3{1, 1, 1};
 
    for (int y = blockIdx.y * blockDim.y + threadIdx.y; y < height; y += blockDim.y * gridDim.y)
    {            
        for (int x = blockIdx.x * blockDim.x + threadIdx.x; x < width; x += blockDim.x * gridDim.x)
        {            
            const float u = 2*float(x)/width-1;
            const float v = 2*float(y)/height-1;
            
            glm::vec3 sky = glm::mix(white, blue, 0.5*(v+1));

            glm::mat4 trnsfm(1.0f);
            trnsfm = glm::translate(trnsfm, glm::vec3(0, -1, 0));
            trnsfm = glm::rotate(trnsfm, t, glm::normalize(glm::vec3(0, 1, 0)));
            trnsfm = glm::scale(trnsfm, glm::vec3(0.02));

            uchar4 color = uchar4{(unsigned char)(sky.x*255), (unsigned char)(sky.y*255), (unsigned char)(sky.z*255), 255};

            Ray r = Ray(glm::vec3{0,0,4}, normalize(glm::vec3{ar*u*scale,v*scale,-1}));
            HitInfo hit = HitInfo();

            m->apply(trnsfm);

            if (m->intersect(r, hit))
            {
                glm::vec3 n = hit.hit->getNormal(hit.u, hit.v);

                color.x = 255 * n.x;
                color.y = 255 * n.y;
                color.z = 255 * n.z;
            }

            surf2Dwrite(color, surface, x * sizeof(uchar4), y);
        }   
    }
}

std::vector<Mesh*> loadModel(const std::string& path)
{
    std::vector<Mesh*> meshes;

    objl::Loader loader;
    if (loader.LoadFile(path))
    {
        for (objl::Mesh& mesh : loader.LoadedMeshes)
        {
            Mesh* m;
            cudaCall(cudaMalloc((void**)&m, sizeof(Mesh))); 

            objl::Vertex* p_vertices;
            cudaCall(cudaMallocHost((void**)&p_vertices, sizeof(objl::Vertex) * mesh.Vertices.size()));
            cudaCall(cudaMemcpy(p_vertices, &(mesh.Vertices.front()), sizeof(objl::Vertex) * mesh.Vertices.size(), cudaMemcpyHostToHost));

            unsigned int* p_indices;
            cudaCall(cudaMallocHost((void**)&p_indices, sizeof(unsigned int) * mesh.Indices.size()));
            cudaCall(cudaMemcpy(p_indices, &(mesh.Indices.front()), sizeof(unsigned int) * mesh.Indices.size(), cudaMemcpyHostToHost));

            initializeMesh<<<1, 1>>>(m, p_vertices, mesh.Vertices.size(), p_indices, mesh.Indices.size());
            cudaCall(cudaPeekAtLastError());
            cudaCall(cudaDeviceSynchronize());
            
            meshes.push_back(m);
        }
    }

    return meshes;
}

struct Interop
{
    cudaGraphicsResource_t cuda_texture;
    GLuint gl_texture;
} interop;

void initializeTexture(int width, int height) 
{
    glCall(glDeleteTextures(1, &interop.gl_texture));
    glCall(glGenTextures(1, &interop.gl_texture));
    glCall(glBindTexture(GL_TEXTURE_2D, interop.gl_texture));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

    cudaCall(
        cudaGraphicsGLRegisterImage(&interop.cuda_texture, interop.gl_texture, GL_TEXTURE_2D, 
        cudaGraphicsRegisterFlagsSurfaceLoadStore)
    );
}

void resizeWindow(GLFWwindow* window, int width, int height)
{
    cudaCall(cudaGraphicsUnregisterResource(interop.cuda_texture));
    glCall(glViewport(0, 0, width, height));
    initializeTexture(width, height);
}

int main(int argc, char const *argv[])
{
    // Initialize GLFW

    if (!glfwInit()) 
    {
        tingeError("Failed to initialize GLFW");
    }

    // Create Window

    int width = 1000, height = 1000;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(width, height, "Tinge", NULL, NULL);

    if (window == NULL)
    {
        tingeError("Failed to create window!");
    }

    glfwSetWindowSizeCallback(window, resizeWindow);
    glfwMakeContextCurrent(window);

    // Initialize GLEW

    if (glewInit() != GLEW_OK) 
    {
        tingeError("Failed to initialize GLEW");
    }
    
    // Check for CUDA availability

    int dev;
    cudaCall(cudaGetDevice(&dev));

    glCall(glEnable(GL_FRAMEBUFFER_SRGB));

    // Main render loop

    initializeTexture(width, height);
    
    int numSMs;
    cudaDeviceGetAttribute(&numSMs, cudaDevAttrMultiProcessorCount, 0);
    numSMs = 14;

    std::vector<Mesh*> cube = loadModel("/home/navin/tinge/assets/low_poly_rabbit.obj");

    while (!glfwWindowShouldClose(window)) 
    {    
        float start_t = glfwGetTime();

        // Render to the texture

        cudaCall(cudaGraphicsMapResources(1, &interop.cuda_texture, 0));

        cudaArray_t cudaTextureArray;
        cudaCall(cudaGraphicsSubResourceGetMappedArray(&cudaTextureArray, interop.cuda_texture, 0, 0));

        cudaResourceDesc resDesc;
        memset(&resDesc, 0, sizeof(resDesc));
        resDesc.resType = cudaResourceTypeArray;
        resDesc.res.array.array = cudaTextureArray;

        cudaSurfaceObject_t cudaSurface;
        cudaCall(cudaCreateSurfaceObject(&cudaSurface, &resDesc));

        dim3 threadsPerBlock(numSMs, numSMs);
        dim3 numBlocks((width + threadsPerBlock.x - 1) / (threadsPerBlock.x), (height + threadsPerBlock.y - 1) / (threadsPerBlock.y));
        renderImage<<<numBlocks, threadsPerBlock>>>(cudaSurface, width, height, cube[0], start_t);
        
        cudaCall(cudaPeekAtLastError());
        cudaCall(cudaDeviceSynchronize());
        cudaCall(cudaDestroySurfaceObject(cudaSurface));    
        cudaCall(cudaGraphicsUnmapResources(1, &interop.cuda_texture, 0));

        float end_t = glfwGetTime();
        
        // Draw the rendered texture

        glCall(glClear(GL_COLOR_BUFFER_BIT));
        glCall(glClearColor(0, 0, 1, 1));

        glCall(glEnable(GL_TEXTURE_2D));
        glCall(glBindTexture(GL_TEXTURE_2D, interop.gl_texture));
        
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
        glCall(glEnd());

        glCall(glDisable(GL_TEXTURE_2D));

        // GLFW render calls
      
        glfwGetWindowSize(window, &width, &height);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwGetWindowSize(window, &width, &height);

        float final_t = glfwGetTime();   

        std::cout << "CUDA: " << 1000 * (end_t - start_t) << "ms, OpenGL: " << 1000 * (final_t - end_t) << "ms\n";
        std::cout << "Framerate: " << 1 / (final_t - start_t) << "\n\033[A\033[A\r"; 
    }

    std::cout << "\n\n" << std::endl;

    glfwTerminate();
    
    return 0;
}

/*float r = 0.05;

        t = 5*t;

        float cx = 0.5*r*(t - sin(t));// - floor(0.5*r*(t - sin(t)));    

        if (abs(2*(u - cx)) < 1e-2)
        {
            if (cx < 0.45)
            {
                if (abs(v + 0.2 - r*(1 - cos(t))) < 1e-2)
                {
                    color.z = u * 255;
                    color.y = 0.5*(v+1) * 255;
                    color.x = 255;
                    color.w = 255;
                }
            }
            else
            {   
                if (abs(v + 0.2 - r*(1 - cos(t)) - 3.4 + t/5) < 1e-2)
                {
                    color.z = u * 255;
                    color.y = 0.5*(v+1) * 255;
                    color.x = 255;
                    color.w = 255;
                }
            }
        }   
        if (u < 0.4 && v < -0.2)
        {
            color.x = 0.5* 255;
            color.y = 0.5* 255;
            color.z = 0.5* 255;
            color.w = 255;
        }*/
