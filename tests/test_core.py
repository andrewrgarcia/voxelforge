import unittest
from VoxelForge import voxel

class TestVoxelGrid(unittest.TestCase):
    def test_add_voxel(self):
        grid = voxel.VoxelGrid()
        grid.addVoxel(1, 2, 3)
        voxels = grid.getVoxels()
        self.assertEqual(len(voxels), 1)
        self.assertEqual(voxels[0].x, 1)
        self.assertEqual(voxels[0].y, 2)
        self.assertEqual(voxels[0].z, 3)

if __name__ == '__main__':
    unittest.main()

