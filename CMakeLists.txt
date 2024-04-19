cmake_minimum_required(VERSION 3.0.0)
project(tinge VERSION 0.1.0 LANGUAGES CUDA C CXX)

# Set up CUDA

set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_FLAGS ${CMAKE_CUDA_FLAGS} "-g -G")  # enable cuda-gdb

# Project structure

set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include)
set(LINK_DIRECTORIES ${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Fetch compilation files

set(SRC "src/main.cpp")

# Build the executable

add_executable(tinge ${SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
