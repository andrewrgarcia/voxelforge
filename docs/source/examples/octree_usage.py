# Import the VoxelForge package and numpy for handling coordinates
import voxelforge as vf
import numpy as np

# Initialize an Octree with a specific origin, size, and maximum depth
origin = np.array([0.0, 0.0, 0.0])
size = 50.0
max_depth = 4
octree = vf.Octree(origin, size, max_depth)

# Insert points into the Octree
points = [
    np.array([5.0, 5.0, 5.0]),
    np.array([15.0, 15.0, 15.0]),
    np.array([35.0, 35.0, 35.0]),
    np.array([45.0, 45.0, 45.0])
]

for point in points:
    octree.insert_point(point)

# Locate a specific point and print its information
target_point = np.array([5.0, 5.0, 5.0])
leaf_node = octree.locate_leaf_node(target_point)
if leaf_node:
    print(f"Leaf node found at {leaf_node.get_point()}")
else:
    print("No leaf node found at the specified location.")
