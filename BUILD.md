# Building VoxelForge Locally

This document provides instructions on how to build the VoxelForge package locally from the source.

## Prerequisites

Before building, ensure you have the following dependencies installed:

- **CMake**: Version 3.12 or later
- **Python**: Version 3.7 or later
- **pip**: The Python package installer
- **Eigen**: C++ template library for linear algebra
- **LibTorch**: PyTorch C++ libraries

Ensure that you have the required dependencies available on your system and that they are properly configured in your environment.

## Step-by-Step Build Instructions

### 1. Clean the Build Directory

First, remove any existing build files to ensure a clean build environment:

```bash
rm -rf build/
```

### 2. Recreate the Build Directory and Configure the Project

Next, recreate the build directory and configure the project using CMake:

```bash
mkdir build
cd build
cmake ..
```

This command will generate the necessary build files for your system.

### 3. Build the Project

Once configured, build the project by running:

```bash
make
```

This will compile the C++ source files and generate the `voxelforge_cpp` module.

### 4. Reinstall the Package

After building, you can reinstall the package using pip:

```bash
cd ..
pip install .
```

This will install the VoxelForge package locally, allowing you to use it within your Python environment.

## Additional Notes

- **Custom Build Options**: If you need to customize the build process (e.g., specifying different paths for Eigen or LibTorch), you can modify the `CMakeLists.txt` file or pass additional options to CMake.
- **Windows Users**: If you are building on Windows, ensure you have the appropriate build tools (e.g., Visual Studio) installed, and follow the specific instructions for copying LibTorch DLLs, as described in the `CMakeLists.txt` file.

## Troubleshooting

- If you encounter any issues during the build process, make sure all dependencies are installed and available in your system's PATH.
- Refer to the CMake and compiler logs for detailed error messages and debugging information.

If you have any questions or need further assistance, please refer to the official documentation or open an issue on the project's GitHub repository.