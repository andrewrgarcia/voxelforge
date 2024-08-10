#ifndef VOXELFORGE_OCTREE_H
#define VOXELFORGE_OCTREE_H

#include <Eigen/Dense>
#include <memory>
#include <vector>

class OctreeNode {
public:
    virtual bool IsLeaf() const = 0;
    virtual ~OctreeNode() = default;
};

class OctreeLeafNode : public OctreeNode {
public:
    OctreeLeafNode(const Eigen::Vector3d& point);
    bool IsLeaf() const override;
    const Eigen::Vector3d& GetPoint() const;

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

private:
    std::vector<std::shared_ptr<OctreeNode>> children_;
};

class Octree {
public:
    Octree(const Eigen::Vector3d& origin, double size, size_t max_depth);
    void InsertPoint(const Eigen::Vector3d& point);
    std::shared_ptr<OctreeLeafNode> LocateLeafNode(const Eigen::Vector3d& point) const;

private:
    void InsertPointRecurse(const std::shared_ptr<OctreeNode>& node,
                            const Eigen::Vector3d& point,
                            const Eigen::Vector3d& origin,
                            double size, size_t depth);
    Eigen::Vector3d origin_;
    double size_;
    size_t max_depth_;
    std::shared_ptr<OctreeNode> root_;
};

#endif // VOXELFORGE_OCTREE_H
