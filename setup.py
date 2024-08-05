from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import os

class get_pybind_include(object):
    """Helper class to determine the pybind11 include path
    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __str__(self):
        import pybind11
        return pybind11.get_include()

# Find PyTorch installation path
import torch
torch_include = os.path.join(torch.__path__[0], 'include')
torch_lib = os.path.join(torch.__path__[0], 'lib')

ext_modules = [
    Extension(
        'VoxelForge.voxelforge',
        ['VoxelForge/voxel.cpp'],
        include_dirs=[
            # Path to pybind11 headers
            get_pybind_include(),
            # get_pybind_include(user=True),
            torch_include,
            os.path.join(torch_include, 'torch/csrc/api/include')  # Ensure correct include path for PyTorch
        ],
        libraries=['torch', 'c10'],  # Ensure correct libraries for PyTorch
        library_dirs=[torch_lib],  # Path to PyTorch libraries
        language='c++'
    ),
]

setup(
    name='VoxelForge',
    version='0.1',
    author='Andrew Garcia',
    author_email='garcia.gtr@gmail.com',
    description='A high-performance Python package written in C++ for efficient voxel and mesh model creation.',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext},
    zip_safe=False,
    packages=['VoxelForge'],
    install_requires=[
        'pybind11>=2.6.0',
        'torch'
    ],
    classifiers=[
        'Programming Language :: Python :: 3',
        'Programming Language :: C++',
        'Operating System :: OS Independent',
    ],
)
