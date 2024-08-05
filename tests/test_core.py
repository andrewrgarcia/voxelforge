import unittest
from VoxelForge import Voxel, VoxelGrid

class TestVoxelGrid(unittest.TestCase):
    def test_add_voxel(self):
        grid = VoxelGrid()
        grid.addVoxel(1, 2, 3)
        voxels = grid.getVoxels()
        self.assertEqual(len(voxels), 1)
        self.assertEqual(voxels[0].x, 1)
        self.assertEqual(voxels[0].y, 2)
        self.assertEqual(voxels[0].z, 3)

    def test_tensor_conversion(self):
        grid = VoxelGrid()
        grid.addVoxel(1, 2, 3)
        tensor = grid.toTensor(10, 10, 10)
        self.assertEqual(tensor[1, 2, 3].item(), 1)

    def test_graph_conversion(self):
        grid = VoxelGrid()
        grid.addVoxel(1, 2, 3)
        grid.addVoxel(1, 2, 4)
        edges = grid.toGraph(10, 10, 10)
        self.assertIn((132, 133), edges)

if __name__ == '__main__':
    unittest.main()
