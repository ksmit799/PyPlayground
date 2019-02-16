cmake_minimum_required(VERSION 3.2)
project(PyPlayground VERSION 1.0.0)

# Set CMake module/source directories.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# To create a folder hierarchy within Visual Studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# C++ 11 standard.
set(CMAKE_CXX_STANDARD 11)

# Find our pybind11 lib.
add_subdirectory(libs/pybind11)

# Include SDL2.
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include OpenGL.
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Include GLEW.
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Include GLM.
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# Include cpp files/headers.
include_directories("${CMAKE_SOURCE_DIR}/src_cpp/")

# Glob all cpp files/headers.
file(GLOB_RECURSE SOURCE_CPP
	"${CMAKE_SOURCE_DIR}/src_cpp/*.cpp"
	"${CMAKE_SOURCE_DIR}/src_cpp/*.h"
)

# Generate Python bindings for our source files.
pybind11_add_module(PyPlayground ${SOURCE_CPP})

# Link libs.
target_link_libraries(PyPlayground PRIVATE ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})