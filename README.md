# VoxelForge

VoxelForge is a high-performance Python package written in C++ for efficient voxel and mesh model creation.

## Installation

```sh
python setup.py install
```

## Usage

```python
import voxelforge as vff

grid = vff.VoxelGrid()
grid.addVoxel(1, 2, 3)
grid.addVoxel(143, 25, 34)

voxels = grid.getVoxels()
for i, v in enumerate(voxels):
    print(f'Voxel {i+1} at ({v.x}, {v.y}, {v.z})')

# Output: 
# Voxel 1 at (1, 2, 3)
# Voxel 2 at (143, 25, 34)
```

## Testing

```sh
python -m unittest discover -s tests
```
