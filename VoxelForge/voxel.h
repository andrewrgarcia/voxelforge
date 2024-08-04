#ifndef VOXEL_H
#define VOXEL_H

#include <vector>

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
};

#endif

