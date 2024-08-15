#pragma once

#include <vector>
#include <Eigen/Dense>
#include <tuple>
#include <pybind11/pybind11.h>

class Voxel {
public:
    int x, y, z;
    pybind11::object data;

    Voxel(int x, int y, int z, pybind11::object data = pybind11::int_(1));

    pybind11::object getData() const;
    void setData(pybind11::object value);
};

class VoxelGrid {
public:
    std::vector<Voxel> voxels;

    VoxelGrid();

    void addVoxel(int x, int y, int z, pybind11::object data = pybind11::int_(1));
    std::vector<std::tuple<int, int, int>> toList() const;
    std::pair<std::vector<std::vector<float>>, std::vector<std::pair<int, int>>>
    toGraph(int xDim, int yDim, int zDim, float neighboring_radius = 1.0);

};
