#include "octree.h"
#include <iostream>

// OctreeLeafNode Implementation
OctreeLeafNode::OctreeLeafNode(const Eigen::Vector3d& point) : point_(point) {}

bool OctreeLeafNode::IsLeaf() const {
    return true;
}

const Eigen::Vector3d& OctreeLeafNode::GetPoint() const {
    return point_;
}

// OctreeInternalNode Implementation
OctreeInternalNode::OctreeInternalNode() : children_(8, nullptr) {}

bool OctreeInternalNode::IsLeaf() const {
    return false;
}

void OctreeInternalNode::AddChild(size_t index, std::shared_ptr<OctreeNode> child) {
    if (index < 8) {
        children_[index] = child;
    } else {
        throw std::out_of_range("Child index out of bounds.");
    }
}

std::shared_ptr<OctreeNode> OctreeInternalNode::GetChild(size_t index) const {
    if (index < 8) {
        return children_[index];
    } else {
        return nullptr;
    }
}

// Octree Implementation
Octree::Octree(const Eigen::Vector3d& origin, double size, size_t max_depth)
    : origin_(origin), size_(size), max_depth_(max_depth) {
    root_node_ = std::make_shared<OctreeInternalNode>();
}

Octree::~Octree() {
    // Cleanup if necessary
}

void Octree::InsertPoint(const Eigen::Vector3d& point) {
    InsertPointRecurse(root_node_, point, origin_, size_, 0);
}

std::shared_ptr<OctreeLeafNode> Octree::LocateLeafNode(const Eigen::Vector3d& point) const {
    std::shared_ptr<OctreeNode> current_node = root_node_;
    Eigen::Vector3d current_origin = origin_;
    double current_size = size_;

    for (size_t depth = 0; depth < max_depth_; ++depth) {
        auto internal_node = std::dynamic_pointer_cast<OctreeInternalNode>(current_node);
        if (!internal_node) {
            return nullptr;  // We reached a leaf without finding the point
        }

        double child_size = current_size / 2.0;
        size_t x_index = point(0) < current_origin(0) + child_size ? 0 : 1;
        size_t y_index = point(1) < current_origin(1) + child_size ? 0 : 1;
        size_t z_index = point(2) < current_origin(2) + child_size ? 0 : 1;
        size_t child_index = x_index + y_index * 2 + z_index * 4;

        current_node = internal_node->GetChild(child_index);
        current_origin = current_origin + Eigen::Vector3d(x_index * child_size,
                                                          y_index * child_size,
                                                          z_index * child_size);
        current_size = child_size;
    }

    return std::dynamic_pointer_cast<OctreeLeafNode>(current_node);
}

void Octree::InsertPointRecurse(const std::shared_ptr<OctreeNode>& node,
                                const Eigen::Vector3d& point,
                                const Eigen::Vector3d& origin,
                                double size, size_t depth) {
    if (depth == max_depth_) {
        auto leaf_node = std::dynamic_pointer_cast<OctreeLeafNode>(node);
        if (!leaf_node) {
            leaf_node = std::make_shared<OctreeLeafNode>(point);
        }
        return;
    }

    auto internal_node = std::dynamic_pointer_cast<OctreeInternalNode>(node);
    if (!internal_node) {
        throw std::runtime_error("Expected an internal node.");
    }

    double child_size = size / 2.0;
    size_t x_index = point(0) < origin(0) + child_size ? 0 : 1;
    size_t y_index = point(1) < origin(1) + child_size ? 0 : 1;
    size_t z_index = point(2) < origin(2) + child_size ? 0 : 1;
    size_t child_index = x_index + y_index * 2 + z_index * 4;

    Eigen::Vector3d child_origin = origin + Eigen::Vector3d(x_index * child_size,
                                                            y_index * child_size,
                                                            z_index * child_size);

    if (!internal_node->GetChild(child_index)) {
        if (depth == max_depth_ - 1) {
            internal_node->AddChild(child_index, std::make_shared<OctreeLeafNode>(point));
        } else {
            internal_node->AddChild(child_index, std::make_shared<OctreeInternalNode>());
        }
    }

    InsertPointRecurse(internal_node->GetChild(child_index), point, child_origin, child_size, depth + 1);
}
