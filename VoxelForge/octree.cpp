#include "octree.h"
#include <stdexcept>
#include <sstream> // For JSON and bit-string methods

OctreeLeafNode::OctreeLeafNode(const Eigen::Vector3d& point) : point_(point) {}

bool OctreeLeafNode::IsLeaf() const {
    return true;
}

const Eigen::Vector3d& OctreeLeafNode::GetPoint() const {
    return point_;
}

std::string OctreeLeafNode::ToJson(int indent) const {
    std::ostringstream oss;
    std::string indentation(indent, ' ');
    oss << indentation << "{\n";
    oss << indentation << "  \"type\": \"leaf\",\n";
    oss << indentation << "  \"point\": [" << point_.transpose() << "]\n";
    oss << indentation << "}";
    return oss.str();
}

OctreeInternalNode::OctreeInternalNode() : children_(8, nullptr) {}

std::shared_ptr<OctreeNode> OctreeInternalNode::GetChild(size_t index) const {
    return children_.at(index);
}

void OctreeInternalNode::SetChild(size_t index, std::shared_ptr<OctreeNode> child) {
    children_.at(index) = std::move(child);
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

std::string Octree::ToBitString() const {
    return ToBitStringRecurse(root_);
}

std::string Octree::ToBitStringRecurse(const std::shared_ptr<OctreeNode>& node) const {
    if (!node) return "0";

    auto internal_node = std::dynamic_pointer_cast<OctreeInternalNode>(node);
    if (internal_node) {
        std::string bitstring = "0"; // Internal node
        for (const auto& child : internal_node->GetChildren()) {
            bitstring += ToBitStringRecurse(child);
        }
        return bitstring;
    } else {
        return "1"; // Leaf node
    }
}

std::string OctreeInternalNode::ToJson(int indent) const {
    std::ostringstream oss;
    std::string indentation(indent, ' ');

    oss << indentation << "{\n";
    oss << indentation << "  \"type\": \"internal\",\n";
    oss << indentation << "  \"children\": [\n";
    for (size_t i = 0; i < 8; ++i) {
        auto child = GetChild(i);
        if (child) {
            oss << child->ToJson(indent + 4); // Use the child's ToJson method
        } else {
            oss << indentation + "    null";
        }
        if (i < 7) oss << ",";
        oss << "\n";
    }
    oss << indentation << "  ]\n";
    oss << indentation << "}";

    return oss.str();
}

Octree::Octree(const Eigen::Vector3d& origin, double size, size_t max_depth)
    : origin_(origin), size_(size), max_depth_(max_depth), root_(std::make_shared<OctreeInternalNode>()) {}

void Octree::InsertPoint(const Eigen::Vector3d& point) {
    InsertPointRecurse(root_, point, origin_, size_, 0);
}

std::shared_ptr<OctreeLeafNode> Octree::LocateLeafNode(const Eigen::Vector3d& point) const {
    std::shared_ptr<OctreeNode> current_node = root_;
    Eigen::Vector3d current_origin = origin_;
    double current_size = size_;

    while (current_node && !current_node->IsLeaf()) {
        auto internal_node = std::dynamic_pointer_cast<OctreeInternalNode>(current_node);
        if (!internal_node) {
            return nullptr;  // Not a leaf and not an internal node
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
    // Check if the node is a leaf node first
    if (node->IsLeaf()) {
        throw std::runtime_error("Expected an internal node.");
    }

    auto internal_node = std::dynamic_pointer_cast<OctreeInternalNode>(node);
    if (!internal_node) {
        throw std::runtime_error("Failed to cast to internal node.");
    }

    size_t child_index = internal_node->GetChildIndex(point, origin, size);
    Eigen::Vector3d child_origin = origin + Eigen::Vector3d(child_index % 2 * size / 2,
                                                            (child_index / 2) % 2 * size / 2,
                                                            (child_index / 4) % 2 * size / 2);

    if (!internal_node->GetChild(child_index)) {
        if (depth == max_depth_ - 1) {
            internal_node->SetChild(child_index, std::make_shared<OctreeLeafNode>(point));
            return;
        } else {
            internal_node->SetChild(child_index, std::make_shared<OctreeInternalNode>());
        }
    }

    // Recurse into the child node
    InsertPointRecurse(internal_node->GetChild(child_index), point, child_origin, size / 2, depth + 1);
}

std::string Octree::ToJson(int indent) const {
    return root_ ? root_->ToJson(indent) : "{}"; // Use the root's ToJson method
}
