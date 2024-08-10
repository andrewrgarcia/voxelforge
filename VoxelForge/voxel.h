#ifndef VOXELFORGE_VOXEL_H
#define VOXELFORGE_VOXEL_H

#include <vector>
#include <Eigen/Dense>

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
    std::vector<std::pair<int, int>> toGraph(int xDim, int yDim, int zDim);
};

#endif
