#include "octree.h"
#include <stdexcept>

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

const std::vector<std::shared_ptr<OctreeNode>>& OctreeInternalNode::GetChildren() const {
    return children_;
}

size_t OctreeInternalNode::GetChildIndex(const Eigen::Vector3d& point, const Eigen::Vector3d& origin, double size) const {
    size_t x_index = point(0) < origin(0) + size / 2 ? 0 : 1;
    size_t y_index = point(1) < origin(1) + size / 2 ? 0 : 1;
    size_t z_index = point(2) < origin(2) + size / 2 ? 0 : 1;
    return x_index + y_index * 2 + z_index * 4;
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

        size_t child_index = internal_node->GetChildIndex(point, current_origin, current_size);
        current_node = internal_node->GetChild(child_index);
        current_origin = current_origin + Eigen::Vector3d(child_index % 2 * current_size / 2,
                                                          (child_index / 2) % 2 * current_size / 2,
                                                          (child_index / 4) % 2 * current_size / 2);
        current_size /= 2.0;
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

    size_t child_index = internal_node->GetChildIndex(point, origin, size);
    Eigen::Vector3d child_origin = origin + Eigen::Vector3d(child_index % 2 * size / 2,
                                                            (child_index / 2) % 2 * size / 2,
                                                            (child_index / 4) % 2 * size / 2);

    if (!internal_node->GetChild(child_index)) {
        if (depth == max_depth_ - 1) {
            internal_node->AddChild(child_index, std::make_shared<OctreeLeafNode>(point));
        } else {
            internal_node->AddChild(child_index, std::make_shared<OctreeInternalNode>());
        }
    }

    InsertPointRecurse(internal_node->GetChild(child_index), point, child_origin, size / 2, depth + 1);
}
