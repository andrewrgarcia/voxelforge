
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
