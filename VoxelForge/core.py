import torch
from voxelforge_cpp import Voxel, VoxelGrid, Octree, OctreeNode, OctreeLeafNode, OctreeInternalNode

class VoxelGridWrapper(VoxelGrid):
    def __init__(self):
        super().__init__()

    def toTorch(self, xDim, yDim, zDim):
        tensor = torch.zeros((xDim, yDim, zDim), dtype=torch.int32)
        voxels = self.getVoxels()

        for voxel in voxels:
            if 0 <= voxel.x < xDim and 0 <= voxel.y < yDim and 0 <= voxel.z < zDim:
                tensor[voxel.x, voxel.y, voxel.z] = 1

        return tensor

    def toTorchGraph(self, xDim, yDim, zDim, neighboring_radius=1.0):
        # Call the C++ toGraph function
        node_features, edge_index = self.toGraph(xDim, yDim, zDim, neighboring_radius)

        # Convert the node features to a torch tensor
        x = torch.tensor(node_features, dtype=torch.float)

        # Convert the edge index to a torch tensor and transpose to get shape [2, num_edges]
        edge_index = torch.tensor(edge_index, dtype=torch.long).t().contiguous()

        # Return a dictionary with the necessary components for a torch_geometric Data object
        return {'x': x, 'edge_index': edge_index}
