#include "voxel.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


namespace py = pybind11;

Voxel::Voxel(int x, int y, int z) : x(x), y(y), z(z) {}

VoxelGrid::VoxelGrid() {}

void VoxelGrid::addVoxel(int x, int y, int z) {
    voxels.emplace_back(x, y, z);
}

PYBIND11_MODULE(voxelforge, m) {
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
        });
}

