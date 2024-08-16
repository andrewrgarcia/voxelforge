cmake_minimum_required(VERSION 3.12)
project(voxelforge VERSION 0.1.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include pybind11
add_subdirectory(pybind11-2.13.1)

# Fetch and include Eigen
include(FetchContent)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# Include LibTorch
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libtorch")
find_package(Torch REQUIRED)
include_directories(${TORCH_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Include directories for header files
include_directories(${eigen_SOURCE_DIR} VoxelForge)

# Add the C++ source files
pybind11_add_module(voxelforge VoxelForge/main.cpp VoxelForge/voxel.cpp VoxelForge/octree.cpp)

# Link LibTorch and other libraries
target_link_libraries(voxelforge PRIVATE ${TORCH_LIBRARIES})

# Ensure Eigen and VoxelForge are included
target_include_directories(voxelforge PRIVATE ${eigen_SOURCE_DIR} VoxelForge)

# Copy LibTorch DLLs on Windows
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET voxelforge
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:voxelforge>)
endif (MSVC)
