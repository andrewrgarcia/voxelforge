import torch
from voxelforge_cpp import Voxel, VoxelGrid  # Ensure the correct C++ module name is used


class VoxelGridWrapper(VoxelGrid):
    def toTorch(self, xDim, yDim, zDim):
        tensor = torch.zeros((xDim, yDim, zDim), dtype=torch.int32)
        voxels = self.getVoxels()

        for voxel in voxels:
            if 0 <= voxel.x < xDim and 0 <= voxel.y < yDim and 0 <= voxel.z < zDim:
                tensor[voxel.x, voxel.y, voxel.z] = 1

        return tensor

    def toGraph(self, xDim, yDim, zDim):
        return super().toGraph(xDim, yDim, zDim)
