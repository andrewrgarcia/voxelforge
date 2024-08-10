Make sure to have the build/ in PYTHONPATH:

```bash
export PYTHONPATH=$PYTHONPATH:/home/andrew/voxelforge/build
```

To re-run with changes: 

```bash
# Clean the build directory
rm -rf build/

# Recreate the build directory and configure the project
mkdir build
cd build
cmake ..

# Build the project
make

# Reinstall the package
cd ..
pip install .
```