import VoxelForge as vff
import numpy as np
import json

# Test the Voxel class
print("Testing Voxel class:")
voxel_instance = vff.Voxel(1, 2, 3)
print(f"Voxel created at ({voxel_instance.x}, {voxel_instance.y}, {voxel_instance.z})")

# Test the VoxelGrid class
print("\nTesting VoxelGrid class:")
grid = vff.VoxelGrid()
grid.addVoxel(1, 2, 3)
grid.addVoxel(1, 1, 3)
grid.addVoxel(4, 5, 6)
grid.addVoxel(7, 8, 9)
voxels = grid.getVoxels()

for v in voxels:
    print(f"Voxel at ({v.x}, {v.y}, {v.z})")

print("\nTesting List conversion:")
voxel_list = grid.toList()
print(voxel_list)  # Output: [(1, 2, 3), (4, 5, 6), (7, 8, 9)]


print("\nTesting Graph conversion:")
# Call the toGraph method (C++ method) to get raw data
node_features, edge_index = grid.toGraph(9, 9, 9, 10)

# The raw node features and edge index from the C++ side
print("Raw Node Features:", node_features)
print("Raw Edge Index:", edge_index)


# Get the components for a torch_geometric Data object
graph_data_dict = grid.toTorchGraph(9, 9, 9, 10.0)
print('Inputs to torch.geometric Data:', graph_data_dict)

# # If the user has torch_geometric installed, they can easily create a Data object
# from torch_geometric.data import Data

# graph_data = Data(x=graph_data_dict['x'], edge_index=graph_data_dict['edge_index'])

# # graph_data is now a Data object ready for use in PyTorch Geometric
# print(graph_data)




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

# # Get JSON representation
# print("\nJSON representation:")
# json_string = octree.to_json(2)
# print(json_string)

# # Convert the JSON string to a Python dictionary
# json_dict = json.loads(json_string)

# # Access the JSON data as a dictionary
# print(json_dict)


# Test Torch.Tensor conversion using VoxelGrid (voxelforge)
print("\nTesting Torch.Tensor conversion:")
tensor = grid.toTorch(9, 9, 9)
print(tensor)
