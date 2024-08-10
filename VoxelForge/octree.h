#pragma once

#include <vector>
#include <memory>
#include <Eigen/Dense>

// Base class for Octree nodes
class OctreeNode {
public:
    virtual ~OctreeNode() = default;  // Ensure virtual destructor is defined
    virtual bool IsLeaf() const = 0;
};

// Octree leaf node class
class OctreeLeafNode : public OctreeNode {
public:
    OctreeLeafNode(const Eigen::Vector3d& point);
    bool IsLeaf() const override;
    const Eigen::Vector3d& GetPoint() const;

    ~OctreeLeafNode() override = default;  // Ensure this is virtual
private:
    Eigen::Vector3d point_;
};


// Octree internal node class
class OctreeInternalNode : public OctreeNode {
public:
    OctreeInternalNode();
    bool IsLeaf() const override;
    void AddChild(size_t index, std::shared_ptr<OctreeNode> child);
    std::shared_ptr<OctreeNode> GetChild(size_t index) const;
    const std::vector<std::shared_ptr<OctreeNode>>& GetChildren() const;
    size_t GetChildIndex(const Eigen::Vector3d& point, const Eigen::Vector3d& origin, double size) const;

private:
    std::vector<std::shared_ptr<OctreeNode>> children_;
};

// Octree class
class Octree {
public:
    Octree(const Eigen::Vector3d& origin, double size, size_t max_depth);
    ~Octree();

    void InsertPoint(const Eigen::Vector3d& point);
    std::shared_ptr<OctreeLeafNode> LocateLeafNode(const Eigen::Vector3d& point) const;

private:
    void InsertPointRecurse(const std::shared_ptr<OctreeNode>& node,
                            const Eigen::Vector3d& point,
                            const Eigen::Vector3d& origin,
                            double size, size_t depth);

    std::shared_ptr<OctreeNode> root_node_;
    Eigen::Vector3d origin_;
    double size_;
    size_t max_depth_;
};
