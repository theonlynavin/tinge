# /********************************************************
#  * @brief Specifies the minimum required version of CMake
#  ********************************************************/
cmake_minimum_required(VERSION 3.10)

# /******************************************************************
#  * @brief Defines the project name and initializes the build system
#  ******************************************************************/
project(Tinge)

# /***********************************************
#  * @brief Set the C++ language standard to C++17
#  ***********************************************/
set(CMAKE_CXX_STANDARD 17)

# /********************************************************
#  * @brief Export compile commands (for tools like clangd)
#  ********************************************************/
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# /**********************************************************
#  * @brief Detect platform and set PLATFORM_NAME accordingly
#  **********************************************************/
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_NAME "win")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_NAME "linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PLATFORM_NAME "mac")
endif()

# /*****************************************************************
#  * @brief Set default build type to Release if not already defined
#  *****************************************************************/
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# /*********************************************************
#  * @brief Set the output directory for the compiled binary
#  *********************************************************/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM_NAME})

# /*******************************************************
#  * @brief Define the list of source files to be compiled
#  *******************************************************/
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

# /***********************************************************
#  * @brief Add executable target 'tinge' with defined sources
#  ***********************************************************/
add_executable(tinge ${SOURCES})

# /*********************************************************************
#  * @brief Define preprocessor macro to enable math constants like M_PI
#  *********************************************************************/
add_compile_definitions(_USE_MATH_DEFINES)

# /**********************************************************
#  * @brief Include header files from the 'include' directory
#  **********************************************************/
target_include_directories(tinge PRIVATE include)
