# Import the VoxelForge package
import voxelforge as vf

# Create a new VoxelGrid instance
grid = vf.VoxelGrid()

# Add several voxels with default and custom identities
grid.addVoxel(1, 2, 3)  # Default identity (integer)
grid.addVoxel(4, 5, 6, "Colorful Voxel")  # String identity
grid.addVoxel(7, 8, 9, {"key": "value"})  # Dictionary identity
grid.addVoxel(10, 11, 12, 3.14159)  # Floating-point identity

# Print out the voxel information
voxels = grid.getVoxels()
for voxel in voxels:
    print(f'Voxel at ({voxel.x}, {voxel.y}, {voxel.z}) with data: {voxel.data}')
