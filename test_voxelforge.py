import VoxelForge as vff
import torch
import time

# Test the Voxel class
print("Testing Voxel class:")
voxel_instance = vff.Voxel(1, 2, 3)
print(f"Voxel created at ({voxel_instance.x}, {voxel_instance.y}, {voxel_instance.z})")

# Test the VoxelGrid class
print("\nTesting VoxelGrid class:")
grid = vff.VoxelGrid()
grid.addVoxel(4, 5, 6)
grid.addVoxel(7, 8, 9)
grid.addVoxel(150, 2, 185)

voxels = grid.getVoxels()

for v in voxels:
    print(f"Voxel at ({v.x}, {v.y}, {v.z})")

# Test Graph conversion
print("\nTesting Graph conversion:")
edges = grid.toGraph(10, 10, 10)
print(edges)

import numpy as np

# Test Tensor conversion using VoxelGrid (voxelforge)
print("\nTesting Tensor conversion with VoxelForge:")
start_time_voxelforge = time.time()
grid = vff.VoxelGrid()
for _ in range(100000):
    grid.addVoxel(*np.random.randint(0,150,3)) 
tensor_voxelforge = grid.toTorch(200, 200, 200)
end_time_voxelforge = time.time() - start_time_voxelforge
print(f"Tensor conversion with VoxelForge took {end_time_voxelforge:.6f} seconds")

# Test Tensor creation natively with PyTorch
print("\nTesting native Tensor creation with PyTorch:")
start_time_torch = time.time()
tensor_torch = torch.zeros((200, 200, 200), dtype=torch.int32)
for _ in range(100000):
    tensor_torch[tuple(np.random.randint(0,150,3))] = 1
end_time_torch = time.time() - start_time_torch
print(f"Native Tensor creation with PyTorch took {end_time_torch:.6f} seconds")

# Optional: Uncomment this to see the tensors (comment out for large tensors)
# print("\nVoxelForge Tensor:")
# print(tensor_voxelforge)
# print("\nPyTorch Tensor:")
# print(tensor_torch)

# Comparison result
print(f"\nVoxelForge is {'faster' if end_time_voxelforge < end_time_torch else 'slower'} than native PyTorch by {abs(end_time_voxelforge - end_time_torch):.6f} seconds.")
