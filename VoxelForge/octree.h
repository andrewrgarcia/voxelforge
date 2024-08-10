#ifndef VOXELFORGE_OCTREE_H
#define VOXELFORGE_OCTREE_H

#include <Eigen/Dense>
#include <memory>
#include <vector>
#include <string> // For JSON and bit-string representations

class OctreeNode {
public:
    virtual bool IsLeaf() const = 0;
    virtual std::string ToJson(int indent = 0) const = 0;  // Pure virtual for ToJson
    virtual ~OctreeNode() = default;
};

class OctreeLeafNode : public OctreeNode {
public:
    OctreeLeafNode(const Eigen::Vector3d& point);
    bool IsLeaf() const override;
    const Eigen::Vector3d& GetPoint() const;
    std::string ToJson(int indent = 0) const override;

private:
    Eigen::Vector3d point_;
};

class OctreeInternalNode : public OctreeNode {
public:
    OctreeInternalNode();
    bool IsLeaf() const override { return false; }
    std::shared_ptr<OctreeNode> GetChild(size_t index) const;
    const std::vector<std::shared_ptr<OctreeNode>>& GetChildren() const;
    size_t GetChildIndex(const Eigen::Vector3d& point, const Eigen::Vector3d& origin, double size) const;
    void SetChild(size_t index, std::shared_ptr<OctreeNode> child);

    // Bit-string and JSON representation methods
    std::string ToBitString() const;
    std::string ToJson(int indent = 0) const override;

private:
    std::vector<std::shared_ptr<OctreeNode>> children_;
};

class Octree {
public:
    Octree(const Eigen::Vector3d& origin, double size, size_t max_depth);
    void InsertPoint(const Eigen::Vector3d& point);
    std::shared_ptr<OctreeLeafNode> LocateLeafNode(const Eigen::Vector3d& point) const;

    // Methods to get bit-string and JSON representations
    std::string ToBitString() const;
    std::string ToJson(int indent = 0) const;

private:
    void InsertPointRecurse(const std::shared_ptr<OctreeNode>& node,
                            const Eigen::Vector3d& point,
                            const Eigen::Vector3d& origin,
                            double size, size_t depth);
    std::string ToBitStringRecurse(const std::shared_ptr<OctreeNode>& node) const;

    Eigen::Vector3d origin_;
    double size_;
    size_t max_depth_;
    std::shared_ptr<OctreeNode> root_;
};

#endif // VOXELFORGE_OCTREE_H
