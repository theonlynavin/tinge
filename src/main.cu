#include <iostream>

#define TINGE_DEBUG
#include "core/core.h"

#include <GLFW/glfw3.h>
#include <cuda_gl_interop.h>

__global__ void kernel(cudaSurfaceObject_t surface, float t, int width, int height) 
{
    unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x < width && y < height) 
    {
        uchar4 color = uchar4{0,0,0,0};
        
        float y0 = sin(t - 5*float(x)/width);

        if (abs(float(4*(y - 0.5*height))/(height) - y0) < 1e-2)
        {
            float v = 255 * abs(y0);
            color.x = v;
            color.y = v;
            color.z = v;
            color.w = v;
        }   
        surf2Dwrite(color, surface, x * sizeof(uchar4), y);
    }
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
    glCall(glViewport(0, 0, width, height));
    initializeTexture(width, height);
}

int main(int argc, char const *argv[])
{
    // Initialize GLFW

    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create Window

    int width = 1000, height = 1000;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(width, height, "tinge", NULL, NULL);
    glfwSetWindowSizeCallback(window, resizeWindow);
    glfwMakeContextCurrent(window);

    // Initialize GLEW

    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Check for CUDA availability

    int dev;
    cudaCall(cudaGetDevice(&dev));

    // Main render loop

    initializeTexture(width, height);

    while (!glfwWindowShouldClose(window)) 
    {
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

        dim3 threadsPerBlock(16, 16);
        dim3 numBlocks((width + threadsPerBlock.x - 1) / threadsPerBlock.x, (height + threadsPerBlock.y - 1) / threadsPerBlock.y);
        kernel<<<numBlocks, threadsPerBlock>>>(cudaSurface, glfwGetTime(), width, height);
        
        cudaCall(cudaDeviceSynchronize());
        cudaCall(cudaDestroySurfaceObject(cudaSurface));    
        cudaCall(cudaGraphicsUnmapResources(1, &interop.cuda_texture, 0));
        
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
      
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwGetWindowSize(window, &width, &height);
    }

    glfwTerminate();
    
    return 0;
}
