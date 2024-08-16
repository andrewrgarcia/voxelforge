Usage
=====

Basic Voxel Operations
----------------------

To start using **VoxelForge**, import the package and create a `VoxelGrid` instance:

.. code-block:: python

    import voxelforge as vf

    # Create a VoxelGrid and add voxels
    grid = vf.VoxelGrid()
    grid.addVoxel(1, 2, 3)
    grid.addVoxel(4, 5, 6, "String identity")
    grid.addVoxel(7, 8, 9, {"key": "value"})

    voxels = grid.getVoxels()
    for voxel in voxels:
        print(f'Voxel at ({voxel.x}, {voxel.y}, {voxel.z}) with data {voxel.data}')

Advanced Graph Features
-----------------------

**VoxelForge** also supports transforming voxel data into graph structures, useful for graph-based machine learning models:

.. code-block:: python

    graph_data = grid.toTorchGraph(xDim=10, yDim=10, zDim=10, neighboring_radius=1.0)
    print("Node Features:", graph_data['x'])
    print("Edge Index:", graph_data['edge_index'])
