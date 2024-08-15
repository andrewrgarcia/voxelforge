import VoxelForge as vff

# Initialize VoxelGrid
grid = vff.VoxelGrid()

grid.addVoxel(1, 2, 3, "Red Voxel")       # String Identity
grid.addVoxel(4, 5, 6, 42)                # Integer Identity
grid.addVoxel(7, 8, 9, 3.14)              # Float Identity
grid.addVoxel(1, 2, 4, {"key": "value"})  # Dictionary Identity

# Retrieval of VoxelGrid
for i, voxel in enumerate(grid.getVoxels()):
    print(f" Voxel {i} -- Coordinates: ({voxel.x}, {voxel.y}, {voxel.z}) -- Identity: {voxel.data} ")

# Modify the Identity of one voxel
grid.getVoxels()[0].setData("Updated Red Voxel")
print(f"\nUpdated Identity of Voxel 0: {grid.getVoxels()[0].getData()}")

# Add another voxel with a complex Identity type
grid.addVoxel(10, 11, 12, [1, 2, 3])  # List Identity

# Print all voxel data again to see the updates
print("\nUpdated Voxel List with New Voxel Added:")
for i, voxel in enumerate(grid.getVoxels()):
    print(f" Voxel {i} -- Coordinates: ({voxel.x}, {voxel.y}, {voxel.z}) -- Identity: {voxel.data} ")

