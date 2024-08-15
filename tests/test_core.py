import unittest
import torch
from VoxelForge import VoxelGrid

class TestVoxelGrid(unittest.TestCase):
    def test_add_voxel(self):
        grid = VoxelGrid()  # Use the wrapper class to access the new methods
        grid.addVoxel(1, 2, 3)
        voxels = grid.getVoxels()
        self.assertEqual(len(voxels), 1)
        self.assertEqual(voxels[0].x, 1)
        self.assertEqual(voxels[0].y, 2)
        self.assertEqual(voxels[0].z, 3)

    def test_tensor_conversion(self):
        grid = VoxelGrid()
        grid.addVoxel(1, 2, 3)
        tensor = grid.toTorch(10, 10, 10)
        self.assertEqual(tensor[1, 2, 3].item(), 1)
        self.assertEqual(tensor.sum().item(), 1)  # Check if only one voxel is set to 1

    def test_graph_conversion(self):
        grid = VoxelGrid()
        grid.addVoxel(1, 2, 3)
        grid.addVoxel(1, 2, 4)
        # Call the toTorchGraph to get the graph data as a dictionary
        graph_data = grid.toTorchGraph(10, 10, 10, 1.0)

        # Check if the node features are correct
        x = graph_data['x']
        self.assertTrue(torch.equal(x, torch.tensor([[1, 2, 3], [1, 2, 4]], dtype=torch.float)))

        # Check if the edge index contains the expected connection
        edge_index = graph_data['edge_index']
        self.assertTrue(torch.equal(edge_index, torch.tensor([[0, 1], [1, 0]], dtype=torch.long)))


if __name__ == '__main__':
    unittest.main()
