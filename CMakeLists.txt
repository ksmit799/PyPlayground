cmake_minimum_required(VERSION 3.2)

# This CMake file describes the private (compiled) implementation of PyPlayground.
# It outputs a '_pyplayground.xxx' lib that's imported via the Python implementation.
# See the 'src_py' tree for more info.

project(_pyplayground)

# Set CMake module/source directories.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# C++ 11 standard.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add our pybind11 lib.
add_subdirectory(deps/pybind11)

# Include SDL2.
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include cpp source files.
include_directories("${CMAKE_SOURCE_DIR}/src_cpp/")

set(SRC_CPP_WRAPPER
  src_cpp/wrapper.h
  src_cpp/wrapper.cpp
)

set(SRC_CPP_CORE
  src_cpp/core/playground_base.h
  src_cpp/core/playground_base.cpp
  src_cpp/core/playground_exception.h
  src_cpp/core/playground_exception.cpp
  src_cpp/core/color.h
  src_cpp/core/color.cpp
)

set(SRC_CPP_DISPLAY
  src_cpp/display/window.h
  src_cpp/display/window.cpp
)

set(SRC_CPP_RENDER
  src_cpp/render/renderer.h
  src_cpp/render/renderer.cpp
)

# All cpp source files.
set(SOURCE_CPP
  ${SRC_CPP_WRAPPER}
  ${SRC_CPP_CORE}
  ${SRC_CPP_DISPLAY}
  ${SRC_CPP_RENDER}
)

# Generate Python bindings for our source files.
pybind11_add_module(_pyplayground ${SOURCE_CPP})

# Link libs.
target_link_libraries(_pyplayground PRIVATE ${SDL2_LIBRARIES})