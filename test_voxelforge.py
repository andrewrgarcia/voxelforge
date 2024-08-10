import VoxelForge as vff
import numpy as np

# Test the Voxel class
print("Testing Voxel class:")
voxel_instance = vff.Voxel(1, 2, 3)
print(f"Voxel created at ({voxel_instance.x}, {voxel_instance.y}, {voxel_instance.z})")

# Test the VoxelGrid class
print("\nTesting VoxelGrid class:")
grid = vff.VoxelGrid()
grid.addVoxel(4, 5, 6)
grid.addVoxel(7, 8, 9)
voxels = grid.getVoxels()

for v in voxels:
    print(f"Voxel at ({v.x}, {v.y}, {v.z})")

# Test Graph conversion
print("\nTesting Graph conversion:")
edges = grid.toGraph(10, 10, 10)
print(edges)

# Test Tensor conversion using VoxelGrid (voxelforge)
print("\nTesting Tensor conversion:")
tensor = grid.toTorch(200, 200, 200)
print(tensor)

# Test Octree functionality
print("\nTesting Octree class:")
origin = np.array([0.0, 0.0, 0.0])
size = 10.0
max_depth = 3
octree = vff.Octree(origin, size, max_depth)

# Insert points into the octree
points = [
    np.array([1.0, 1.0, 1.0]),
    np.array([3.0, 3.0, 3.0]),
    np.array([7.0, 7.0, 7.0])
]

for point in points:
    octree.insert_point(point)

# Locate a leaf node
leaf_node = octree.locate_leaf_node(np.array([1.0, 1.0, 1.0]))
if leaf_node:
    print(f"Leaf node found at {leaf_node.get_point()}")
else:
    print("Leaf node not found.")

# Testing insertion of a point and locating it in the octree
new_point = np.array([2.0, 2.0, 2.0])
octree.insert_point(new_point)
found_leaf = octree.locate_leaf_node(new_point)

if found_leaf:
    print(f"Inserted point found at {found_leaf.get_point()}")
else:
    print("Inserted point not found.")

# Test edge cases: locate a point not in the octree
missing_point = np.array([20.0, 20.0, 20.0])
missing_leaf = octree.locate_leaf_node(missing_point)

if missing_leaf:
    print(f"Unexpectedly found a node at {missing_leaf.get_point()}")
else:
    print("Correctly did not find a node for the missing point.")


# Get bit-string representation
bit_string = octree.to_bit_string()
print("Bit-string representation:")
print(bit_string)

# Get JSON representation
json_string = octree.to_json(indent=2)
print("\nJSON representation:")
print(json_string)