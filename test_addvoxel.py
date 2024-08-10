import numpy as np
import VoxelForge as vff
import torch
import time

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
