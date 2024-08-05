#ifndef VOXEL_H
#define VOXEL_H

#include <vector>
#include <utility>
#include <torch/torch.h>

class Voxel {
public:
    int x, y, z;
    Voxel(int x, int y, int z);
};

class VoxelGrid {
public:
    std::vector<Voxel> voxels;
    VoxelGrid();
    void addVoxel(int x, int y, int z);
    torch::Tensor toTorch(int xDim, int yDim, int zDim);
    std::vector<std::pair<int, int>> toGraph(int xDim, int yDim, int zDim);
};

#endif
