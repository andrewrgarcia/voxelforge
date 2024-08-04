cmake_minimum_required(VERSION 3.0.0)
project(voxelforge VERSION 0.1.0)

# Include pybind11
add_subdirectory(pybind11-2.13.1)
include_directories(pybind11-2.13.1/include)

# Add the C++ source files
pybind11_add_module(voxelforge VoxelForge/voxel.cpp)
