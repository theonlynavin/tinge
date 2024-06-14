cmake_minimum_required(VERSION 3.0.0)
project(tinge VERSION 0.1.0 LANGUAGES CUDA C CXX)

# Set up CUDA

set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_FLAGS ${CMAKE_CUDA_FLAGS} "-Xptxas -O3")  # -g -G for cuda-gdb
                                                   # -Xptxas -O3 for optimization
find_library(CUDART_LIBRARY cudart ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})

# Set up project structure

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(
    ${PROJECT_SOURCE_DIR}/include 
    ${PROJECT_SOURCE_DIR}/src/core 
    ${PROJECT_SOURCE_DIR}/src/shapes 
    ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib 
    ${CUDART_LIBRARY}
)

set(SRC "src/main.cu")

# Build the executable

add_executable(tinge ${SRC})
target_link_libraries(tinge "libglfw3.a" "libGLEW.a" "GL")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
