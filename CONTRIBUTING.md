# Contributing to VoxelForge

We are thrilled that you are interested in contributing to **VoxelForge**! Contributions of all kinds are welcome, from bug fixes to new features. Follow the guidelines below to ensure that your contribution is successful.

## How to Contribute

1. **Fork the repository**: Fork this repository to your GitHub account, clone it locally, and create a new branch for your contribution. Use a descriptive name for your branch, such as `fix-issue-123` or `feature/add-new-functionality`.

    ```bash
    git clone https://github.com/your-username/VoxelForge.git
    cd VoxelForge
    git checkout -b feature/add-new-functionality
    ```

2. **Choose an Issue**: Look for issues marked with the `hacktoberfest` or `help wanted` labels in the [issues](https://github.com/andrewrgarcia/VoxelForge/issues) section.

3. **Make your changes**: Make sure your changes are well-tested and follow the repository's coding standards. Use the existing codebase as a reference for naming conventions and structure.

4. **Run the tests**: Before submitting your pull request, make sure all tests pass.

    ```bash
    python -m unittest discover tests
    ```

5. **Create a Pull Request (PR)**: Once your changes are ready, push them to your fork and submit a pull request to the main repository.

    ```bash
    git add .
    git commit -m "Description of the change"
    git push origin feature/add-new-functionality
    ```

    Then, go to the original repository and [create a pull request](https://github.com/andrewrgarcia/VoxelForge/pulls) from your branch.

6. **Respond to feedback**: Be ready to make changes based on feedback from the maintainers. Discussions about improvements are a key part of the review process.

## Hacktoberfest 2024 Participation

We are excited to participate in **Hacktoberfest 2024**! To contribute during Hacktoberfest:

- Ensure that your pull requests are meaningful and not considered spam. Contributions must align with the rules of Hacktoberfest 2024 to be counted.
- Valid contributions will be marked with the `hacktoberfest-accepted` label.
- Look for issues tagged with `hacktoberfest` for tasks that are ideal for this event.

## Project Structure

The following is a high-level overview of the repository structure:

```plaintext
VoxelForge/
├── VoxelForge/
│   ├── __init__.py           # Package initialization
│   ├── core.py               # Core functionality
│   ├── utils.py              # Utility functions
│   ├── voxel.cpp             # Voxel C++ implementation
│   ├── octree.cpp            # Octree C++ implementation
│   └── main.cpp              # Pybind11 bindings
├── docs/
│   ├── source/
│   │   ├── examples/         # Example Python scripts
│   │   └── conf.py           # Sphinx documentation configuration
├── tests/                    # Unit tests
│   ├── test_core.py          # Core functionality tests
│   └── test_speed_tensor_add.py # Speed test for tensor conversion
├── setup.py                  # Setup script for installation
└── README.md                 # Project documentation
```

### File Extensions of Interest

- **Python files** (`*.py`): Core code and examples.
- **C++ files** (`*.cpp`): Backend implementations using Pybind11.
- **Documentation**: Found under the `docs/` folder.
- **Tests**: Found in the `tests/` directory.

Excluded directories: `venv`, `build`, `dist`, `__pycache__`.

## Code of Conduct

We follow the Contributor Covenant [Code of Conduct](CODE_OF_CONDUCT.md) to foster an open and welcoming community for all contributors.

## License

By contributing to **VoxelForge**, you agree that your contributions will be licensed under the BSD-3-Clause license.
