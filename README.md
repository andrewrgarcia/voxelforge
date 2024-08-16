![](img/banner.png)

VoxelForge is a high-performance Python package written in C++ for creating and manipulating voxel models with advanced spatial data structures like octrees and graph representations. Designed to facilitate integration with machine learning and deep learning workflows, VoxelForge is ideal for applications that require complex spatial data processing and analysis.

## Key Features

- Efficient voxel manipulation and storage using C++.
- Spatial indexing with octree structures for fast query performance.
- Integration of voxel data into graph structures for advanced modeling and analysis.
- Flexible data identity for voxels, supporting simple integers by default or complex data types like strings and dictionaries.


## Installation

Install VoxelForge easily using pip:

```sh
pip install VoxelForge
```


## Building from Source

If you prefer to build VoxelForge from source, detailed instructions are available in the [BUILD.md](BUILD.md) file.

In summary, you'll need to:

1. Clean the build directory.
2. Configure the project using CMake.
3. Build the project with `make`.
4. Reinstall the package locally using `pip install .`.

For complete step-by-step instructions, please refer to the [BUILD.md](BUILD.md) file.


## Usage

### Basic Voxel Operations

```python
import voxelforge as vf

# Create a new VoxelGrid and add a voxel with default identity
grid = vf.VoxelGrid()
grid.addVoxel(1, 2, 3)  # Adds a voxel with default identity 1

# Retrieve and display voxel information
voxels = grid.getVoxels()
for voxel in voxels:
    print(f'Voxel at ({voxel.x}, {voxel.y}, {voxel.z})')
```

### Handling Various Data Identities

```python
# Create another VoxelGrid for handling different identities
advanced_grid = vf.VoxelGrid()
advanced_grid.addVoxel(6, 6, 6, "Santa")
advanced_grid.addVoxel(7, 8, 9, {"color": "#001230", "alpha": 0.12, "gravity": 0.81  })

# Retrieve and display voxel information with identities
advanced_voxels = advanced_grid.getVoxels()
for voxel in advanced_voxels:
    print(f'Voxel at ({voxel.x}, {voxel.y}, {voxel.z}) with data {voxel.data}')
```

### Advanced Graph Features

```python
# Convert VoxelGrid to a graph structure with specified dimensions and neighboring radius
graph_data = advanced_grid.toTorchGraph(xDim=10, yDim=10, zDim=10, neighboring_radius=1.0)

# Access node features and edge indexes from the graph
print("Node Features:", graph_data['x'])
print("Edge Index:", graph_data['edge_index'])
```

### Using Octree for Spatial Indexing

```python
# Initialize an Octree with a specific size and depth
octree = vf.Octree(origin=np.array([0.0, 0.0, 0.0]), size=10.0, max_depth=3)

# Insert points and locate leaf nodes
octree.insert_point(np.array([1.0, 1.0, 1.0]))
leaf_node = octree.locate_leaf_node(np.array([1.0, 1.0, 1.0]))

if leaf_node:
    print(f"Leaf node found at {leaf_node.get_point()}")
```
