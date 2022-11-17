cmake_minimum_required(VERSION 3.4)

# This CMake file describes the private (compiled) implementation of PyPlayground.
# It outputs a '_pyplayground.xxx' lib that's imported via the Python implementation.
# See the 'src_py' tree for more info.

project(_pyplayground)

# C++ 17 standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add our pybind11 lib.
add_subdirectory(lib/pybind11)

# Include SDL2.
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

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
  src_cpp/render/container.h
  src_cpp/render/container.cpp
)

set(SRC_CPP_TASK
  src_cpp/task/task_manager.h
  src_cpp/task/task_manager.cpp
  src_cpp/task/task.h
  src_cpp/task/task.cpp
)

# All cpp source files.
set(SOURCE_CPP
  ${SRC_CPP_WRAPPER}
  ${SRC_CPP_CORE}
  ${SRC_CPP_DISPLAY}
  ${SRC_CPP_RENDER}
  ${SRC_CPP_TASK}
)

# Generate Python bindings for our source files.
pybind11_add_module(_pyplayground ${SOURCE_CPP})

# Link libs.
target_link_libraries(_pyplayground PRIVATE ${SDL2_LIBRARIES})
