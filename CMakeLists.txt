
cmake_minimum_required(VERSION 3.10)

project(Tinge)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_FLAGS "/Ot /Oi /O2 /Ob3 /fp:fast /GL /Qpar")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_NAME "win")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_NAME "linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PLATFORM_NAME "mac")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM_NAME})

set(SOURCES
    src/main.cpp
    src/util.cpp
    src/random.cpp
    src/objects.cpp
    src/camera.cpp
    src/frame.cpp
    src/renderer.cpp
    src/scene_generator.cpp
)

add_executable(tinge ${SOURCES})

add_compile_definitions(_USE_MATH_DEFINES)

target_include_directories(tinge PRIVATE include)
