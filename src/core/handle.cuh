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

#define tingeError(msg) { handleTingeError(msg, __FILE__, __LINE__ ); }     // handles Tinge Errors
#define tingeWarn(msg) { handleTingeWarning(msg, __FILE__, __LINE__ ); }    // handles Tinge Warnings

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

inline void handleTingeError(const std::string& message, const char* file, int line)
{
    std::cerr << file << "(" << line << "):\t" << message << "(Error)" << std::endl;
}

inline void handleTingeWarning(const std::string& message, const char* file, int line)
{
    std::cerr << file << "(" << line << "):\t" << message << "(Warning)" << std::endl;
}