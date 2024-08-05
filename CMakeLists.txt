cmake_minimum_required(VERSION 3.12)
project(voxelforge VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include pybind11
add_subdirectory(pybind11-2.13.1)
include_directories(pybind11-2.13.1/include)

# Include Eigen
include_directories("/usr/local/include/eigen3")

# Include LibTorch
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libtorch")
find_package(Torch REQUIRED)
include_directories(${TORCH_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Add the C++ source files
pybind11_add_module(voxelforge VoxelForge/voxel.cpp)

# Link LibTorch
target_link_libraries(voxelforge "${TORCH_LIBRARIES}")

# Set C++ standard
set_property(TARGET voxelforge PROPERTY CXX_STANDARD 17)

# Copy LibTorch DLLs on Windows
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET voxelforge
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:voxelforge>)
endif (MSVC)
