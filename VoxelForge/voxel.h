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
    std::vector<std::tuple<int, int, int>> toList() const;
    std::pair<std::vector<std::vector<float>>, std::vector<std::pair<int, int>>>
    toGraph(int xDim, int yDim, int zDim, float neighboring_radius = 1.0);
};

#endif
