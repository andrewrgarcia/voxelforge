#include "voxel.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

Voxel::Voxel(int x, int y, int z) : x(x), y(y), z(z) {}

VoxelGrid::VoxelGrid() {}

void VoxelGrid::addVoxel(int x, int y, int z) {
    voxels.emplace_back(x, y, z);
}

std::vector<std::pair<int, int>> VoxelGrid::toGraph(int xDim, int yDim, int zDim) {
    std::unordered_map<int, std::vector<int>> adjList;
    std::vector<std::pair<int, int>> edges;

    for (const auto& voxel : voxels) {
        int index = voxel.x * yDim * zDim + voxel.y * zDim + voxel.z;
        std::vector<std::tuple<int, int, int>> neighbors = {
            {voxel.x + 1, voxel.y, voxel.z}, {voxel.x - 1, voxel.y, voxel.z},
            {voxel.x, voxel.y + 1, voxel.z}, {voxel.x, voxel.y - 1, voxel.z},
            {voxel.x, voxel.y, voxel.z + 1}, {voxel.x, voxel.y, voxel.z - 1}
        };

        for (const auto& [nx, ny, nz] : neighbors) {
            if (0 <= nx && nx < xDim && 0 <= ny && ny < yDim && 0 <= nz && nz < zDim) {
                int neighborIndex = nx * yDim * zDim + ny * zDim + nz;
                adjList[index].push_back(neighborIndex);
            }
        }
    }

    for (const auto& [key, neighbors] : adjList) {
        for (int neighbor : neighbors) {
            edges.emplace_back(key, neighbor);
        }
    }

    return edges;
}

PYBIND11_MODULE(voxelforge_cpp, m) {
    py::class_<Voxel>(m, "Voxel")
        .def(py::init<int, int, int>())
        .def_readwrite("x", &Voxel::x)
        .def_readwrite("y", &Voxel::y)
        .def_readwrite("z", &Voxel::z);

    py::class_<VoxelGrid>(m, "VoxelGrid")
        .def(py::init<>())
        .def("addVoxel", &VoxelGrid::addVoxel)
        .def("getVoxels", [](const VoxelGrid &grid) {
            return grid.voxels;
        })
        .def("toGraph", &VoxelGrid::toGraph);
}
