#include "voxel.h"
#include <unordered_map>  
#include <tuple>          
#include <cmath>

Voxel::Voxel(int x, int y, int z, pybind11::object data) : x(x), y(y), z(z), data(data) {}

pybind11::object Voxel::getData() const {
    return data;
}

void Voxel::setData(pybind11::object value) {
    data = value;
}


VoxelGrid::VoxelGrid() = default;

void VoxelGrid::addVoxel(int x, int y, int z, pybind11::object data) {
    voxels.emplace_back(x, y, z, data);
}

std::vector<std::tuple<int, int, int>> VoxelGrid::toList() const {
    std::vector<std::tuple<int, int, int>> voxel_list;
    for (const auto& voxel : voxels) {
        voxel_list.emplace_back(voxel.x, voxel.y, voxel.z);
    }
    return voxel_list;
}


// Declare because being called prior tu function def for clean code
std::vector<std::vector<float>> createNodeFeatures(const VoxelGrid& grid);
std::vector<std::pair<int, int>> createEdgeIndex(const VoxelGrid& grid, float neighboring_radius);
float calculateDistance(const Voxel& v1, const Voxel& v2);

std::pair<std::vector<std::vector<float>>, std::vector<std::pair<int, int>>>
VoxelGrid::toGraph(int xDim, int yDim, int zDim, float neighboring_radius) {
    auto node_features = createNodeFeatures(*this);
    auto edge_index = createEdgeIndex(*this, neighboring_radius);
    return std::make_pair(node_features, edge_index);
}

std::vector<std::vector<float>> createNodeFeatures(const VoxelGrid& grid) {
    std::vector<std::vector<float>> node_features;
    for (const auto& voxel : grid.voxels) {
        node_features.push_back({
            static_cast<float>(voxel.x),
            static_cast<float>(voxel.y),
            static_cast<float>(voxel.z)
        });
    }
    return node_features;
}

std::vector<std::pair<int, int>> createEdgeIndex(const VoxelGrid& grid, float neighboring_radius) {
    std::vector<std::pair<int, int>> edges;
    for (size_t i = 0; i < grid.voxels.size(); ++i) {
        const auto& voxel = grid.voxels[i];
        for (size_t j = 0; j < grid.voxels.size(); ++j) {
            if (i == j) continue; // Skip self-connection
            const auto& neighbor = grid.voxels[j];
            float distance = calculateDistance(voxel, neighbor);
            if (distance <= neighboring_radius) {
                edges.emplace_back(i, j); // Add edge from voxel i to voxel j
            }
        }
    }
    return edges;
}

float calculateDistance(const Voxel& v1, const Voxel& v2) {
    return std::sqrt(
        std::pow(v1.x - v2.x, 2) +
        std::pow(v1.y - v2.y, 2) +
        std::pow(v1.z - v2.z, 2)
    );
}
