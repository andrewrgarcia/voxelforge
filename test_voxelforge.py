import VoxelForge as vff
import numpy as np

# Test the Voxel class
print("Testing Voxel class:")
voxel_instance = vff.Voxel(1, 2, 3)
print(f"Voxel created at ({voxel_instance.x}, {voxel_instance.y}, {voxel_instance.z})")

# Test the VoxelGrid class
print("\nTesting VoxelGrid class:")
grid = vff.VoxelGrid()
grid.addVoxel(4, 5, 6)
grid.addVoxel(7, 8, 9)
voxels = grid.getVoxels()

for v in voxels:
    print(f"Voxel at ({v.x}, {v.y}, {v.z})")

# Test Graph conversion
print("\nTesting Graph conversion:")
edges = grid.toGraph(10, 10, 10)
print(edges)

# Test Tensor conversion using VoxelGrid (voxelforge)
print("\nTesting Tensor conversion:")
tensor = grid.toTorch(200, 200, 200)
print(tensor)
