#include "voxel.h"
#include "octree.h"
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
    // Existing bindings
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

    // Octree bindings
    py::class_<OctreeNode, std::shared_ptr<OctreeNode>>(m, "OctreeNode")
        .def("is_leaf", &OctreeNode::IsLeaf);

    py::class_<OctreeLeafNode, OctreeNode, std::shared_ptr<OctreeLeafNode>>(m, "OctreeLeafNode")
        .def(py::init<const Eigen::Vector3d&>())
        .def("get_point", &OctreeLeafNode::GetPoint);

    py::class_<OctreeInternalNode, OctreeNode, std::shared_ptr<OctreeInternalNode>>(m, "OctreeInternalNode")
        .def(py::init<>())
        .def("get_child", &OctreeInternalNode::GetChild);

    py::class_<Octree, std::shared_ptr<Octree>>(m, "Octree")
        .def(py::init<const Eigen::Vector3d&, double, size_t>())
        .def("insert_point", &Octree::InsertPoint)
        .def("locate_leaf_node", &Octree::LocateLeafNode);
}
