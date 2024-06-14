#pragma once
#include <GL/glew.h>
#include <cuda_runtime.h>
#include <iostream>

#ifdef TINGE_DEBUG
#define cudaCall(err) handleCudaCall(err, __FILE__, __LINE__)   // handles CUDA API Calls
#define glCall(f) { f; handleGLCall(__FILE__, __LINE__); }      // handles OpenGL API Calls

#else
#define cudaCall(err) err                                       // handles CUDA API Calls
#define glCall(f) f                                             // handles OpenGL API Calls
#endif

inline void handleCudaCall(cudaError_t err, const char* file, int line)
{
    if (err != cudaSuccess)
    {
        std::cerr << file << "(" << line << "):\t" << cudaGetErrorString(err) << "(" << err << ")" << std::endl;
        std::exit(err);
    }
}

inline void handleGLCall(const char* file, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cerr << file << "(" << line << "):\t" << glewGetErrorString(err) << "(" << err << ")" << std::endl;
        std::exit(err);
    }
}