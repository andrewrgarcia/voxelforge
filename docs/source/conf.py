import os
import sys

# Adjust sys.path to include your Python package directory
sys.path.insert(0, os.path.abspath('../../VoxelForge'))

# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'VoxelForge'
copyright = '2024, Andrew Garcia'
author = 'Andrew Garcia'
release = '0.1.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'breathe',  # To integrate Doxygen with Sphinx
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',  # If you're using Google or Numpy style docstrings
    'sphinx.ext.todo',
    'sphinx.ext.viewcode',
]

# Paths for templates and static files
templates_path = ['_templates']
html_static_path = ['_static']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# Set the root document
root_doc = 'index'

# -- Breathe Configuration ---------------------------------------------------
# Link Breathe with the Doxygen output
breathe_projects = {
    "VoxelForge": "../../doxygen/xml"
}
breathe_default_project = "VoxelForge"

# Mock the voxelforge_cpp module
autodoc_mock_imports = ["voxelforge_cpp"]


# -- Options for HTML output -------------------------------------------------
html_theme = 'furo'  # Modern theme, clean and easy to navigate

# Path to your custom logo
html_logo = "_static/banner.png"

# Add custom CSS files if you have any styling changes
html_css_files = [
    'custom.css',
]
